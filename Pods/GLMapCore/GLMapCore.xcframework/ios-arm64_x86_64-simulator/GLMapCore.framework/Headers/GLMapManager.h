//
//  GLMapManager.h
//  GLMap
//
//  Created by Arkadi Tolkun on 3/11/14.
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

#import <GLMapCore/GLMapCoreTypes.h>

@class GLMapDownloadTask;
@class GLMapInfo;

NS_ASSUME_NONNULL_BEGIN

/// Notification is sent when list of maps is changed
EXPORT extern NSString *kGLMapListChanhged;
/**
 Blocks what will called on the main thread when task is completed or cancelled
 */
typedef void (^GLMapDownloadCompletionBlock)(GLMapDownloadTask *);

/**
 Blocks what will called on the main thread when subtask is completed or cancelled.

 Download task contains map data download task and navigation data download task inside.
 */
typedef void (^GLMapDownloadStatsBlock)(NSString *serverID, NSUInteger downloadSize, double downloadSpeed);

/**
 GLMapListUpdateBlock is used to notify about map list updates.

 Map list is stored at server and sometimes it takes some time to fetch latest map list. It is downloaded only if updated. If no changes happened block called
 almost immidiately.
 */
typedef void (^GLMapListUpdateBlock)(NSArray<GLMapInfo *> *_Nullable result, BOOL mapListUpdated, NSError *_Nullable error);

/**
 GLMapTileDownloadProgressBlock is called when tile downloaded.
 @return if NO returned downloading will be cancelled.
 */
typedef BOOL (^GLMapTileDownloadProgressBlock)(uint64_t tile, NSError *_Nullable error);

/**
 GLMapFloatBlock is called when anasyncronys request of slope or elevation  is finished.
 */
typedef void (^GLMapFloatBlock)(float slope);

/**
 GLMapDownloadProgress is preriodically called to report porgress of download
 */
typedef void (^GLMapDownloadProgress)(NSUInteger totalSize, NSUInteger downloadSize, double downloadSpeed);

/**
 GLMapDownloadCompletion is called when download is finised
 */
typedef void (^GLMapDownloadCompletion)(NSError *_Nullable error);

/**
 Map manager used to work with list of offline maps
 */
EXPORT @interface GLMapManager : NSObject

/**
 Activates GLMap framework. Should be called before usage.

 @property key API key
 @property bundle Bundle with framework resources world.vm, fonts and DefaultStyle.bundle. If `null` uses main bundle.
 @property storagePath A path to folder where offline maps is stored. If `null` uses documents folder.
 */

+ (void)activateWithApiKey:(NSString *)apiKey
           resourcesBundle:(NSBundle *_Nullable)resourcesBundle
            andStoragePath:(NSString *_Nullable)storagePath CF_SWIFT_NAME(GLMapManager.activate(apiKey:resources:storage:));

/// Plain -init is disabled
- (instancetype)init __attribute__((unavailable("It's singleton object. Use `[GLMapManager sharedManager]`")));

#pragma mark - Properties

/**
 A path to folder where offline maps is stored
 */
@property(strong) NSString *storagePath;

/**
 Path to network activity log file. By default it's nil and logging is disabled.
 */
@property(strong) NSString *_Nullable networkActivityLogPath;

/**
 Allows to download map tiles one by one

 By default `tileDownloadingAllowed` = NO. GLMapView checks tile in world offline map first, then in embed and downloaded offline maps, then in downloaded
 earlier tiles and at last step if tile downloading is allowed it tries to download map tile.
 */
@property(assign) BOOL tileDownloadingAllowed;

/**
 Cached tile will be refreshed if it will stay in cache more than given time. Time interval is measured in seconds.

 By default `tileRefreshTimeInterval` = -1. If `tileRefreshTimeInterval` < 0  no tile refreshing will be triggered.
 */
@property(assign) int64_t tileRefreshTimeInterval;

/**
 Number of donwloded maps. World map is not counted as downloaded map.
 */
@property(readonly) NSInteger downloadedMapsCount;

/**
 All tasks created by `[GLMapManager downloadMap:withCompletionBlock]`
 Map download task is removed from array when map downloading is finished
 */
