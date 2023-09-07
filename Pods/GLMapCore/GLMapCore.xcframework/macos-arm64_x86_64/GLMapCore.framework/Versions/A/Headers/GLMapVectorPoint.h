//
//  GLMapVectorPoint.h
//  GLMap
//
//  Created by Arkadi Tolkun on 6.06.23.
//  Copyright © 2023 Evgen Bodunov. All rights reserved.
//

#import <GLMapCore/GLMapVectorObject.h>

NS_ASSUME_NONNULL_BEGIN

EXPORT @interface GLMapVectorPoint : GLMapVectorObject

/**
 Creates vector object with point.
 @param point Point on the map.
 */
- (instancetype)init:(GLMapPoint)point;

@end

NS_ASSUME_NONNULL_END
