//
//  GLMapScaleRuler.h
//  GLMap
//
//  Created by Arkadi Tolkun on 19.04.23.
//  Copyright © 2023 Evgen Bodunov. All rights reserved.
//

#import <GLMap/GLMapDrawObject.h>
#import <GLMapCore/GLMapCoreTypes.h>

/// `GLMapScaleRulerTextFormatterBlock` is used to change scale ruler format or localize unit name.
typedef NSString *_Nullable (^GLMapScaleRulerTextFormatterBlock)(int value, GLUnits units);
@class GLMapVectorStyle;

NS_ASSUME_NONNULL_BEGIN

/**
 * `GLMapScaleRuler`draws a scale ruler on screen
 */
EXPORT @interface GLMapScaleRuler : GLMapDrawObject

/**
 Initializes empty balloon that will be displayed with given drawOrder
 @param drawOrder drawOrder of object
 */
- (instancetype)initWithDrawOrder:(int32_t)drawOrder;

/**
 Sets text at the bottom of ruler.

 It's used to display map center coordinates or any other useful information
 */
- (void)setBottomText:(NSString *_Nullable)text;

/**
 Sets style of text at the bottom of ruler.
 Defaul is "{font-size:11; text-color:black; fill-color:#000000B2; font-stroke-width:2pt; font-stroke-color:#FFFFFF99;}
 */
- (void)setBottomTextStyle:(GLMapVectorStyle *)style;

/**
 Sets style of the scale ruler.
     //Sets scale ruler position to the bottom center part of screen. And width to half of screen width
     [_mapView setScalePlacement:GLMapPlacement_BottomLeft paddings:CGPointMake(5, 5) maxWidth:300];
 @param placement placement of text
 @param paddings paddings of scale ruler
 @param maxWidth maxWidth of scale hit in points
 */
- (void)setPlacement:(GLMapPlacement)placement paddings:(CGPoint)paddings maxWidth:(float)maxWidth;

/**
 Sets block that called when ruler value is updated. Block allows to translate units and use custom digit format inside ruler.
 @param block New text formatter block
 */
- (void)setTextFormatterBlock:(GLMapScaleRulerTextFormatterBlock)block;

@end

NS_ASSUME_NONNULL_END
