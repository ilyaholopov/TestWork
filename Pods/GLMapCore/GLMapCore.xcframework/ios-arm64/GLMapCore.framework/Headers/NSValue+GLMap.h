//
//  NSValue+GLMap.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 1/28/17.
//  Copyright © 2017 Evgen Bodunov. All rights reserved.
//

#import <GLMapCore/GLMapCoreTypes.h>

/// Extensions to store `GLMapPoint` and `GLMapGeoPoint` inside `NSValue`
EXPORT @interface NSValue(GLMapViewAdditions)

/**
 Creates `NSValue` object with `GLMapPoint`.

 @param pt Point
 @return Returns new `NSValue` object with `GLMapPoint` inside.
 */
+ (NSValue *)valueWithGLMapPoint:(GLMapPoint)pt;

/**
 Creates `NSValue` object with `GLMapGeoPoint`.

 @param pt Point
 @return Returns new `NSValue` object with `GLMapGeoPoint` inside.
 */
+ (NSValue *)valueWithGLMapGeoPoint:(GLMapGeoPoint)pt;

/**
 Creates `NSValue` object with `GLMapBBox`.

 @param bbox BBox
 @return Returns new `NSValue` object with `GLMapBBox` inside.
 */
+ (NSValue *)valueWithGLMapBBox:(GLMapBBox)bbox;

/**
 Returns `GLMapPoint` object from `NSValue`.

 It automatically converts value from `GLMapGeoPoint` to `GLMapPoint` if needed.
 If there is no `GLMapPoint` or `GLMapGeoPoint` inside (NaN, NaN) is returned.

 @return Returns `GLMapPoint` object from `NSValue`.
 */
- (GLMapPoint)glMapPoint;

/**
 Returns `GLMapGeoPoint` object from `NSValue`.

 It automatically converts value from `GLMapPoint` to `GLMapGeoPoint` if needed.
 If there is no `GLMapGeoPoint` or `GLMapPoint` inside (NaN, NaN) is returned.

 @return Returns `GLMapGeoPoint` object from `NSValue`.
 */
- (GLMapGeoPoint)glMapGeoPoint;

/**
 Returns `GLMapBBox` object from `NSValue`.
 @return Returns `GLMapBBox` object from `NSValue`.
 */
- (GLMapBBox)glMapBBox;

@end
