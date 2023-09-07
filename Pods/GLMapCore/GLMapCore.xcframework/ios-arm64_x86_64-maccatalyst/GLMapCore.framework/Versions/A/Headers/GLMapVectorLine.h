//
//  GLMapVectorLine.h
//  GLMap
//
//  Created by Arkadi Tolkun on 6.06.23.
//  Copyright © 2023 Evgen Bodunov. All rights reserved.
//

#import <GLMapCore/GLMapVectorObject.h>

NS_ASSUME_NONNULL_BEGIN

EXPORT @interface GLMapVectorLine : GLMapVectorObject

/**
 Data previously loaded by <code>-[GLMapVectorObject initWithMultiline:]</code>
 */
@property(readonly) NSArray<GLMapPointArray *> *lines;

/**
 Creates vector object with line
 @param line line
 */
- (instancetype)initWithLine:(GLMapPointArray *)line;

/**
 Creates vector object with multiline
 @param lines Multiline
 */
- (instancetype)initWithLines:(NSArray<GLMapPointArray *> *)lines;

/**
 Creates vector object with big circle line from `start` to `end`. Useful to display plane routes.
 @param start Start point
 @param end End point
 @param quality Maximum distance from point to line, used for simplification in Douglas Peucker algorithm. Units is map internal coordinates.
 */
- (instancetype)initGeoStart:(GLMapGeoPoint)start end:(GLMapGeoPoint)end quality:(double)quality;

@end

NS_ASSUME_NONNULL_END