@property(readonly) NSArray<GLMapDownloadTask *> *allDownloadTasks;

/**
 Blocks what will called on the main thread when subtask is completed or cancelled.
 */
@property(strong) GLMapDownloadStatsBlock _Nullable downloadStatsBlock;

#pragma mark - Shared Methods

/**
 Singleton manager object
 */
@property(class, nonatomic, readonly) GLMapManager *sharedManager;

/**
 Bundle with resources
 */
@property(nonatomic, readonly) NSBundle *resourcesBundle;

#pragma mark - Methods

/**
 @return Returns array of `GLMapInfo` objects downloaded earlier and cached by `GLMapManager`
 */
- (NSArray<GLMapInfo *> *_Nullable)cachedMapList;

/**
 @return Returns dictionary of all `GLMapInfo` objects (including submaps) downloaded earlier and cached by `GLMapManager`
 */
- (NSDictionary<NSNumber *, GLMapInfo *> *_Nullable)cachedMaps;

/**
 Updates map list

 @param block A block called when map list is downloaded
 */
- (void)updateMapListWithCompletionBlock:(GLMapListUpdateBlock _Nullable)block;

/**
 Updates downloaded maps. Call this after placing map data files to storage path.
 */
- (void)updateDownloadedMaps;

/**
 Sorts maps by distance from border.
 @param maps maps to sort
 @param point point to meashure distance
 **/
- (void)sortMaps:(NSMutableArray<GLMapInfo *> *)maps fromPoint:(GLMapPoint)point;

/**
 Deletes downloaded map data sets

 @param dataSets data sets to delete
 @param map map object
 */
- (void)deleteDataSets:(GLMapInfoDataSetMask)dataSets forMap:(GLMapInfo *)map;

/**
 Starts download task

 It's up to you save download task or not. Active map download task could be received later from -downloadTaskForMap:.

 @param dataSets data sets to download
 @param map map object
 @param completionBlock completion block
 @return A new download task object
 */
- (NSArray<GLMapDownloadTask *> *)downloadDataSets:(GLMapInfoDataSetMask)dataSets
                                            forMap:(GLMapInfo *)map
                               withCompletionBlock:(GLMapDownloadCompletionBlock _Nullable)completionBlock;

/**
 Used to check if there is a download task for a given map
 @param map A map info object
 @return Returns `GLMapDownloadTask` previously created for a map
*/
- (GLMapDownloadTask *_Nullable)downloadTaskForMap:(GLMapInfo *)map dataSet:(GLMapInfoDataSet)dataSet;

/**
 Used to check if there is a download task for a given map and data set
 @param map A map info object
 @param dataSets data set to check
 @return Returns array of `GLMapDownloadTask` previously created for a map
 */
- (NSArray<GLMapDownloadTask *> *_Nullable)downloadTasksForMap:(GLMapInfo *)map dataSets:(GLMapInfoDataSetMask)dataSets;

/**
 Downloads custom data set
 @param dataSet Data set to download
 @param path Full path to file where to download data set
 @param bbox BBox of data to download
 @param progress Progress callback
 @param completion Completion callback
 @return taskID that can be used to cancel download
 */
- (int64_t)downloadDataSet:(GLMapInfoDataSet)dataSet
                      path:(NSString *)path
                      bbox:(GLMapBBox)bbox
                   progres:(GLMapDownloadProgress)progress
                completion:(GLMapDownloadCompletion)completion;

/**
 Cancels download by its task id
 @param taskID id of the task to cancel
 */
- (void)cancelDownload:(int64_t)taskID;

/**
 Cancels all downloads
 */
- (void)cancelAllDownloads;

/**
 Adds custom data set. Could be used for maps embed into the app resources.
 When map is added, it becomes available for all `GLMapView` objects.

 @param dataSet Data set to add
 @param path Path to the data
 @param bbox BBox of data (can be empty)
 @return `YES` if file is a valid data
 */
- (GLMapError)addDataSet:(GLMapInfoDataSet)dataSet path:(NSString *)path bbox:(GLMapBBox)bbox;

/**
 Removes custom data set from map manager. When removed is safe to delete data file.

 @param dataSet Data set to remove
 @param path Path to the data
 */
