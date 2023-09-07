//
//  GLMapViewTypes.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 1/15/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#ifndef GLMapViewSDK_GLMapViewTypes_h
#define GLMapViewSDK_GLMapViewTypes_h

#include <errno.h>
#include <math.h>
#include <stdint.h>

#ifdef __OBJC__
#    import <CoreGraphics/CoreGraphics.h>
#    import <Foundation/Foundation.h>
#    define ENUM_NAME(_name)
#else
#    define ENUM_NAME(_name) _name
#    define ENUM_ATTRIBUTES __attribute__((enum_extensibility(open)))
#    define CLOSED_ENUM_ATTRIBUTES __attribute__((enum_extensibility(closed)))
#    define OPTIONS_ATTRIBUTES __attribute__((flag_enum, enum_extensibility(closed)))
#    if (__cplusplus)
#        define NS_ENUM(_type, _name) enum ENUM_ATTRIBUTES _name : _type
#        define NS_CLOSED_ENUM(_type, _name) enum ENUM_ATTRIBUTES _name : _type
#        define NS_OPTIONS(_type, _name)                                                                                                                       \
            _type _name;                                                                                                                                       \
            enum OPTIONS_ATTRIBUTES : _type
#    else
#        define NS_ENUM(_type, _name)                                                                                                                          \
            _type _name;                                                                                                                                       \
            enum ENUM_ATTRIBUTES
#        define NS_CLOSED_ENUM(_type, _name)                                                                                                                   \
            _type _name;                                                                                                                                       \
            enum CLOSED_ENUM_ATTRIBUTES
#        define NS_OPTIONS(_type, _name)                                                                                                                       \
            _type _name;                                                                                                                                       \
            enum OPTIONS_ATTRIBUTES : _type
#    endif
#endif

#ifndef CF_SWIFT_NAME
#    define CF_SWIFT_NAME(x)
#endif

#ifndef EXPORT
#    define EXPORT __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
#    define ConstInline static constexpr
#    define NoExcept noexcept
#else
#    define ConstInline static inline
#    define NoExcept
#endif

#include <GLMapCore/GLMapColor.h>
#include <GLMapCore/GLMapPoint.h>
#include <GLMapCore/GLMapGeoPoint.h>

