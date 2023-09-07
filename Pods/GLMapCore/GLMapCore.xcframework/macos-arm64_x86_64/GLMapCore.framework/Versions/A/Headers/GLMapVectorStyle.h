//
//  GLMapVectorStyle.h
//  GLMap
//
//  Created by Evgen Bodunov on 3/31/14.
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

#import <GLMapCore/GLMapCoreTypes.h>

@class GLMapValue;

/** `GLMapVectorStyle` is used to define appearance of text inside `GLMapMarkerLayer` or `GLMapView`.

 Style is used to render a map, which is stored inside DefaultStyle.bundle/Style.mapcss file. Detailed MapCSS specification is located at: http://www.mapcss.org
 */
EXPORT @interface GLMapVectorStyle : NSObject

/// Plain -init is disabled
- (instancetype _Nonnull)init __attribute__((unavailable("Please use `[GLMapVectorStyle createStyle:]` and `[GLMapVectorStyle createStyle:error:]`")));

NS_ASSUME_NONNULL_BEGIN

/**
 Creates style object.

 `GLMapVectorStyle *style = [GLMapVectorStyle createStyle(@"{font-size:12;}"];`

 @param style NSString with style rule in MapCSS format
 @return New `GLMapVectorStyle` object
 */
+ (nullable instancetype)createStyle:(NSString *_Nonnull)style;

/**
 Creates style object.

 @param style NSString with style rule in MapCSS format
 @param error Error is filled if object cannot be created

 @return New `GLMapVectorStyle` object
 */
+ (nullable instancetype)createStyle:(NSString *_Nonnull)style error:(NSError **)error;

/**
 Creates style with given iconName and iconTint
 @param iconName name of icon
 @param iconTint tint color of icon
 @return New `GLMapVectorStyle` object
 */
- (instancetype)initWithIconName:(NSString *_Nonnull)iconName andIconTint:(GLMapColor)iconTint;

/**
 Resolved value of 'icon-image' attribute.
*/
@property(readonly) GLMapValue *_Nullable iconName;

/**
 Resolved value of 'icon-tint' attribute.
*/
@property(readonly) GLMapColor iconTint;

/**
 Resolved value of 'icon-scale' attribute.
*/
@property(readonly) CGFloat iconScale;

/**
 Resolved value of 'text' attribute.
*/
@property(readonly) GLMapValue *_Nullable text;

/**
 Subset of parameters that defines only text style
*/
@property(readonly) GLMapVectorStyle *_Nullable textStyleSubset;

/**
 Resolved value of 'details-text' attribute.
*/
@property(readonly) GLMapValue *_Nullable detailsText;

/**
 Resolved value of 'details-description' attribute.
*/
@property(readonly) GLMapValue *_Nullable detailsDescription;

NS_ASSUME_NONNULL_END

@end
