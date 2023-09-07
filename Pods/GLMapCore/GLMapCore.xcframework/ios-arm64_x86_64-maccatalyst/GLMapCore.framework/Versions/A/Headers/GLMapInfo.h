//
//  VectorMapInfo.h
//  GLMap
//
//  Created by Evgen Bodunov on 12/6/13.
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

#import <GLMapCore/GLMapCoreTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class GLMapLocaleSettings;

/// Notification sent when GLMapInfo.state property changes
EXPORT extern NSString *kGLMapInfoStateChanged;

/**
 `GLMapInfo` is a class with general information about all resources of vector map and states of that resources. It works with map data, navigation data,
 contour lines and hill shades. Returned by `-[GLMapManager cachedMapList]`
 */
EXPORT @interface GLMapInfo : NSObject

/// Disable default init
- (instancetype)init __attribute__((unavailable("GLMapInfo returned by `[GLMapInfo cachedMapList]`")));

#pragma mark - Properties

/// A dictionary mapping language codes to their corresponding names of this map
@property(readonly) NSDictionary<NSString *, NSString *> *names;

/// Unique ID of the offline map
@property(readonly) int64_t mapID;

/// Timestamp when the offline map was last updated on the server
@property(readonly) NSTimeInterval serverTimestamp;

/// Geographical point indicating the center of the map
@property(readonly) GLMapGeoPoint location;

/// Array containing sub-regions of the current offline map. Usually used for large maps (size > 300 MB)
@property(readonly) NSArray<GLMapInfo *> *subMaps;

/// Parent of the sub-region map or nil if the map is not a sub-region
@property(readonly) GLMapInfo *_Nullable parent;

/// Flag indicating if this `GLMapInfo` instance is deleted and has no data sets
@property(readonly) BOOL isDeleted;

/// Array of files associated with the map
@property(readonly) NSArray<NSURL *> *files;

#pragma mark - Methods

// Various methods for handling data set information including path, state, timestamps, sizes on disk and server, and state checks

/**
 Retrieves the file path for a specified map data set stored on the disk.

 @param dataSet The data set for which to retrieve the file path.

 @return A string representing the file path of the specified data set or nil if the data set is not available.
 */
- (NSString *_Nullable)pathForDataSet:(GLMapInfoDataSet)dataSet;

/**
 Fetches the current state of a specified map data set.

 @param dataSet The data set for which to retrieve the state.

 @return The current state of the specified data set.
 */
- (GLMapInfoState)stateForDataSet:(GLMapInfoDataSet)dataSet;

/**
 Retrieves the timestamp of a specified map data set stored on the disk.

 @param dataSet The data set for which to retrieve the timestamp.

 @return The timestamp of the specified data set on the disk. This may differ from the server timestamp if a map update has occurred on the server.
 */
- (NSTimeInterval)timestampForDataSet:(GLMapInfoDataSet)dataSet;

/**
 Retrieves the timestamp of a specified map data set on the server.

 @param dataSet The data set for which to retrieve the server timestamp.

 @return The timestamp of the specified data set on the server. This may differ from the disk timestamp if a map update has occurred on the server.
 */
- (NSTimeInterval)serverTimestampForDataSet:(GLMapInfoDataSet)dataSet;

/**
 Calculates the total size of the downloaded and decompressed data sets specified by a data set mask.

 @param dataSets A mask representing the data sets for which to calculate the total size.

 @return The total size, in bytes, of the specified data sets on the disk.
 */
- (uint64_t)sizeOnDiskForDataSets:(GLMapInfoDataSetMask)dataSets;

/**
 Calculates the total size of temporary files associated with the data sets specified by a data set mask.

 @param dataSets A mask representing the data sets for which to calculate the total size of temporary files.

 @return The total size, in bytes, of the temporary files associated with the specified data sets.
 */
- (uint64_t)tempSizeOnDiskForDataSets:(GLMapInfoDataSetMask)dataSets;

/**
 Calculates the total size of the specified map data sets on the server. The data sets are stored in a compressed format on the server.

 @param dataSets A mask representing the data sets for which to calculate the total size on the server.

 @return The total size, in bytes, of the specified data sets on the server.
 */
- (uint64_t)sizeOnServerForDataSets:(GLMapInfoDataSetMask)dataSets;

/**
 Checks the state of all data sets specified by a data set mask and determines if any of them are in a given state.

 @param state The state to check for.
 @param sets A mask representing the data sets to check.

 @return A boolean value indicating whether any of the specified data sets are in the given state.
 */
- (BOOL)haveState:(GLMapInfoState)state inDataSets:(GLMapInfoDataSetMask)sets;

/**
 Checks the state of all data sets and returns a mask of those data sets that are in a given state.

 @param state The state to check for.

 @return A mask representing the data sets that are in the given state.
 */
- (GLMapInfoDataSetMask)dataSetsWithState:(GLMapInfoState)state;

/**
 Retrieves the name of the map in a specified language.

 @param language A string representing the preferred language code.

 @return A string representing the localized name of the map in the requested language or nil if the name is not available in the requested language.
 */
- (NSString *_Nullable)nameInLanguage:(NSString *)language;

/**
 Fetches the name of the map in its native language.

 @return A string representing the map's name in its native language.
 */
- (NSString *)name;

/**
 Retrieves the name of the map according to the provided language priority settings.
 This method iterates through the list of preferred languages in the settings, from highest to lowest priority, until it finds a translated name that is
 available.

 @param settings An instance of GLMapLocaleSettings representing the preferred language order.

 @return A string representing the localized name of the map according to the provided language priority settings or nil if no translated name is available in
 the preferred languages.
 */
- (NSString *_Nullable)localizedName:(GLMapLocaleSettings *)settings;

/**
 Computes the geographical distance from the center of the map to a specified location.

 @param location A GLMapGeoPoint representing the location to measure distance from.

 @return A double representing the geographical distance in meters from the center of the map to the provided location.
 */
- (double)distanceFrom:(GLMapGeoPoint)location;

/**
 Calculates the distance from a given point to the nearest border of the map.

 @param location A GLMapPoint representing the point on the map to measure distance from.

 @return A double representing the distance to the nearest map border measured in internal units. If the point is inside the map border, it returns 0.
 */
- (double)distanceFromBorder:(GLMapPoint)location;

/**
 Generates the borders of the map as a multi-polygon.

 Each polygon in the multi-polygon consists of a set of rings, where the first ring represents the outer border and the remaining rings represent the inner
 borders. To get coordinates from `NSValue` use `-[NSValue glMapPoint]` or `-[NSValue glMapGeoPoint]` getter function.

 @return An array of arrays of arrays of NSValue objects, each representing a point in a ring of a polygon of the multi-polygon.
 */
- (NSArray<NSArray<NSArray<NSValue *> *> *> *)getPolygons;

@end

NS_ASSUME_NONNULL_END
