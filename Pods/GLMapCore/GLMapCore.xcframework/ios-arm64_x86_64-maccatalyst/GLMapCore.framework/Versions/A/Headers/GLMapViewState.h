//
//  GLMapViewState.h
//  GLMapCore
//
//  Created by Arkadiy Tolkun on 10.12.21.
//  Copyright © 2021 Evgen Bodunov. All rights reserved.
//

#import <GLMapCore/GLMapCore.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Class that holds state of map view (like map position, locale settings, map style)
 */
EXPORT @interface GLMapViewState : NSObject

/// Plain -init is disabled
- (instancetype _Nonnull)init __attribute__((unavailable("GLMapViewState returned by `[GLMapView state]`")));

/**
Updates draw attributes of vector object with style of mapView.
@mapView view where object is displayed
@return true if visible
*/
- (BOOL)updateDrawAttributesOfVectorObject:(GLMapVectorObject *)object;

/**
 Finds nearest point of track, to given point. Useful to find nearest point of track whe user tap.

 @param point Point on map. If point was found this value will be set to nearest point
 @param distance Max distance from track allowed

 @return YES if point found, otherwise NO.
 */
- (BOOL)findNearestPoint:(GLMapPoint *_Nonnull)point nearTrack:(GLMapTrackData *_Nonnull)trackData maxDistance:(CGFloat)distance;

@end

NS_ASSUME_NONNULL_END
