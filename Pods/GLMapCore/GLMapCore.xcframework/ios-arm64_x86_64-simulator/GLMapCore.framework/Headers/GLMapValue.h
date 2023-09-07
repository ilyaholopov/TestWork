//
//  GLMapValue.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 10/23/18.
//  Copyright © 2018 Evgen Bodunov. All rights reserved.
//

#import <GLMapCore/GLMapCoreTypes.h>

/**
 `GLMapValue` is a class that hold some value and can convert it to Obj-C or Swift value
 */
EXPORT @interface GLMapValue : NSObject

/**
 Initialize value with string.
 */
- (instancetype _Nullable)initWithString:(NSString *_Nonnull)string;

/**
 Converts value to float, or NAN on failure.
 @return Float value
 */
- (CGFloat)asFloat;

/**
 Converts value to string.
 @return String value
 */
- (NSString *_Nullable)asString;

/**
 Converts value to bool.
 @return Bool value
*/
- (BOOL)asBool;

/**
 Converts value to color
 @return Color value or nil on failure
 */
- (PlatformColor *_Nullable)asColor;

/**
 Used for values returned by offline search. When part of value is matched during search, this functions returns `NSAttributedString` with higlighted parts.
 @param normalAttributes Normal attributes
 @param highlightAttributes Highlight attributes
 @return Name value with highlighted parts
 */
- (NSAttributedString *_Nullable)asAttributedString:(NSDictionary *_Nonnull)normalAttributes highlight:(NSDictionary *_Nonnull)highlightAttributes;

/**
 Calculates stable hash for string
 @param string input string
 @return calculated hash
 */
+ (uint32_t)calcFastHash:(NSString *_Nonnull)string;

@end