- (void)removeDataSet:(GLMapInfoDataSet)dataSet path:(NSString *)path;

/**
 Finds custom data set at point

 @param dataSet Data set to remove
 @param point Point to search
 */
- (NSArray<NSString *> *_Nullable)customDataSet:(GLMapInfoDataSet)dataSet atPoint:(GLMapPoint)point;

/**
 Returns map info with downloaded map data

 @param point Some point in internal format
 @return `GLMapInfo` of downloaded map
 */
- (GLMapInfo *_Nullable)downloadedMapAtPoint:(GLMapPoint)point;

/**
 Returns map at given point

 @param point Some point in internal format
 @return `GLMapInfo` of map
 */
- (NSArray<GLMapInfo *> *_Nullable)mapsAtPoint:(GLMapPoint)point;

/**
 Removes GLMap cached objects and closes opened databases

 `clearCaches` called automatically on `UIApplicationDidEnterBackgroundNotification`
 */
- (void)clearCaches;

/**
 Saves state for downloading tasks. It allows to resume downloads in case of crash or unexpected behavior

 Called automatically when app is minimized
 */
- (void)saveDownloadsState;

/**
 Returns vector tiles that bbox contains or intersects
 @param bbox bbox of area
 @return Returns vector tiles array contained or intersected by bbox
 */
- (NSArray<NSNumber *> *)vectorTilesAtBBox:(GLMapBBox)bbox;

/**
 Returns not cached vector tiles that bbox contains or intersects
 @param bbox bbox of area
 @return Returns not cached vector tiles contained or intersected by bbox
 */
- (NSArray<NSNumber *> *)notCachedVectorTilesAtBBox:(GLMapBBox)bbox;

/**
 Check if tiles cached. If not tile will be downloaded.
 @param tiles tiles to check
 @param progressBlock block that will be called when one tile is checked.
 */
- (void)cacheTiles:(NSArray<NSNumber *> *)tiles progressBlock:(GLMapTileDownloadProgressBlock _Nullable)progressBlock;

/**
 Returns bbox for given tile
 @param tile tile to calculate bbox
 @return Returns bbox of tile
 */
- (GLMapBBox)bboxForTile:(uint64_t)tile;

/**
 Enable fix of gcj coordinates to wgs
 **/
- (void)setNeedsChinaFix:(BOOL)needsChinaFix;

/**
 The method is used to retrieve elevation and slope data for a given set of points.

 @param points A pointer to an array of GLMapGeoPoint structures. Each structure specifies a point in geographical coordinates. This parameter must not be NULL.
 @param count The number of points in the array. This parameter can be zero.
 @param elevation A pointer to an array that the method fills in with the elevation data for each point, if not NULL. This is an output parameter.
 @param slope A pointer to an array that the method fills in with the slope data for each point, if not NULL. This is an output parameter.
 @return This method returns a BOOL value. If the method is successful, the return value is YES. If the method is not successful, the return value is NO.

 @note If either the elevation or slope parameters are NULL, the method will simply not fill in those values.
 */
- (BOOL)samplePoints:(GLMapGeoPoint *)points count:(NSInteger)count elevation:(float *_Nullable)elevation slope:(float *_Nullable)slope;

/**
 Returns elevation at given point
 @param point location of elevation data
 @return elevation at point in meters or INT16_MIN if no downloaded data for this point
 */
- (int16_t)elevationAtPoint:(GLMapGeoPoint)point;

/**
 Asyncronys request of elevation
 @param point location of elevation data
 @param completion block that will be called on completion
 */
- (void)elevationAtPoint:(GLMapGeoPoint)point completion:(GLMapFloatBlock)completion;

/**
 Returns slope at given point
 @param point location of slope data
 @return elevation at point in meters or NaN if no downloaded data for this point
 */
- (float)slopeAtPoint:(GLMapGeoPoint)point;

/**
 Asyncronys request of elevation
 @param point location of slope data
 @param completion block that will be called on completion
 */
- (void)slopeAtPoint:(GLMapGeoPoint)point completion:(GLMapFloatBlock)completion;

@end

NS_ASSUME_NONNULL_END
