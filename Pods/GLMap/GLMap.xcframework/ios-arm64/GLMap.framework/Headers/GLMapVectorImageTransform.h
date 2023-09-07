//
//  GLMapVectorImageTransform.h
//  GLMap
//
//  Created by Arkadi Tolkun on 23.11.22.
//  Copyright © 2022 Evgen Bodunov. All rights reserved.
//

#import <GLMapCore/GLMapCoreTypes.h>

NS_ASSUME_NONNULL_BEGIN

/// `ColorTransformBlock` is used to transform colors of image
typedef GLMapColor (^ColorTransformBlock)(GLMapColor color);

/// `RectTransformBlock` is used to transform draw rect of image
typedef CGRect (^RectTransformBlock)(CGRect color);

/// `GLMapVectorImageTransform` used to customize vector image rendering process and hold together all rendering params.
EXPORT @interface GLMapVectorImageTransform : NSObject

/// Color cache key
@property(strong, readonly) NSString *_Nullable colorCacheKey;
/// Color transform block
@property(strong, readonly) ColorTransformBlock _Nullable color;

/// Rect cache key
@property(strong, readonly) NSString *_Nullable rectCacheKey;
/// Rect transform block
@property(strong, readonly) RectTransformBlock _Nullable rect;

/// Sets scale to use during render
/// @param scale scale
- (void)setScale:(double)scale;

/// Sets expected size of image
/// @param size target size
/// @param inCenter when true,
- (void)setSize:(CGSize)size inCenter:(BOOL)inCenter;

/// Sets tint to use during render
/// @param tint tint
- (void)setTint:(GLMapColor)tint;

/// Sets block to transform colors of an image
/// @param color block that modifies colors
/// @param colorCacheKey name of that color in cache key
- (void)setColor:(ColorTransformBlock)color colorCacheKey:(NSString *)colorCacheKey;

/// Sets rect transform block
/// @param rect block that modifies rect of the image
/// @param rectCacheKey key for that image with updated rect
- (void)setRect:(RectTransformBlock)rect rectCacheKey:(NSString *)rectCacheKey;
@end

NS_ASSUME_NONNULL_END
