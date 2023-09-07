//
//  GLMapPointArray.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 6/11/19.
//  Copyright © 2019 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Generator block. Returns points for index. Used in generating constructor `-initWithCount:callback:`
 @param index Index of the point
 @return Point to add into the array
 */
typedef GLMapPoint (^GetPointBlock)(NSUInteger index);
/**
 Enumerator block. Called for all points subsequently.
 @param index Point index
 @param point Point
 */
typedef void (^EnumeratePointBlock)(NSUInteger index, GLMapPoint point);

/**
 Array of GLMapPoint. Usesefull to load lines and polygons into GLMapVectorObject. Based on C++ vector and works faster with GLMapPoints without obj-c overhead,
 **/
EXPORT @interface GLMapPointArray : NSObject

/**
 Initialize array with no capacity hint
 */
- (instancetype)init;

/**
 Initialize array with initial capacity hint
 */
- (instancetype)initWithCapacity:(NSUInteger)initialCapacity;

/**
 Initialize array with points
 */
- (instancetype)initWithPoints:(GLMapPoint *)points count:(NSUInteger)count;

/**
 Initialize array with callback. Usefull in case of generated geometerey. Or to convert
 data without creating additional array.
 */
- (instancetype)initWithCount:(NSUInteger)count callback:(GetPointBlock)callback;

/**
 Add points to array
 **/
- (BOOL)addPoints:(const GLMapPoint *_Nonnull)points count:(NSUInteger)count;

/**
 Add one point to array
 */
- (BOOL)addPoint:(GLMapPoint)pt;

/// Point count in array
@property(readonly) NSUInteger count;

/**
 Returns point at index
 @param index Point index
 @return Point value
 */
- (GLMapPoint)pointAtIndex:(NSUInteger)index;

/**
 Enumerates points with block
 @param block Enumerator block
 */
- (void)enumeratePointsWithBlock:(EnumeratePointBlock)block;

@end

NS_ASSUME_NONNULL_END
