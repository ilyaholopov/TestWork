//
//  GLMapDownloadTask.h
//  GLMap
//
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

#import <GLMapCore/GLMapCoreTypes.h>
@class GLMapInfo;

/**
 Notification is sent when GLMapInfo.downloadProgress or GLMapInfo.processedProgress property is changed
 */
EXPORT extern NSString *_Nonnull kGLMapDownloadTaskProgress;

/**
 Notification is sent when download task is started
 */
EXPORT extern NSString *_Nonnull kGLMapDownloadTaskStarted;

/**
 Notification is sent when download task is finished
 */
EXPORT extern NSString *_Nonnull kGLMapDownloadTaskFinished;

/**
 `GLMapDownloadTask` is a class that downloads offline maps. It allows to cancel map download and check download error.

 @see `[GLMapManager downloadMap:withCompletionBlock:]`
 */
EXPORT @interface GLMapDownloadTask : NSObject

/// Plain -init is disabled
- (instancetype _Nonnull)init __attribute__((unavailable("GLMapDownloadTask should be created with - `[GLMapManager downloadMap:withCompletionBlock:]`")));

#pragma mark - Properties

/**
 `error` is nil if no error happens. Otherwise error contains information from component that failed. Error domain could be 'CURL', 'HTTP', 'XZ' or 'GLMap'. For
 more information check `GLMapError`

 @see `GLMapError`
 */
@property(readonly) NSError *_Nullable error;

/**
 `isCancelled` set to `YES` when task was cancelled.
 */
@property(readonly) BOOL isCancelled;

/**
 Speed of transfer. NAN if transfer is not started.
 */
@property(readonly) CGFloat speed;

/**
 Bytes downloded by task
 */
@property(readonly) uint32_t downloaded;

/**
 Total bytes to downloded by task
 */
@property(readonly) uint32_t total;

/**
 `GLMapInfo` for map being downloaded
 */
@property(readonly) GLMapInfo *_Nonnull map;

/**
 Data set being downloaded
 */
@property(readonly) GLMapInfoDataSet dataSet;

#pragma mark - Methods

/**
 Cancels downloading task at any time
 */
- (void)cancel;

@end
