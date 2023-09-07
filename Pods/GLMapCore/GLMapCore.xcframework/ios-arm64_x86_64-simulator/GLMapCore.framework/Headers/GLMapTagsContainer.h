//
//  GLMapTagsContainer.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 23.07.21.
//  Copyright © 2021 Evgen Bodunov. All rights reserved.
//

#import <GLMapCore/GLMapCoreTypes.h>

@class GLMapValue;
@class GLMapLocaleSettings;

NS_ASSUME_NONNULL_BEGIN

/**
 `GLMapTagsContainer` is a base class for objects that contains tags
 */
@interface GLMapTagsContainer : NSObject

/**
 Holds all properties set by setValue:forKey: or initialized from geoJSON
 */
@property(readonly) NSDictionary *properties;

/**
 Sets properties of object. This can be used by mapcss to apply different styles.

 In MapCSS style if you have for example rule `area|z9-[key=value]{ .. style params .. }`, "[key=value]" part means, that it will be applied only to objects,
 which have key equal to value. And this function allows you to set key and value. Other option is to pass keys and values is set them as properties of Features
 in GeoJSON.

 @param value Value to be set, or nil to remove value
 @param key Key to be set
 */
- (void)setValue:(NSString *_Nullable)value forKey:(NSString *)key;

/**
 Returns value of object style

 @param key Key string
 @return Value that set by `[GLMapVectorObject setValue:forKey:]` or loaded from geojson
 */
- (GLMapValue *_Nullable)valueForKey:(NSString *)key;

/**
 Returns array of values of object style

 Map data on OpenStreetMap could contain multiple values for same tag. According standard they should be divided with ;. Internally it's represented as multiple
 values for same tag.

 @param key Key string
 @return Values that tag
 */
- (NSArray<GLMapValue *> *_Nullable)valuesForKey:(NSString *)key;

/**
 Returns name of search result.
 @param localeSettings Locale settings used to find name
 @return Object name
 */
- (GLMapValue *_Nullable)localizedName:(GLMapLocaleSettings *)localeSettings;

@end

NS_ASSUME_NONNULL_END
