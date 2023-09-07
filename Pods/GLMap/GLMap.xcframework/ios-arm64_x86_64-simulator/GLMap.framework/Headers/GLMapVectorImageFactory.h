//
//  GLMapVectorImage.h
//  GLMap
//
//  Created by Evgen Bodunov on 12/16/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#import <GLMap/GLMapVectorImageTransform.h>
#import <GLMapCore/GLMapCoreTypes.h>

/// `GLMapTimestampBlock` is used to get timestamp of resource from custom place. Return NAN if no resurces with such name exit.
typedef double (^GLMapTimestampBlock)(NSString *_Nonnull name);
/**
 `GLMapVectorImageFactory` used to render images from svg files. Image factory caches rendered images for future use.
 */
EXPORT @interface GLMapVectorImageFactory : NSObject

/// Plain -init is disabled
- (instancetype _Nonnull)init __attribute__((unavailable("It's singleton object. Use `[GLMapVectorImageFactory sharedFactory]`")));

NS_ASSUME_NONNULL_BEGIN

/// Disables disk caching if set to `YES`. Default value is `NO`
@property(assign) BOOL disableCaching;

/// Returns singleton factory object
@property(class, nonatomic, readonly) GLMapVectorImageFactory *_Nonnull sharedFactory;

/// If not nil - GLMapVectorImageFactory will try to get image data using this block. If no data returned it will fallback to direct file reading
@property(strong) GLMapResourceBlock resourceBlock;

/// If timestamp is changed - image will be updated.
@property(strong) GLMapTimestampBlock timestampBlock;

/// Removes all memory cached images
- (void)clearCaches;

/// Delete all cached images files
- (void)deleteCachedFiles;

/**
 Renders `UIImage` from svg file.

 @param imagePath Path to the svg file

 @return Returns rendered image
 */
- (nullable PlatformImage *)imageFromSvg:(NSString *)imagePath;
/**
 Renders `UIImage` from svg file.

 @param imagePath Path to the svg file
 @param scale Scale applied during render. 1.0 - original image size.

 @return Returns rendered image
 */
- (nullable PlatformImage *)imageFromSvg:(NSString *)imagePath withScale:(double)scale;
/**
 Renders `UIImage` from svg file.

 @param imagePath Path to the svg file
 @param scale Scale applied during render. 1.0 - original image size.
 @param tintColor Tint color applied to the image. Use `0`, when no tint required.

 @return Returns rendered image
 */
- (nullable PlatformImage *)imageFromSvg:(NSString *)imagePath withScale:(double)scale andTintColor:(GLMapColor)tintColor;
/**
 Renders `UIImage` from svg file.

 @param imagePath Path to the svg file
 @param size Target image size
 @param tintColor Tint color applied to the image. Use `0`, when no tint required.

 @return Returns rendered image
 */
- (nullable PlatformImage *)imageFromSvg:(NSString *)imagePath withSize:(CGSize)size andTintColor:(GLMapColor)tintColor;

/**
 Renders `UIImage` from svg file.

 @param imagePath Path to the svg file
 @param size Target image size
 @param isInCenter Image placement inside the canvas
 @param tintColor Tint color applied to the image. Use `0`, when no tint required.

 @return Returns rendered image
 */
- (nullable PlatformImage *)imageFromSvg:(NSString *)imagePath withSize:(CGSize)size isInCenter:(BOOL)isInCenter andTintColor:(GLMapColor)tintColor;

/**
 Renders `UIImage` from svg file.
 @param imagePath Path to the svg file
 @param transform Transform to apply
 @return Returns rendered image
 */
- (nullable PlatformImage *)imageFromSvg:(NSString *)imagePath transform:(GLMapVectorImageTransform *_Nullable)transform;

/**
 Returns cached image for key

 @param key key of cached image
 @param timestamp timestamp to check modifications
 @return caceded image or nil if no image cached for key or timestamp are not equal
 **/
- (nullable PlatformImage *)cachedImageWithKey:(NSString *)key timestamp:(double)timestamp;

/**
 Caches image

 @param img image to cache
 @param key key of image
 @param timestamp timestamp of image. If NaN image will be cached only in memory
 **/
- (void)cacheImage:(PlatformImage *)img withKey:(NSString *)key timestamp:(double)timestamp;

/**
 Deletes cached image

 @param key key of image
 **/
- (void)deleteCached:(NSString *)key;

NS_ASSUME_NONNULL_END

@end
