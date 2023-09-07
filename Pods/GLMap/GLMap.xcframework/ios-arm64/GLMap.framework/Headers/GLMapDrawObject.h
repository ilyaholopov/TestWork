//
//  GLMapDrawObject.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 9/12/17.
//  Copyright © 2017 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * `GLMapDrawObject` is a base class for GLMapDrawable, GLMapTrack, GLMapMarkerLayer, GLMapImageGroup
 */
EXPORT @interface GLMapDrawObject : NSObject

/**
 Draw order of object.
 */
@property(readonly) int drawOrder;

/**
 A Boolean value that determines whether the object is hidden. Default value is 'NO'
 */
@property(assign) BOOL hidden;

@end
