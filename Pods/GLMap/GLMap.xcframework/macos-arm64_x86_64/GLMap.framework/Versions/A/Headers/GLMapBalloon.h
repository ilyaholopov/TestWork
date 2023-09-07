//
//  GLMapBalloon.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 8.08.22.
//  Copyright © 2022 Evgen Bodunov. All rights reserved.
//

#import <GLMap/GLMapDrawable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * `GLMapBalloon`draws a ballon with text on map.
 */
EXPORT @interface GLMapBalloon : GLMapDrawable

/**
 Initializes empty balloon that will be displayed with given drawOrder
 @param drawOrder drawOrder of object
 */
- (instancetype)initWithDrawOrder:(int32_t)drawOrder;

/**
 Sets backgroud image of balloon
 @param image image to set
 @param insets insets of background image
 */
- (void)setBackgroundImage:(PlatformImage *)image insets:(PlatformEdgeInsets)insets;

/**
 Sets text of balloon

 @param text New text
 @param style A style object used for text
 @param completion A block called when balloon ready to draw with new text

 @see `GLMapVectorStyle`
 */
- (void)setText:(NSString *)text withStyle:(GLMapVectorStyle *)style insets:(PlatformEdgeInsets)insets completion:(dispatch_block_t _Nullable)completion;

/**
 Sets refrence angle to detect direction of balloon
 @param refrenceAngle refrence angle
 */
- (void)setRefrenceAngle:(float)refrenceAngle;

/**
 Sets positions where balloon can be displayed
 @param positions positions to set
 @param count number of positions
 */
- (void)setPossiblePositions:(const GLTrackSampleResult *)positions count:(NSUInteger)count;

/**
 If set to `true` position nearest to center of screen will be selected
 @param placeToCenter value to set
 */
- (void)setPlaceToCenter:(BOOL)placeToCenter;

@end

NS_ASSUME_NONNULL_END
