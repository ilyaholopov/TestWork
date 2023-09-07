//
//  GLMapLabel.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 5.08.22.
//  Copyright © 2022 Evgen Bodunov. All rights reserved.
//

#import <GLMap/GLMapDrawable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * `GLMapLabel`draws a label on map.
 */
EXPORT @interface GLMapLabel : GLMapDrawable

/**
 Initializes empty label that will be displayed with given drawOrder
 @param drawOrder drawOrder of object
 */
- (instancetype)initWithDrawOrder:(int32_t)drawOrder;

/**
 Initializes image that will be injected into map tile data (for example you can set vector object that can be displayed under map elements)
 */
- (instancetype)init;

/**
 Sets text to draw

 @param text New text
 @param style A style object used for text
 @param completion A block called when text is replaced.

 @see `GLMapVectorStyle`
 */
- (void)setText:(NSString *)text withStyle:(GLMapVectorStyle *)style completion:(dispatch_block_t _Nullable)completion;

/**
 Creates a new string with line breaks near position
 @param text - text to break
 @param position - position where line break will be placed
 @return new string with break
 */
+ (NSString *)breakLine:(NSString *)text position:(NSInteger)position;

/**
 Creates a new string with line breaks near default position
 @param text - text to break
 @return new string with break
 */
+ (NSString *)breakLine:(NSString *)text;

@end

NS_ASSUME_NONNULL_END
