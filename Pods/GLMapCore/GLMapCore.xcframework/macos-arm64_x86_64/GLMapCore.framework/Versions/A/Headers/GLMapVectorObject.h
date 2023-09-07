//
//  GLMapVectorObject.h
//  GLMap
//
//  Created by Arkadi Tolkun on 3/21/14.
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

#import <GLMapCore/GLMapCoreTypes.h>
#import <GLMapCore/GLMapTagsContainer.h>

@class GLMapVectorStyle;
@class GLMapVectorCascadeStyle;
@class GLSearchCategory;
@class GLSearchCategories;
@class GLMapLocaleSettings;
@class GLMapVectorObjectArray;
@class GLMapVectorObject;
@class GLMapView;
@class GLMapValue;
@class GLMapPointArray;

NS_ASSUME_NONNULL_BEGIN

/**
 * Called when next object is ready while enumerating
 * @return NO to break enumaration
 */
typedef BOOL (^GLMapVectorObjectBlock)(GLMapVectorObject *object);

/**
 `GLMapVectorObject` is a bridge class, to work with GLMap internal representation of vector object.
 */
EXPORT @interface GLMapVectorObject : GLMapTagsContainer<NSCopying>

#pragma mark - Properties

/**
 Point that belongs to vector object.
 */
@property(readonly) GLMapPoint point;

/**
 Bounding box of an object
 */
@property(readonly) GLMapBBox bbox;

/**
 Resolved draw attributes after last update.
 */
@property(copy) GLMapVectorStyle *_Nullable drawAttributes;

#pragma mark - Static Methods

/**
 Creates array of vector object from GeoJSON data

 @param geoJSONData Data with GeoJSON inside

 @return Array of new vector objects
 */
+ (GLMapVectorObjectArray *_Nullable)createVectorObjectsFromGeoJSONData:(NSData *)geoJSONData error:(NSError **)error;

/**
 Creates array of vector object from GeoJSON string

 @param geoJSON String with GeoJSON inside

 @return Array of new vector objects
 */
+ (GLMapVectorObjectArray *_Nullable)createVectorObjectsFromGeoJSON:(NSString *)geoJSON error:(NSError **)error;

/**
 Creates array of vector object from GeoJSON file

 @param filePath Path to GeoJSON file

 @return Array of new vector objects
 */
+ (GLMapVectorObjectArray *_Nullable)createVectorObjectsFromFile:(NSString *)filePath error:(NSError **)error;

/**
 Streamed parsing of GeoJSON file

 @param objectBlock block that is called when next object is ready

 @return NO if error happened
 */
+ (BOOL)enumVectorObjectsFromFile:(NSString *)filePath objectBlock:(GLMapVectorObjectBlock)objectBlock error:(NSError **)error;

#pragma mark - Methods

//- (instancetype _Nonnull)init __attribute__((unavailable("Please use proper subclass.")));

/**
 Finds nearest point of object to given point.
 */
- (BOOL)findNearestPoint:(GLMapPoint *)nearestPoint toPoint:(GLMapPoint)point maxDistance:(CGFloat)distance;

/**
 Compare with other object.
 **/
- (NSComparisonResult)compare:(id)object;

/**
 Usefull for debuging.
 */
- (NSString *)debugDescription;

/**
  GeoJSON representaion on vector object
 */
- (NSString *)asGeoJSON;

@end

NS_ASSUME_NONNULL_END
