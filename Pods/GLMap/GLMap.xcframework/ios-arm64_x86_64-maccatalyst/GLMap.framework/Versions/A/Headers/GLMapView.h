//
//  GLMapView.h
//  GLMapView
//
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <CoreLocation/CoreLocation.h>

#import <GLMap/GLMapAnimation.h>

@class GLMapDrawObject;
@class GLMapVectorObject;
@class GLMapVectorCascadeStyle;
@class GLMapTileSource;
@class GLSearchCategories;
@class GLMapLocaleSettings;
@class GLMapVectorStyle;
@class GLMapTrackData;
@class GLMapViewState;

NS_ASSUME_NONNULL_BEGIN

/// `GLMapTapGestureBlock` called, when user tapped or long tapped on map. Add custom tap handling logic inside this block.
typedef void (^GLMapTapGestureBlock)(CGPoint pt);

/// `GLMapBBoxChangedBlock` called every time, when map is moved or zoom is changed.
typedef void (^GLMapBBoxChangedBlock)(GLMapBBox bbox);

/// `GLMapAnimationBlock` created for animations. Map properties modified inside `GLMapAnimationBlock` will use animation. Animation properties could be changed
/// in `animation` object.
typedef void (^GLMapAnimationBlock)(GLMapAnimation *animation);

/// `GLMapVisibleTilesChangedBlock` called when set of visible tiles changed
typedef void (^GLMapVisibleTilesChangedBlock)(NSSet *visibleTiles);

/// `GLMapCaptureFrameBlock` is called when frame is captured.
typedef void (^GLMapCaptureFrameBlock)(PlatformImage *_Nullable);

/**
 `GLMapView` is a custom `UIView` that renders and presents vector map.
 */
EXPORT @interface GLMapView : PlatformView<CLLocationManagerDelegate>

/**
 Captures frame from `GLMapView` to `UIImage`

 @return Current state of the `GLMapView`
 */
- (nullable PlatformImage *)captureFrame;

/**
 Captures frame from `GLMapView` to `UIImage` when all load operations will finish.

 @param block Block callback is called when screenshot is ready.

 @see `-captureFrame`
 @see `offscreen`
 */
- (void)captureFrameWhenFinish:(GLMapCaptureFrameBlock)block;

/**
 Allows to render offscreen frames

 By default offscreen = `NO`. And GLMapView stop render if there is no superview. But in case you need to capture frames from standalone GLMapView, you need to
 set offscreen = YES;
 */
@property BOOL offscreen;

/**
 Rendering frame interval. By default frameInterval is 2 (30 fps)
 */
@property NSInteger frameInterval;

/**
 State of tile in center of screen

 @see `centerTileStateChangedBlock`
 */
@property(readonly) GLMapTileState centerTileState;

#pragma mark - User Interface

/// Gestures handled by `GLMapView`
typedef NS_OPTIONS(NSUInteger, GLMapViewGestures) {
    /// Gesture recognition disabled
    GLMapViewGesture_None = 0,
    /// Pan gesture
    GLMapViewGesture_Pan = 1,
    /// Zoom gesture
    GLMapViewGesture_Zoom = 1 << 1,
    /// Rotate gesture
    GLMapViewGesture_Rotate = 1 << 2,
    /// Zoom in gesture
    GLMapViewGesture_ZoomIn = 1 << 3,
    /// Zoom out gesture
    GLMapViewGesture_ZoomOut = 1 << 4,
    /// Tap gesture
    GLMapViewGesture_Tap = 1 << 5,
    /// Long press gesture
    GLMapViewGesture_LongPress = 1 << 6,
    /// Recognise all gestures
    GLMapViewGesture_All = GLMapViewGesture_Pan | GLMapViewGesture_Zoom | GLMapViewGesture_Rotate | GLMapViewGesture_ZoomIn | GLMapViewGesture_ZoomOut |
                           GLMapViewGesture_Tap | GLMapViewGesture_LongPress
};

/**
 Sets mask that defines enabled gestures.

 Use `tapGestureBlock` and `longPressGestureBlock` to add your tap and long press handlers.
 */
@property(nonatomic, assign) GLMapViewGestures gestureMask;

/// `tapGestureBlock` called for each tap gesture recognized.
@property(copy) GLMapTapGestureBlock _Nullable tapGestureBlock;

/// `longPressGestureBlock` called for each long press gesture recognized.
@property(copy) GLMapTapGestureBlock _Nullable longPressGestureBlock;

/// `bboxChangedBlock` called when map is moved or zoomed.
@property(copy) GLMapBBoxChangedBlock _Nullable bboxChangedBlock;

/// `mapDidMoveBlock` called when animation or deceleration ends.
@property(copy) GLMapBBoxChangedBlock _Nullable mapDidMoveBlock;

/// `visibleTilesChangedBlock` called when set of visible tiles is changed.
@property(copy) GLMapVisibleTilesChangedBlock _Nullable visibleTilesChangedBlock;

