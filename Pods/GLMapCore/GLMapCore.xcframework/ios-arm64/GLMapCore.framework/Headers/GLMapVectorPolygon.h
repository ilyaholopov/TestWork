//
//  GLMapVectorPolygon.h
//  GLMap
//
//  Created by Arkadi Tolkun on 6.06.23.
//  Copyright © 2023 Evgen Bodunov. All rights reserved.
//

#import <GLMapCore/GLMapVectorObject.h>

NS_ASSUME_NONNULL_BEGIN

@class GLMapVectorLine;

EXPORT @interface GLMapVectorPolygon : GLMapVectorObject

/**
 Creates vector object with polygon
 @param outerRings exterior of polygon
 @param innerRings holes of polygon
 */
- (instancetype)init:(NSArray<GLMapPointArray *> *)outerRings innerRings:(NSArray<GLMapPointArray *> *_Nullable)innerRings;

/**
 Create outline of polygon
 @return outline of polygon
 */
- (GLMapVectorLine *)buildOutline;

@end

NS_ASSUME_NONNULL_END
