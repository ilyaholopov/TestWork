//
//  GLMapDrawable.h
//  GLMap
//
//  Created by Evgen Bodunov on 3/16/14.
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

#import <GLMap/GLMapDrawObject.h>

@class GLMapVectorStyle;
@class GLMapVectorObject;
@class GLMapVectorObjectArray;
@class GLMapVectorCascadeStyle;
@class GLMapView;

/**
 `GLMapDrawable` is a bridge class, to work with GLMap internal representation of object that should be rendered on map. This can be single image, text or
 vector object. `GLMapDrawable` can be rendered as a separate object or injected into tile data. Check `GLMapImageGroup` for big groups of images. Or
 `GLMapMarkerLayer` to display map markers with clustering.

 @see `[GLMapView addDrawable:]`
 @see `GLMapMarkerLayer`
 @see `GLMapImageGroup`
 */

/**
 Normal drawable:
 0, GLMapPointMax                   GLMapPointMax, GLMapPointMax
  ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
  ┃                                             ┃
  ┃           ╭────────────────────T            ┃
  ┃           │                    │            ┃
  ┃           │←╍╍╍╍╍╍╍╍╍╍╍╍╍P     │            ┃
  ┃           │              ╏     │            ┃
  ┃           │              ╏     │            ┃
  ┃           │              ↓     │            ┃
  ┃           O──────────────┴─────╯            ┃
  ↑                                             ┃
  ┗━→━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 0,0                                GLMapPointMax,0

 P = position (GLMapPoint)
 O = position - offset * scale (pt)
 T = O + size * scale (pt)

 Drawable that uses transform:
 0, GLMapPointMax                   GLMapPointMax, GLMapPointMax
 ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 ┃                                              ┃
 ┃           ╭────────────────────T             ┃
 ┃           │                    │             ┃
 ┃           │                    │             ┃
 ┃           │                    │             ┃
 ┃           │                    │             ┃
 ┃           │                    │             ┃
 ┃           P────────────────────╯             ┃
 ↑                                              ┃
 ┗━━→━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 0,0                                GLMapPointMax,0

 P = position (GLMapPoint)
 T = position + size * scale (GLMapPoint)
 **/

EXPORT @interface GLMapDrawable : GLMapDrawObject

/// Plain -init is disabled
- (instancetype _Nonnull)init __attribute__((unavailable("GLMapDrawable is abstract class")));

#pragma mark - Properties

/**
 When set to `YES` image rotates with map. Default value is 'NO'
 */
@property(assign) BOOL rotatesWithMap;

/**
 GLMapTransform mode of drawable
 */
@property(assign) GLMapTransformMode transformMode;

/**
 A position that sets image position in map internal coordinates
 For vector object adds translation
 Animatable.
 */
@property(assign) GLMapPoint position;

/**
 Image offset from the `position` point, measured in image pixels.
 Can be used for both image and text.
 When the offset is (0, 0), the bottom-left corner of the image is displayed at the position. When the offset is (image.size.width / 2, 0), it is ideal for a
 pin. Animatable.
*/
@property(assign) CGPoint offset;

/**
 A size of image in pixels
 Can be used for image and text
 */
@property(readonly) CGSize size;

/**
 Scale of object. (by default is 1.0)
 Animatable.
 */
@property(assign) double scale;

/**
 A float variable that defines image angle
 Animatable.
 */
@property(assign) float angle;

#pragma mark - Methods

/**
 * Tests if point is inside of image
 * @param mapView mapView where images is displayed
 * @param point point to check
 * @param paddings paddings of image
 * @return `true` if point is inside image
 */
- (BOOL)hitTest:(CGPoint)point onMap:(GLMapView *_Nonnull)mapView withPaddings:(PlatformEdgeInsets)paddings;

@end