/// `centerTileStateChangedBlock` called when centerTileState is changed
@property(copy) dispatch_block_t _Nullable centerTileStateChangedBlock;

/// Bounding box of the map
@property(readonly) GLMapBBox bbox;

/**
 Sets position of map attribution.
 */
@property(assign) GLMapPlacement attributionPosition;

/**
    Calculate bounding box of the map with insets
    @param insets insets in points
    @return bounding box
 */
- (GLMapBBox)bboxWithInsets:(PlatformEdgeInsets)insets;

#pragma mark - User Location
/**
 In order to show user location using GLMapView you should create your own CLLocationManager and set GLMapView as CLLocationManager's delegate. Or you could
 forward `-locationManager:didUpdateLocations:` calls from your location manager delegate to the GLMapView.
 */

/// Last location received by `GLMapView`
@property(readonly) CLLocation *_Nullable lastLocation;

/// Defines if user location is displayed or not. If `YES`, user location is displayed.
@property(assign, nonatomic) BOOL showUserLocation;

/**
 Sets alternative user location images.

 @param locationImage new user location image. If `nil`, old image is left unchanged.
 @param movementImage new user movement image. If `nil`, old image is left unchanged.
 */
- (void)setUserLocationImage:(PlatformImage *_Nullable)locationImage movementImage:(PlatformImage *_Nullable)movementImage;

#pragma mark - Style

/** Sets map style
 @param style Style to set
 */
- (void)setStyle:(GLMapVectorCascadeStyle *)style;

/**
 Sets scale of font loaded frrom styleBundle. By default fontScale is 1.0
 */
- (void)setFontScale:(float)fontScale;

/**
 Base source of tiles. By default it is vector source
 */
@property(copy) GLMapTileSource *base;

/**
 Tiles that draws over base tiles
 */
@property(copy) NSArray<GLMapTileSource *> *_Nullable overlays;

/**
  Draw elevation lines. By default is false.
 */
@property(assign) BOOL drawElevationLines;

/**
  Draw hill shades. By default is false.
 */
@property(assign) BOOL drawHillshades;

/**
  Draw slopes. By default is false.
 */
@property(assign) BOOL drawSlopes;

/**
 Forces reloading of all tiles.
 Call this function after modifying map style with functions `loadStyle*`
 */
- (void)reloadTiles;

/**
 Removes all tiles. Useful to reduce memory usage in background mode
 */
- (void)removeAllTiles;

#pragma mark - Configuring the Map Position

/**
 Origin point of the map coordinate system (X, Y).

 Changing the values in this property between 0 and 1 in relative coordinates describes the point of GLMapView which is considered as a center point for
 `mapCenter` and `setMapCenter:animated:`.

 @see `mapCenter`, `setMapCenter:`
 */
@property(assign) CGPoint mapOrigin;

/**
 Coordinates of the origin point of the map.
 @see `mapOrigin`
 */
@property(assign) GLMapPoint mapCenter;

/**
 Coordinates of the origin point of the map.
 @see `mapOrigin`
 */
@property(assign) GLMapGeoPoint mapGeoCenter;

/**
 Current zoom of the map view.
 */
@property(assign) double mapZoom;

/**
 Current zoom level of the map view.
 */
@property(assign) double mapZoomLevel;

/**
 Maximum possible value of `mapZoom`. Map won't zoom closer.
 */
@property(assign) double maxZoom;

/**
 Map rotation angle form 0° to 360°.
 */
@property(assign) double mapAngle;

/**
 Captures state of map for search (screenScale, mapCenter, zoom etc)
 */
@property(readonly) GLMapViewState *state;

/**
 Starts animation described in block.

 @param animations Block with animations. You could set animation params using block param.
 */
- (GLMapAnimation *)animate:(GLMapAnimationBlock NS_NOESCAPE)animations;

/**
 Starts animation described in block.

 @param animations Block with animations. You could set animation params using block param.
 @param completion Commpletion block. It's called when animation ends or cancelled.
 */
- (GLMapAnimation *)animate:(GLMapAnimationBlock NS_NOESCAPE)animations withCompletion:(GLMapAnimationCompletionBlock _Nullable)completion;

/**
 Starts animation
 @param animation Animation to start.
 */
- (void)startAnimation:(GLMapAnimation *)animation;

/**
 Cancels all map position, zoom and angle animations.
 */
- (void)cancelMapAnimations;

/**
 Calculates map zoom to fit bbox in view with given size.

 @warning If bbox size is 0, returns +inf.
 */
- (double)mapZoomForBBox:(GLMapBBox)bbox viewSize:(CGSize)size;

/**
 Calculates map zoom to fit current view.

 @warning If bbox size is 0, returns +inf.
 */
- (double)mapZoomForBBox:(GLMapBBox)bbox;

/**
 * Enables clipping of visible map area
 *
 * @param bbox clipping bbox to set
 * @param minLevel min zoom level
 * @param maxLevel max zoom level
 */
