//
//  GLMapLocaleSettings.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 6/3/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#import <GLMapCore/GLMapCoreTypes.h>

/**
 `GLMapLocaleSettings` is used to set language order to all `GLMapView` objects.

 For each label on map framework checks translated names in order set by `-initWithLocalesOrder:`, if no translated label is available - native name is used.

 Following map languages is included in vector map data

 * native - native language in for country or region
 * ar - Arabic
 * be - Belarusian
 * cs - Czech
 * da - Danish
 * de - German
 * en - English
 * es - Spanish
 * fr - French
 * it - Italian
 * ja - Japanese
 * ko - Korean
 * nl - Dutch
 * pl - Polish
 * pt - Portuguese
 * ru - Russian
 * sv - Swedish
 * uk - Ukrainian
 * zh - Chinese

 Check [Multilingual names in OpenStreetMap](http://wiki.openstreetmap.org/wiki/Multilingual_names) for more information.

 */
EXPORT @interface GLMapLocaleSettings : NSObject

#pragma mark - Static Methods

/**
 @return Settings object gets values from `+[NSLocale preferredLanguages]` to set order of locales
 */
+ (GLMapLocaleSettings *_Nonnull)systemSettings;

/**
 Sets of supported map languages

 @return Returns language codes supported by framework
 */
+ (NSSet<NSString *> *_Nonnull)supportedLocales;

/**
 @return Returns `YES` if `mapLanguage` is among supported languages
 */
+ (BOOL)isLocaleSupported:(NSString *_Nonnull)locale;

#pragma mark - Methods

/**
 Creates instance of GLMapLocaleSettings with given order of locales

 @param localesOrder Ordered array of language codes
 @param unitSystem Active unit system
 @return New locale settings object
 */
- (instancetype _Nonnull)initWithLocalesOrder:(NSArray<NSString *> *_Nullable)localesOrder unitSystem:(GLUnitSystem)unitSystem;

/**
 Locales order set during object initialization.
 */
@property(readonly) NSArray<NSString *> *_Nullable localesOrder;

/**
 Get localized string for key
 @return localized string
 */
- (NSString *_Nonnull)localizedString:(NSString *_Nonnull)key;

@end
