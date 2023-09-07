//
//  GLMapAnimation.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 9/12/17.
//  Copyright © 2017 Evgen Bodunov. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <GLMapCore/GLMapCoreTypes.h>

@class GLMapDrawable;
@class GLMapView;

/// `GLMapAnimationCompletionBlock` called when animation ends. `finished` set to YES, when animation is finished, and NO when animation is cancelled.
typedef void (^GLMapAnimationCompletionBlock)(BOOL finished);

/**
 * `GLMapAnimation` defines animation of objects parameters that will be executed synchronously.
 */
EXPORT @interface GLMapAnimation : NSObject

/**
 Initializes GLMapAnimation
 */
- (instancetype)initWithCompletion:(GLMapAnimationCompletionBlock)completion;

/**
 Transition of animation. Default transition is Ease In - Ease Out
 */
@property(assign) GLMapTransitionFunction transition;

/**
 Duration of animation. Default duration is 0.5 seconds.
 */
@property(assign) double duration;

/**
 Focus point of zoom and rotate animations
 */
@property(assign) GLMapPoint focusPoint;

/**
 If YES flyTo animation will be used if new mapCenter is set and previous flyTo animation is not finished yet. Default value YES.
 */
@property(assign) BOOL continueFlyTo;

/**
 * Sets new position of drawable
 * @param drawable drawable to modify
 * @param position new position
 */
- (void)setPosition:(GLMapPoint)position forDrawable:(GLMapDrawable *)drawable;

/**
 * Sets new scale of drawable
 * @param drawable drawable to modify
 * @param scale new scale
 */
- (void)setScale:(double)scale forDrawable:(GLMapDrawable *)drawable;

/**
 * Sets new angle of drawable
 * @param drawable drawable to modify
 * @param angle new angle
 */
- (void)setAngle:(float)angle forDrawable:(GLMapDrawable *)drawable;

/**
 * Sets new offset of drawable
 * @param offset new offset
 * @param drawable drawable to modify
 */
- (void)setOffset:(CGPoint)offset forDrawable:(GLMapDrawable *)drawable;

/**
 Moves to new center with animation optimized for long distances.
 @param point Target location.
 */
- (void)flyToPoint:(GLMapPoint)point;

/**
 Moves to new center with animation optimized for long distances.
 @param geoPoint Target location.
 */
- (void)flyToGeoPoint:(GLMapGeoPoint)geoPoint;

/**
 Uses "fly to" animation to change map position and zoom.
 */
- (void)useFlyTo;

/**
 Defines the scrolling speed at the end of map scrolling movement.

 @param velocity Initial velocity of deceleration
 */
- (void)decelerate:(GLMapPoint)velocity;

/**
 Cancels anmation
 @param setFinalValues if YES aimatied values will be set to it's final values.
 */
- (void)cancel:(BOOL)setFinalValues;

@end