- (void)enableClipping:(GLMapBBox)bbox minLevel:(float)minLevel maxLevel:(float)maxLevel;

/**
 * Disables clipping of visible map area
 */
- (void)disableClipping;

/**
 * Checks if clipping is enabled
 * @return true if enabled
 */
- (BOOL)isClippingEnabled;

#pragma mark - Converting map coordinates

/**
 Converts a point on the screen to an internal map coordinate.

 @param displayPoint The point you want to convert.
 @return The internal map coordinate of the specified point.
 */
- (GLMapPoint)makeMapPointFromDisplayPoint:(CGPoint)displayPoint;

/**
 Converts a distance between two points on the screen to an internal map coordinate at current map zoom.

 @param displayDelta The delta you want to convert.
 @return The delta in internal map coordinates.
 */
- (GLMapPoint)makeMapPointFromDisplayDelta:(CGPoint)displayDelta;

/**
 Converts a distance between two points on the screen to an internal map coordinate.

 @param displayDelta The delta you want to convert.
 @param mapZoom Zoom of map
 @param mapAngle Angle of map
 @return The delta in internal map coordinates.
 */
- (GLMapPoint)makeMapPointFromDisplayDelta:(CGPoint)displayDelta andMapZoom:(double)mapZoom andMapAngle:(double)mapAngle;

/**
 Converts a geo point to the point on the screen.

 @param geoPoint The geo point you want to convert.
 @return Coresponding point on the screen.
 */
- (CGPoint)makeDisplayPointFromGeoPoint:(GLMapGeoPoint)geoPoint;

/**
 Converts a point on the screen to the geo point.

 @param displayPoint Point on screen you want to convert.
 @return Coresponding geo point.
 */
- (GLMapGeoPoint)makeGeoPointFromDisplayPoint:(CGPoint)displayPoint;

/**
 Converts an internal map coordinate to the point on the screen.

 @param mapPoint The map point you want to convert.
 @return Coresponding point on the screen.
 */
- (CGPoint)makeDisplayPointFromMapPoint:(GLMapPoint)mapPoint;

/**
 Converts geo coordinates to the internal point.

 @param geoPoint Geo point you want to convert.
 @return Corresponding point in map coordinates.
 */
+ (GLMapPoint)makeMapPointFromGeoPoint:(GLMapGeoPoint)geoPoint;

/**
 Converts an internal point to geo coordinates.

 @param mapPoint Point in map coordinates.
 @return Corresponding point in geo coordinates.
 */
+ (GLMapGeoPoint)makeGeoPointFromMapPoint:(GLMapPoint)mapPoint;

/**
 Converts distance in meters to pixels on the screen

 @param meters Distance in meters
 @return Distance in pixels
 */
- (double)makePixelsFromMeters:(double)meters;

/**
 Converts distance in pixels on the screen to meters

 @param pixels Distance in pixels
 @return Distance in meters
 */
- (double)makeMetersFromPixels:(double)pixels;

/**
 Converts distance in meters to map coordinates

 @param meters Distance in meters
 @return Distance in map coordinates
 */
- (double)makeInternalFromMeters:(double)meters;

/**
 Converts distance in map coordinates to meters

 @param internal Distance in map coordinates
 @return Distance in meters
 */
- (double)makeMetersFromInternal:(double)internal;

/**
 Converts distance in pixels to map coordinates

 @param pixels Distance in pixels
 @return Distance in map coordinates
 */
- (double)makeInternalFromPixels:(double)pixels;

/**
 Converts distance in map coordinates to pixels

 @param internal Distance in map coordinates
 @return Distance in pixels
 */
- (double)makePixelsFromInternal:(double)internal;

#pragma mark - Vector Objects

/**
 Adds the `GLMapDrawObject` to the map view.

 @param drawObject object to add
 */
- (void)add:(GLMapDrawObject *)drawObject;

/**
 Removes previsously added `GLMapDrawObject` from the map view.

 @param drawObject object to be removed.
 */
- (void)remove:(GLMapDrawObject *)drawObject;

/**
 When set to true - poi will not display icon and text
 @param forceHidden value to set
 @param poi object
 */
- (void)setForceHidden:(BOOL)forceHidden forPOI:(GLMapVectorObject *)poi;

/**
 Map locale settings

 Set of supported locales is returned by `[GLMapLocaleSettings supportedLocales]`

 E.g. to set map languages priority to English, Deutsch, native

     [_mapView setLocaleSettings:[[GLMapLocaleSettings alloc] initWithLocalesOrder:@[@"en", @"de", @"native"]]];
     // Then reload tiles to apply new locale settings
     [_mapView reloadTiles];

 Default value is supported languages from `[NSLocale preferredLanguages]`
 */
@property(strong) GLMapLocaleSettings *localeSettings;

/**
 Defines visible part of map. Usefull interactive objects like balloons.
 */
- (PlatformEdgeInsets)visibleMapInsets;

@end

NS_ASSUME_NONNULL_END
