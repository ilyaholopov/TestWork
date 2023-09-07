//
//  GLMapPoint.h
//  GLMap
//
//  Created by Arkadi Tolkun on 12.06.23.
//  Copyright © 2023 Evgen Bodunov. All rights reserved.
//

#ifndef GLMapPoint_h
#define GLMapPoint_h

#ifdef __cplusplus
extern "C" {
#endif

/// `GLMapPoint` always uses internal map coordinates. From 0 to `GLMapPointMax` for X and Y axis. Origin is at the top left corner.
typedef struct GLMapPoint {
    /// X coordinate
    double x;
    /// Y coordinate
    double y;
}
/// :nodoc:
GLMapPoint;

/// Maximum `GLMapPoint` value. World size in map coordinates is from 0 to `GLMapPointMax`.
extern const int32_t GLMapPointMax;

/// Equal to GLMapPointMake(0,0);
CF_SWIFT_NAME(GLMapPoint.zero)
extern const GLMapPoint GLMapPointZero;

/**
 Creates new `GLMapPoint`

 @param x X coordinate
 @param y Y coordinate
 @return New map point
 */
CF_SWIFT_NAME(GLMapPoint.init(x:y:))
ConstInline GLMapPoint GLMapPointMake(double x, double y) NoExcept
{
    return (GLMapPoint){x, y};
}

/**
 Checks equality of two map points

 @param a First map point
 @param b Second map point
 @return `true` if map points is equal
 */
ConstInline bool GLMapPointEqual(GLMapPoint a, GLMapPoint b) NoExcept
{
    return a.x == b.x && a.y == b.y;
}

/**
 Return sum of point components
 @param point  point
 @param x x component
 @param y y component
 @return Sum of components
 **/
CF_SWIFT_NAME(GLMapPoint.add(self:x:y:))
ConstInline GLMapPoint GLMapPointAdd(GLMapPoint point, double x, double y) NoExcept
{
    return (GLMapPoint){point.x + x, point.y + y};
}

/**
 Length between two points
 @param a First point
 @param b Second point
 @return length (in internal map units)
 */
CF_SWIFT_NAME(GLMapPoint.lengthTo(self:_:))
double GLMapPointLength(GLMapPoint a, GLMapPoint b) NoExcept;

#ifdef __cplusplus
}
template <class SomePoint> GLMapPoint GLMapPointMake(const SomePoint &pt)
{
    return {(double)pt.x, (double)pt.y};
}
#endif
#endif /* GLMapPoint_h */
