//
//  GLMapTrackLayer.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 1/21/19.
//  Copyright © 2019 Evgen Bodunov. All rights reserved.
//

#import <GLMap/GLMapDrawObject.h>

NS_ASSUME_NONNULL_BEGIN

@class GLMapTrackData;
@class GLMapVectorStyle;

/**
 Block is called to get tracks data for given bbox
 @param bbox BBox of tracks
 @return array of `GLMapTrackData`
 */
typedef NSArray<GLMapTrackData *> *_Nullable (^GLMapTrackDataCallback)(GLMapBBox bbox);

/// `GLMapTrackLayer` is a subclass of `GLMapDrawObject` that is optimized to render GPS tracks on map.
EXPORT @interface GLMapTrackLayer : GLMapDrawObject

/// Plain -init is disabled
- (instancetype _Nonnull)init __attribute__((unavailable("GLMapTrackLayer should be created with [GLMapTrackLayer initWithDrawOrder:]")));

/**
 Initializes new GLMapTrackLayer
 @param drawOrder order of object
 */
- (instancetype _Nonnull)initWithDrawOrder:(int32_t)drawOrder;

/**
 Sets new tracks and style
 @param style style for tracks
 @param callback callback that provides data for bbox
**/
- (void)setStyle:(GLMapVectorStyle *)style andCallback:(GLMapTrackDataCallback)callback;

@end

NS_ASSUME_NONNULL_END
