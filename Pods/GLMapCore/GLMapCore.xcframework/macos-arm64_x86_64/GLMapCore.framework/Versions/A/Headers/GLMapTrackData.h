//
//  GLMapTrackData.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 2/8/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#import <GLMapCore/GLMapCoreTypes.h>

@class GLMapView;

/**
 Block is called to get point of track at given `index`
 @return YES if there is point at index `index`, and NO if there is no points.
 */
typedef BOOL (^GLMapTrackPointsCallback)(NSUInteger index, GLTrackPoint *_Nonnull pt);

/**
 `GLMapTrackData` class holds data for track and information to optimize draw at different zoom levels. Data stored without connection to mapView and could be
 added on different `GLMapView` at the same time.
 */
EXPORT @interface GLMapTrackData : NSObject

/**
 Not used.
 */
- (instancetype _Nonnull)init __attribute__((unavailable("Please use inits with data.")));

/**
 Initalizes `GLMapTrackData` with big circle line from `start` to `end`. Useful to display plane routes.
 @param color Track color
 @param start Start point
 @param end End point
 @param quality Maximum distance from point to line, used for simplification in Douglas Peucker algorithm. Units is map internal coordinates.
 */
- (instancetype _Nullable)initWithColor:(GLMapColor)color start:(GLMapGeoPoint)start end:(GLMapGeoPoint)end quality:(double)quality;

/**
 Initalizes `GLMapTrackData` with array of points

 @param points Track point array
 @param count Size of point array

 @return A new track data object
 */
- (instancetype _Nullable)initWithPoints:(const GLTrackPoint *_Nonnull)points count:(NSUInteger)count;

/**
 Initializes `GLMapTrackData` with points that retured by `pointsCallback`

 @param pointsCallback Callback block used to fill track points data
 @param count Number of times callback is called. If zero callback will be called until it will return NO

 @return A new track data object
 */
- (instancetype _Nullable)initWithPointsCallback:(GLMapTrackPointsCallback _Nonnull)pointsCallback count:(NSUInteger)count;

/**
 Copies points from given `GLMapTrackData` and merges segments if needed.

 @param data Source object with points
 @param mergeSegments If YES, it tries to merge line segments into single line during construction. Otherwise it just retains `data` contents.

 @return A new track data object
 */
- (instancetype _Nullable)initWithData:(GLMapTrackData *_Nonnull)data mergeSegments:(BOOL)mergeSegments;

/**
 Copies points from given `GLMapTrackData` and add new point to track.

 When frequently updated track is displayed is a good idea to add new points into small segments. Up to 100 points per segment. And then merge segments
 together. Track uses optimized Ramer-Douglas-Peucker, but it's still can have O(n^2) complexity in worst case. With described solution GLMap could record
 tracks up to million points.

 @param data Source object with points
 @param pt New point to be added
 @param startNewSegment If YES new segment will be created

 @return A new track data object
 */
- (instancetype _Nullable)initWithData:(GLMapTrackData *_Nonnull)data andNewPoint:(GLTrackPoint)pt startNewSegment:(BOOL)startNewSegment;

/**
 Creates new copy of track data with merged segments that have same start/end points.

 @return A new track data object
 */
- (instancetype _Nullable)trackDataWithMergedSegments;

/**
 @return Bounding box of track
 */
- (GLMapBBox)bbox;

/**
 @return `YES` if track have no points
 */
- (BOOL)isEmpty;

/**
 @return Count of lines inside this GLMapTrackData
 */
- (size_t)segmentCount;

/**
 Calculate length of all track segments
 @return length of all segments
 */
- (double)calculateLength;

/**
 Sample track at locations
 @param locations locations where to sample track (distances from start of track)
 @param count number of points to sample
 @param result result of sampling
 */
- (uint32_t)sample:(const double *_Nonnull)locations count:(uint32_t)count result:(GLTrackSampleResult *_Nonnull)result;

/**
 Find nearest point to track and return progressIndex
 @param point refrence point to calculate distance
 @param nearestPoint nearestPoint on track or nil if not needed
 @return progressIndex of nearest point
 */
- (double)findProgressByPoint:(GLMapPoint)point nearestPoint:(GLMapPoint *_Nullable)nearestPoint;

@end
