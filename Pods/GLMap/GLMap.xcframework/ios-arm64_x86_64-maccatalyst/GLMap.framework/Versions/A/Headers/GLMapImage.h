//
//  GLMapImage.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 5.08.22.
//  Copyright © 2022 Evgen Bodunov. All rights reserved.
//

#import <GLMap/GLMapDrawable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * `GLMapImage`draws a image on map.
 */
EXPORT @interface GLMapImage : GLMapDrawable

/**
 Initializes empty image that will be displayed with given drawOrder
 @param drawOrder drawOrder of object
 */
- (instancetype)initWithDrawOrder:(int32_t)drawOrder;

/**
 Initializes image that will be injected into map tile data (for example you can set vector object that can be displayed under map elements)
 */
- (instancetype)init;

/**
 Loads image into `GLMapImage`
 This variant will not load anything into OpenGL util `GLMapImage` will be added to some mapView that will try to render it.
 `UIImage` will be retained by `GLMapDrawable`.

 @param image New image to display on map
 @param completion A block called when image is replaced.
 */
- (void)setImage:(PlatformImage *)image completion:(dispatch_block_t _Nullable)completion;

/**
 Loads image into `GLMapImage`
 This variant of function loads OpenGL data into given mapView and does not retain image itself
 You must call this function for every mapView where you will display the image

 @param image New image to laod
 @param mapView where to load openGL resources
 @param completion A block called when image is replaced.
 */
- (void)setImage:(PlatformImage *)image forMapView:(GLMapView *)mapView completion:(dispatch_block_t _Nullable)completion;

@end

NS_ASSUME_NONNULL_END
