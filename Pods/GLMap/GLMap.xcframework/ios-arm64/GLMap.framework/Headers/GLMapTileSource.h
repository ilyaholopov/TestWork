//
//  GLMapTileSource.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 4/27/20.
//  Copyright © 2020 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GLMapView;
/**
`GLMapTileSource` is base class for raster and vector tile sources
*/
@interface GLMapTileSource : NSObject

/**
 Called when layer will be attached to map view
 @param mapView map view where layer will be attached
 **/
- (void)willAttachToMapView:(GLMapView *_Nonnull)mapView;

/**
Called when layer will be detached from map view
@param mapView map view from where layer will be detached
**/
- (void)willDetachFromMapView:(GLMapView *_Nonnull)mapView;

@end
