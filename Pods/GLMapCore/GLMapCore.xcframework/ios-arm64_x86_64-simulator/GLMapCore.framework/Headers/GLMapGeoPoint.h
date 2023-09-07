//
//  GLMapGeoPoint.h
//  GLMapCore
//
//  Created by Arkadi Tolkun on 12.06.23.
//  Copyright © 2023 Evgen Bodunov. All rights reserved.
//

#ifndef GLMapGeoPoint_h
#define GLMapGeoPoint_h

#ifdef __cplusplus
extern "C" {
#endif

/// Geo point with latitude and longitude
typedef struct GLMapGeoPoint {
    /// Latitude
    double lat;
    /// Longitude
    double lon;

#ifdef __cplusplus
    GLMapGeoPoint operator*(double mult) { return {lat * mult, lon * mult}; }
#endif
}
/// :nodoc:
GLMapGeoPoint;

/**
 Creates new `GLMapGeoPoint`.

 @param lat Latitude
 @param lon Longitude
 @return New geo point
 */
CF_SWIFT_NAME(GLMapGeoPoint.init(lat:lon:))
ConstInline GLMapGeoPoint GLMapGeoPointMake(double lat, double lon) NoExcept
{
    return (GLMapGeoPoint){lat, lon};
}

/**
 Checks equality of two geo points

 @param a First geo point
 @param b Second geo point
 @return `true` if map points is equal
 */
ConstInline bool GLMapGeoPointEqual(GLMapGeoPoint a, GLMapGeoPoint b) NoExcept
{
    return a.lat == b.lat && a.lon == b.lon;
}

/**
 Calculates distance between two points. Сontains internal conversion to GLMapGeoPoint.

 @param a First geo point
 @param b Second geo point
 @return Distance in meters
 */
CF_SWIFT_NAME(GLMapGeoPoint.distanceTo(self:_:))
double GLMapDistanceBetweenGeoPoints(GLMapGeoPoint a, GLMapGeoPoint b);

/**
 Calculates bearing between two points. Сontains internal conversion to GLMapGeoPoint.

 @param a First geo point
 @param b Second geo point
 @return bearing angle in degrees
 */
CF_SWIFT_NAME(GLMapGeoPoint.bearingTo(self:_:))
double GLMapBearingBetweenGeoPoints(GLMapGeoPoint a, GLMapGeoPoint b);

#ifdef __cplusplus
}
#endif

#endif /* GLMapGeoPoint_h */