#ifdef __cplusplus
extern "C" {
#endif
/// State of the vector map. `GLMapInfo` tracks state of the vector map.
typedef NS_CLOSED_ENUM(uint8_t, GLMapInfoState) {
    /// Map is deleted and there is no way to download it again because it was removed from map list.
    GLMapInfoState_Removed,
    /// Map is not downloaded, but available to download.
    GLMapInfoState_NotDownloaded,
    /// Map is downloaded successfully.
    GLMapInfoState_Downloaded,
    /// New version of map is available to download.
    GLMapInfoState_NeedUpdate,
    /// User cancelled map downloading.
    GLMapInfoState_NeedResume,
    /// Map downloading is in progress.
    GLMapInfoState_InProgress,
} ENUM_NAME(GLMapInfoState);

/// Data sets of vector map.
typedef NS_CLOSED_ENUM(uint8_t, GLMapInfoDataSet) {
    /// Data set with offline map data.
    GLMapInfoDataSet_Map,
    /// Data set with navigation data required for offline navigation feature.
    GLMapInfoDataSet_Navigation,
    /// Data set with elevation data
    GLMapInfoDataSet_Elevation,
    /// Number of data sets.
    GLMapInfoDataSet_Count,
} ENUM_NAME(GLMapInfoDataSet);

/// Data set mask. Used to perform action on multiple data sets at once.
typedef NS_OPTIONS(uint8_t, GLMapInfoDataSetMask) {
    /// Mask with offline map data.
    GLMapInfoDataSetMask_Map = (1 << GLMapInfoDataSet_Map),
    /// Mask with offline navigation data.
    GLMapInfoDataSetMask_Navigation = (1 << GLMapInfoDataSet_Navigation),
    /// Mask with offline elevation data
    GLMapInfoDataSetMask_Elevation = (1 << GLMapInfoDataSet_Elevation),
    /// Mask for all data sets.
    GLMapInfoDataSetMask_All = GLMapInfoDataSetMask_Map | GLMapInfoDataSetMask_Navigation | GLMapInfoDataSetMask_Elevation
};

/// Placement of the object on map view. It's used for scale ruler and attribution placement
typedef NS_CLOSED_ENUM(uint8_t, GLMapPlacement) {
    /// Top left corner
    GLMapPlacement_TopLeft,
    /// Top center of the screen
    GLMapPlacement_TopCenter,
    /// Top right corner
    GLMapPlacement_TopRight,

    /// Bottom left corner
    GLMapPlacement_BottomLeft,
    /// Bottom center of the screen
    GLMapPlacement_BottomCenter,
    /// Bottom right corner
    GLMapPlacement_BottomRight,

    /// Object should be hidden
    GLMapPlacement_Hidden
} ENUM_NAME(GLMapPlacement);

/// Alignment of text. It's used for text in MarkerLayer
typedef NS_CLOSED_ENUM(uint8_t, GLMapTextAlignment) {
    /// Undefined
    GLMapTextAlignment_Undefined,
    /// Center
    GLMapTextAlignment_Center,
    /// Bottom
    GLMapTextAlignment_Bottom,
    /// Top
    GLMapTextAlignment_Top,
    /// Right
    GLMapTextAlignment_Right,
    /// Left
    GLMapTextAlignment_Left
} ENUM_NAME(GLMapTextAlignment);

/// Type of data inside of the `GLMapVectorObject`
typedef NS_OPTIONS(uint8_t, GLMapVectorObjectType) {
    /// No geometry loaded yet
    GLMapVectorObjectType_Unknown = 0x0,
    /// Point object
    GLMapVectorObjectType_Point = 0x1,
    /// Line object
    GLMapVectorObjectType_Line = 0x2,
    /// Polygon object
    GLMapVectorObjectType_Polygon = 0x4,
    /// Any object
    GLMapVectorObjectType_Any = GLMapVectorObjectType_Point | GLMapVectorObjectType_Line | GLMapVectorObjectType_Polygon
};

/// Errors returned by download tasks
typedef NS_CLOSED_ENUM(uint16_t, GLMapError) {
    /// No error
    GLMapError_Success = 0x0000u,
    /// Custom error
    GLMapError_Custom,

    /// Used internally. Check for `[NSError domain]`, if it's equal to `ERRNO`, `[NSError code]` is ERRNO code [1-106].
    GLMapError_System = 0x800u,
    /// Used internally. Check for `[NSError domain]`, if it's equal to `HTTP`, `[NSError code]` is HTTP error code [100-526].
    GLMapError_HTTP = 0x1000u,
    /// Used internally. Check for `[NSError domain]`, if it's equal to `CURL`, `[NSError code]` is CURL error code [0 - 96].
    /// https://curl.haxx.se/libcurl/c/libcurl-errors.html
    GLMapError_CURL = 0x2000u,
    /// Used internally. Check for `[NSError domain]`, if it's equal to `XZ`, `[NSError code]` is XZ archiver error code [0 - 8].
    GLMapError_XZ = 0x4000u,
    /// Used internally. Check for `[NSError domain]`, if it's equal to `Valhalla`, `[NSError code]` is Valhalla archiver error code [100 - 599].
    GLMapError_Valhalla = 0x8000u,
} ENUM_NAME(GLMapError);

/// Checks if it's error or success code
CF_SWIFT_NAME(getter:GLMapError.isSuccess(self:))
ConstInline bool GLMapIsSuccess(GLMapError v) NoExcept
{
    return v == GLMapError_Success;
}

/// Transform mode for GLMapDrawable
typedef NS_CLOSED_ENUM(uint8_t, GLMapTransformMode) {
    /// Position is in map coordinates. Vector objects optimize it's geometry for zoom.
    GLMapTransformMode_Off,
    /// Position is in map coordinates. Vector objects does not optimize geometry for zoom.
    GLMapTransformMode_Custom,
    /// Position is in screen coordinates. Position == (0,0) is at map origin
    GLMapTransformMode_Screen,
} ENUM_NAME(GLMapTransformMode);

/// Supported unit systems
typedef NS_CLOSED_ENUM(uint8_t, GLUnitSystem) {
    /// International System of Units (SI)
    GLUnitSystem_International,
    /// Imperial units
    GLUnitSystem_Imperial,
    /// Nautical units
    GLUnitSystem_Nautical
} ENUM_NAME(GLUnitSystem);

/// Supported units
typedef NS_CLOSED_ENUM(uint8_t, GLUnits) {
    /// Kilometers
    GLUnits_Kilometers,
    /// Meters
    GLUnits_Meters,
    /// Miles
    GLUnits_Miles,
    /// Foots
    GLUnits_Feet,
    /// Nautical miles
    GLUnits_NauticalMiles,
    /// Cable length
    GLUnits_Cable,
    /// Fathoms
    GLUnits_Fathoms
} ENUM_NAME(GLUnits);

/// Maneuver types
typedef NS_CLOSED_ENUM(uint8_t, GLManeuverType) {
    /// Check https://github.com/valhalla/valhalla-docs/blob/master/turn-by-turn/api-reference.md
    GLManeuverType_None = 0,
    GLManeuverType_Start = 1,
    GLManeuverType_StartRight = 2,
    GLManeuverType_StartLeft = 3,
    GLManeuverType_Destination = 4,
    GLManeuverType_DestinationRight = 5,
    GLManeuverType_DestinationLeft = 6,
    GLManeuverType_Becomes = 7,
    GLManeuverType_Continue = 8,
    GLManeuverType_SlightRight = 9,
    GLManeuverType_Right = 10,
    GLManeuverType_SharpRight = 11,
    GLManeuverType_UturnRight = 12,
    GLManeuverType_UturnLeft = 13,
    GLManeuverType_SharpLeft = 14,
    GLManeuverType_Left = 15,
    GLManeuverType_SlightLeft = 16,
    GLManeuverType_RampStraight = 17,
    GLManeuverType_RampRight = 18,
    GLManeuverType_RampLeft = 19,
    GLManeuverType_ExitRight = 20,
    GLManeuverType_ExitLeft = 21,
    GLManeuverType_StayStraight = 22,
    GLManeuverType_StayRight = 23,
    GLManeuverType_StayLeft = 24,
    GLManeuverType_Merge = 25,
    GLManeuverType_RoundaboutEnter = 26,
    GLManeuverType_RoundaboutExit = 27,
    GLManeuverType_FerryEnter = 28,
    GLManeuverType_FerryExit = 29,
    GLManeuverType_Transit = 30,
    GLManeuverType_TransitTransfer = 31,
    GLManeuverType_TransitRemainOn = 32,
    GLManeuverType_TransitConnectionStart = 33,
    GLManeuverType_TransitConnectionTransfer = 34,
    GLManeuverType_TransitConnectionDestination = 35,
    GLManeuverType_PostTransitConnectionDestination = 36,
} ENUM_NAME(GLManeuverType);

/// Resource information filled by `GLMapResourceBlock`
typedef struct GLMapResource {
    /// Object data
    void *_Nullable data;
    /// Object data size
    uint32_t dataSize;
}
/// :nodoc:
GLMapResource;

/// Constains empty resource data.
CF_SWIFT_NAME(GLMapResource.empty)
extern const GLMapResource GLMapResourceEmpty;

/// Map tile state
typedef NS_CLOSED_ENUM(uint8_t, GLMapTileState) {
    /// Tile without data
    GLMapTileState_NoData,
    /// Tile data is being loaded
    GLMapTileState_Updating,
    /// Tile already has data
    GLMapTileState_HasData,
} ENUM_NAME(GLMapTileState);

/// Transition functions available
typedef NS_CLOSED_ENUM(uint8_t, GLMapTransitionFunction) {
    /// Instant set value. No animation.
    GLMapTransitionInstant = 0,
    /// Linear animation.
    GLMapTransitionLinear,
    /// Ease-in animation.
    GLMapTransitionEaseIn,
    /// Ease-out animation.
    GLMapTransitionEaseOut,
    /// Ease-in-out animation.
    GLMapTransitionEaseInOut,
} ENUM_NAME(GLMapTransitionFunction);

/// Id of world map.
extern const int64_t GLMapWorldMapID;

/// Merkator tile coordinates
typedef struct GLMapTilePos {
    /// X coordinate
    int x;
    /// Y coordinate
    int y;
    /// Z coordinate
    int z;
}
/// :nodoc:
GLMapTilePos;

/**
 Creates `GLMapTilePos`

 @param x X coordinate
 @param y Y coordinate
 @param z Z coordinate
 @return New tile position
 */
CF_SWIFT_NAME(GLMapTilePos.init(x:y:z:))
ConstInline GLMapTilePos GLMapTilePosMake(int x, int y, int z) NoExcept
{
    return (GLMapTilePos){x, y, z};
}

#ifdef __OBJC__
/// :nodoc:
EXPORT extern NSString *_Nonnull GLMapViewErrorDomain;

#    if TARGET_OS_OSX
#        import <AppKit/AppKit.h>

/// :nodoc:
typedef NSView PlatformView;
/// :nodoc:
typedef NSWindow PlatformWindow;
/// :nodoc:
typedef NSImage PlatformImage;
/// :nodoc:
typedef NSEdgeInsets PlatformEdgeInsets;
/// :nodoc:
typedef NSColor PlatformColor;

#        define PlatformColorFromGLMapColor NSColorFromGLMapColor
#        define PlatformImageGetScale(img) 1.0
#        define PlatformImageGetCGImage(img) [img CGImageForProposedRect:nil context:nil hints:nil]
#        define PlatformGetMainScreenScale() NSScreen.mainScreen.backingScaleFactor

/**
 Creates `NSColor` object from our `GLMapColor`

 @param color Initial color
 @return New `NSColor` object
 */
CF_SWIFT_NAME(getter:GLMapColor.nsColor(self:))
NSColor *_Nullable NSColorFromGLMapColor(GLMapColor color);
#    else
#        import <UIKit/UIKit.h>
#        if TARGET_OS_MACCATALYST
#            import <AppKit/AppKit.h>
#        endif
/// :nodoc:
typedef UIView PlatformView;
/// :nodoc:
typedef UIWindow PlatformWindow;
/// :nodoc:
typedef UIImage PlatformImage;
/// :nodoc:
typedef UIEdgeInsets PlatformEdgeInsets;
/// :nodoc:
typedef UIColor PlatformColor;

#        define PlatformColorFromGLMapColor UIColorFromGLMapColor
#        define PlatformImageGetScale(img) img.scale
#        define PlatformImageGetCGImage(img) img.CGImage
#        define PlatformGetMainScreenScale() UIScreen.mainScreen.scale

/**
 Creates `UIColor` object from our `GLMapColor`

 @param color Initial color
 @return New `UIColor` object
 */
CF_SWIFT_NAME(getter:GLMapColor.uiColor(self:))
UIColor *_Nullable UIColorFromGLMapColor(GLMapColor color);

/**
 Convert `UIColor` to `GLMapColor`

 @param color color to conver
 @@return converted value
 */
CF_SWIFT_NAME(GLMapColor.init(uiColor:))
GLMapColor GLMapColorMakeFromUIColor(UIColor *_Nonnull color);
#    endif

/// :nodoc:
@class NSData;

/// `GLMapResourceBlock` is used to load resources from custom place.
typedef GLMapResource (^GLMapResourceBlock)(NSString *_Nonnull name);

/**
 Converts `NSData` objects into `GLMapResources`.

 @param data Data object to convert.
 @return Created resource object.
 */
CF_SWIFT_NAME(GLMapResource.init(data:))
GLMapResource GLMapResourceWithData(NSData *_Nonnull data);
#endif

/// Point of track with color
typedef struct GLTrackPoint {
    /**
     Point of track in framework coordinates
     */
    GLMapPoint pt;
    /**
     Color of point. Specific color could be set for each point.
     */
    GLMapColor color;
}
/// :nodoc:
GLTrackPoint;

/// Point of track with color
typedef struct GLRoutePoint {
    /**
     * Coordinates of route point
     */
    GLMapGeoPoint pt;

    /**
     * Heading at given point or NaN
     */
    double heading;
    /**
     * Ignored in request
     * After route optimization this field will hold original index of point
     */
    int originalIndex;

    /**
     * If set to true point is a stop. Otherwise it is a waypoint.
     */
    bool isStop;

    /**
     * Allow UTurn in this point
     */
    bool allowUTurn;
}
/// :nodoc:
GLRoutePoint;

/// Creates route point
CF_SWIFT_NAME(GLRoutePoint.init(pt:heading:isStop:allowUTurn:))
ConstInline GLRoutePoint GLRoutePointMake(GLMapGeoPoint pt, double heading, bool isStop, bool allowUTurn) NoExcept
{
    return (GLRoutePoint){pt, heading, -1, isStop, allowUTurn};
}

/// Bounding box
typedef struct GLMapBBox {
    /// Bounding box origin. Point with minimal coordinates.
    GLMapPoint origin;
    /// Size of the bounding box.
    GLMapPoint size;
}
/// :nodoc:
GLMapBBox;

/// Empty bounding box. You always should start with empty bbox, then add points inside.
CF_SWIFT_NAME(GLMapBBox.empty)
extern const GLMapBBox GLMapBBoxEmpty;

/// Bounding box for whole world.
CF_SWIFT_NAME(GLMapBBox.world)
extern const GLMapBBox GLMapBBoxWorld;

/**
 Adds point into existing bounding box.

 @param bbox Bounding box
 @param point Point to add into bounding box
 */
CF_SWIFT_NAME(GLMapBBox.adding(self:_:))
ConstInline GLMapBBox GLMapBBoxAddPoint(GLMapBBox bbox, GLMapPoint point) NoExcept
{
    if (bbox.size.x < 0 && bbox.size.y < 0) {
        bbox.size = GLMapPointZero;
        bbox.origin = point;
    } else {
        if (point.x < bbox.origin.x) {
            bbox.size.x += bbox.origin.x - point.x;
            bbox.origin.x = point.x;
        }
        if (point.x > bbox.origin.x + bbox.size.x) {
            bbox.size.x = point.x - bbox.origin.x;
        }

        if (point.y < bbox.origin.y) {
            bbox.size.y += bbox.origin.y - point.y;
            bbox.origin.y = point.y;
        }
        if (point.y > bbox.origin.y + bbox.size.y) {
            bbox.size.y = point.y - bbox.origin.y;
        }
    }
    return bbox;
}

/**
 Checks if the bbox contains the point

 @param bbox Bounding box
 @param point Point to check
 @return true if point is in bbox
 */
CF_SWIFT_NAME(GLMapBBox.contains(self:_:))
ConstInline bool GLMapBBoxContains(GLMapBBox bbox, GLMapPoint point) NoExcept
{
    if (point.y < bbox.origin.y)
        return false;
    if (point.y > bbox.origin.y + bbox.size.y)
        return false;

    if (point.x >= bbox.origin.x && point.x <= bbox.origin.x + bbox.size.x)
        return true;

    if (point.x >= bbox.origin.x - GLMapPointMax && point.x <= bbox.origin.x + bbox.size.x - GLMapPointMax)
        return true;

    if (point.x >= bbox.origin.x + GLMapPointMax && point.x <= bbox.origin.x + bbox.size.x + GLMapPointMax)
        return true;

    return false;
}

/**
 Creates new bounding box

 @param origin Origin point
 @param width Width
 @param height Height
 @return New bounding box
 */
CF_SWIFT_NAME(GLMapBBox.init(origin:width:height:))
ConstInline GLMapBBox GLMapBBoxMake(GLMapPoint origin, double width, double height) NoExcept
{
    return (GLMapBBox){origin, GLMapPointMake(width, height)};
}

/**
 Checks equality of two bounding boxes

 @param a First bounding box
 @param b Second bounding box
 @return `true` if bounding boxes is equal
 */
ConstInline bool GLMapBBoxEqual(GLMapBBox a, GLMapBBox b) NoExcept
{
    return GLMapPointEqual(a.origin, b.origin) && GLMapPointEqual(a.size, b.size);
}

/**
 Returns center of bbox
 @return center of bbox
 */
CF_SWIFT_NAME(getter:GLMapBBox.center(self:))
ConstInline GLMapPoint GLMapBBoxCenter(GLMapBBox a) NoExcept
{
    return GLMapPointMake(a.origin.x + a.size.x / 2, a.origin.y + a.size.y / 2);
}

/**
 Computes distance from bounding box to point
 @param bbox Bounding box
 @param point Point
 @return Distance in internal coordinates
 */
CF_SWIFT_NAME(GLMapBBox.distanceTo(self:_:))
double GLMapBBoxDistanceToPoint(GLMapBBox bbox, GLMapPoint point);

/**
 Checks if two bbox have any common point
 @param a First bounding bbox
 @param b Second bounding bbox
 @return `true` if bbox intersecs other bbox
 */
CF_SWIFT_NAME(GLMapBBox.intersects(self:bbox:))
ConstInline bool GLMapBBoxIntersects(GLMapBBox a, GLMapBBox b) NoExcept
{
    return a.origin.x <= b.origin.x + b.size.x && b.origin.x <= a.origin.x + a.size.x && a.origin.y <= b.origin.y + b.size.y &&
           b.origin.y <= a.origin.y + a.size.y;
}

/**
 Creates map point from geo coordinates

 @param lat Latitude
 @param lon Longitude
 @return New map point
 */
CF_SWIFT_NAME(GLMapPoint.init(lat:lon:))
GLMapPoint GLMapPointMakeFromGeoCoordinates(double lat, double lon);

/**
 Creates map point from geo point
 @param point Geo point
 @return New point
 */
CF_SWIFT_NAME(GLMapPoint.init(geoPoint:))
GLMapPoint GLMapPointFromMapGeoPoint(GLMapGeoPoint point);

/**
Creates map point from tile position
@param tilePos Tile position
@return New point
*/
CF_SWIFT_NAME(GLMapPoint.init(tilePos:))
GLMapPoint GLMapPointFromMapTilePos(GLMapTilePos tilePos);

/**Creates geo point from map coordinates

@param point Map point
@return New geo point
*/
CF_SWIFT_NAME(GLMapGeoPoint.init(point:))
GLMapGeoPoint GLMapGeoPointFromMapPoint(GLMapPoint point);

/**
 Calculates distance between two points on map

 @param a First point on map
 @param b Second point on map
 @return Distance in meters
 */
CF_SWIFT_NAME(GLMapPoint.distanceTo(self:_:))
double GLMapDistanceBetweenPoints(GLMapPoint a, GLMapPoint b);

/**
 Calculates bearing between two geo points.

 @param a First point
 @param b Second point
 @return bearing angle in degrees
 */
CF_SWIFT_NAME(GLMapPoint.bearingTo(self:_:))
double GLMapBearingBetweenPoints(GLMapPoint a, GLMapPoint b);

/// Set of GLMapPoint
typedef void *GLMapPointSet;

/**
 Creates new empty set
 **/
GLMapPointSet _Nonnull GLMapPointSetCreate(void);

/**
 Destroys set
 @param set set to destroy
 **/
void GLMapPointSetDestroy(GLMapPointSet _Nonnull set);

/**
 Adds new point to set. Can add many points with same coordinates.
 @param set set to modify
 @param point point to add
 **/
void GLMapPointSetInsert(GLMapPointSet _Nonnull set, GLMapPoint point);

/**
 Inserts new point to set.
 @param set set to modify
 @param point point to insert.
 @return `true` if point is inserted. `false` if point with same coordinates already in set.
 **/
bool GLMapPointSetInsertUnique(GLMapPointSet _Nonnull set, GLMapPoint point);

/**
 Removes point from set
 @param set set to modify
 @param point point to remove
 @return YES if point was removed
 **/
bool GLMapPointSetRemove(GLMapPointSet _Nonnull set, GLMapPoint point);

/**
 Checks if set have given point
 @param set set to test
 @param point point to test
 @return YES if point is in set
 **/
bool GLMapPointSetContains(GLMapPointSet _Nonnull set, GLMapPoint point);

/**
 Returns nearest point in set
 @param set object created by `GLMapPointSetCreate`
 @param point reference point to calculate distance
 @return Nearest point in set
 **/
GLMapPoint GLMapPointSetNearestPoint(GLMapPointSet _Nonnull set, GLMapPoint point);

/// Set of GLMapPoint
typedef void *GLMapBBoxSet;

/**
 Creates new empty set
 **/
GLMapBBoxSet _Nonnull GLMapBBoxSetCreate(void);

/**
 Destroys set
 @param set set to destroy
 **/
void GLMapBBoxSetDestroy(GLMapBBoxSet _Nonnull set);

/**
 Test if bbox intersects with any other bbox in set.
 @param set set
 @param bbox bbox to test
 @return true if intersects
 **/
bool GLMapBBoxSetTest(GLMapBBoxSet _Nonnull set, GLMapBBox bbox);

/**
 Adds new bbox to set.
 @param set set to modify
 @param bbox bbox to add
 **/
void GLMapBBoxSetInsert(GLMapBBoxSet _Nonnull set, GLMapBBox bbox);

/// Allows application to change verbosity of GLMap logs
extern uint8_t GLMapLogMask;

/**
 Parse double using fast_float.
 @param string on input - string to parse, on outpur last position wehre parsing stops
 @param length length of string
 @param result on output - result of parse
 @return true if success
 */
EXPORT bool ParseDouble(const char *_Nonnull *_Nonnull string, uint32_t length, double *_Nonnull result);
/**
 Parse float using fast_float.
 @param string on input - string to parse, on outpur last position wehre parsing stops
 @param length length of string
 @param result on output - result of parse
 @return true if success
 */
EXPORT bool ParseFloat(const char *_Nonnull *_Nonnull string, uint32_t length, float *_Nonnull result);

// loglevel
#define VERBOSE_FLAG 1U
#define ERROR_FLAG 2U
#define FATAL_FLAG 4U
#define OPENGL_FLAG 8U

/// :nodoc:
EXPORT void SendLogMessage(const char *_Nonnull, ...);

/// Result of track sampling
typedef struct GLTrackSampleResult {
    /// Position on track
    GLMapPoint position;
    /// Direction of track
    GLMapPoint direction;
}
/// :nodoc:
GLTrackSampleResult;

#ifdef __cplusplus
}
#endif

#endif
