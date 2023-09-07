//
//  GLMapVectorCascadeStyle.h
//  GLMap
//
//  Created by Evgen Bodunov on 1/10/17.
//  Copyright © 2017 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

/// TintFunctionBlock is used to customize tint function.
/// E.g. It's possible to add custom mapping for specific colors.
typedef GLMapColor (^TintFunctionBlock)(GLMapColor tint, GLMapColor color);

@class GLMapView;
@class GLMapViewState;
@class GLMapVectorObject;

/** `GLMapVectorCascadeStyle` is used to define appearance of `GLMapVectorObject`. One style could be used with many `GLMapVectorObjects`.

 Style is used to render a map, which is stored inside DefaultStyle.bundle/Style.mapcss. Detailed MapCSS specification is located at: http://www.mapcss.org

 MapCSS examples:

 Any point with tag natural=peak, should be displayed on zoom level 11+ with trangle icon tinted with brown color.
 ```
 node|z11-[natural=peak] {
        icon-image:"triangle.svg";
        icon-tint:brown;
 }
 ```
 Any point with tag natural=peak, should display it's localized name on zoom level 13+.
 ```
 node|z13-[natural=peak] {
 text: eval( locTag('name') );
        text-color:brown;
        font-size:12;
 }
 ```
*/

EXPORT @interface GLMapVectorCascadeStyle : NSObject

/**
 Unavailable. Please use `[GLMapVectorCascadeStyle createStyle:]` or `[GLMapVectorCascadeStyle createStyle:error:]`.
 */
- (instancetype _Nonnull)init
    __attribute__((unavailable("Please use `[GLMapVectorCascadeStyle createStyle:]` or `[GLMapVectorCascadeStyle createStyle:error:]`")));

NS_ASSUME_NONNULL_BEGIN

/**
 Helper to parse style wihtout
 `GLMapVectorCascadeStyle *style = [GLMapVectorCascadeStyle createStyle(@"area{fill-color:#10106050;}"];`
 @param style NSString with style rules in MapCSS format
 @return New `GLMapVectorCascadeStyle` object
 */
+ (instancetype _Nullable)createStyle:(NSString *)style;

/**
 Create optimized version of style with resolved zoom tests
 @param range valid zooms range
 @return optimzed version of style
 */
- (GLMapVectorCascadeStyle *)opimizedForZoomRange:(NSRange)range;

/**
Sets custom tint function for loading svg files
 @param function custom tint function
 @param cacheKey unique key used for caching
 */
- (void)setTintFunction:(TintFunctionBlock)function cacheKey:(NSString *)cacheKey;

/**
 Updates draw attributes of vector object.
 @mapView view where object is displayed
 @mapState map state to calulate all parameters or null to leave them as is
 @zoomLevel zoom level to test
 @return true if visible
 */
- (BOOL)updateDrawAttributesOfVectorObject:(GLMapVectorObject *)object mapState:(GLMapViewState *_Nullable)mapState forZoomLevel:(int)zoomLevel;

/**
 Returns all "icon-image" from style
 @return all "icon-image" from style
 */
- (NSSet<NSString *> *)allIconNames;

NS_ASSUME_NONNULL_END

@end
