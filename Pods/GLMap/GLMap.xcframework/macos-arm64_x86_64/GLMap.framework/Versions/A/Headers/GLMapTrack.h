//
//  GLMapTrack.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 1/28/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#import <GLMap/GLMapTrackLayer.h>

@class GLMapTrackData;
@class GLMapView;
@class GLMapVectorStyle;

NS_ASSUME_NONNULL_BEGIN

/**
 `GLMapTrack` is a container class for track objects. Main difference from line - data generalization function is used for tracks to remove data points
 redundant for current zoom level.
 */
EXPORT @interface GLMapTrack : GLMapTrackLayer

/// Plain -init is disabled
- (instancetype)init __attribute__((unavailable("GLMapTrack should be created with [GLMapTrack initWithDrawOrder:]")));

/**
 Initializes new GLMapTrack
 @param drawOrder order of object
 */
- (instancetype)initWithDrawOrder:(int32_t)drawOrder;

/**
 Sets track width and other properties
 @param style New track style
 */
- (void)setStyle:(GLMapVectorStyle *)style;

/**
 Sets track data
 @param data New track data
 */
- (void)setTrackData:(GLMapTrackData *_Nullable)data style:(GLMapVectorStyle *)style completion:(dispatch_block_t _Nullable)completion;

/**
 Color of track from start to progress index
 */
@property(nonatomic, assign) GLMapColor progressColor;

/**
 Track from start to progress index will change color to progress color.
 Animatable.
 */
@property(nonatomic, assign) double progressIndex;

@end

NS_ASSUME_NONNULL_END
