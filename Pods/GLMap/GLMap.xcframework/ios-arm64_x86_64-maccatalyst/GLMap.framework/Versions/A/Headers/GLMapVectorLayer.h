//
//  GLMapVectorLayer.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 5.08.22.
//  Copyright © 2022 Evgen Bodunov. All rights reserved.
//

#import <GLMap/GLMap.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * `GLMapVectorLayer`draws a multiple vector objects on map.
 */
EXPORT @interface GLMapVectorLayer : GLMapDrawable

/**
 Initializes empty vector layer that will be displayed with given drawOrder
 @param drawOrder drawOrder of object
 */
- (instancetype _Nonnull)initWithDrawOrder:(int32_t)drawOrder;

/**
 Initializes image that will be injected into map tile data (for example you can set vector object that can be displayed under map elements)
 */
- (instancetype _Nonnull)init;

/**
 Sets vector object to draw

 @param object object to draw
 @param style A style of object
 @param completion A block called when object ready to draw

 @see `GLMapVectorStyle`
 */
- (void)setVectorObject:(GLMapVectorObject *_Nonnull)object
              withStyle:(GLMapVectorCascadeStyle *_Nonnull)style
             completion:(dispatch_block_t _Nullable)completion;

/**
 Sets vector objects to draw

 @param objects objects to draw
 @param style A style of object
 @param completion A block called when object ready to draw

 @see `GLMapVectorStyle`
 */
- (void)setVectorObjects:(GLMapVectorObjectArray *_Nonnull)objects
               withStyle:(GLMapVectorCascadeStyle *_Nonnull)style
              completion:(dispatch_block_t _Nullable)completion;

@end

NS_ASSUME_NONNULL_END
