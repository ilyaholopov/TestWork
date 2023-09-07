//
//  GLMapImageGroup.h
//  GLMap
//
//  Created by Evgen Bodunov on 3/16/14.
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

#import <GLMap/GLMapDrawObject.h>

/**
 `GLMapImageGroupDataSource` is a callback that provide infromation images.
  @warning Do not edit image group while it is updated
 */
EXPORT @protocol GLMapImageGroupDataSource
/**
 Called at start of updating image group.
 */
- (void)startUpdate;
/**
 Called at end of uparing image group
 */
- (void)endUpdate;

/**
 Returns number of unique images
 */
- (NSInteger)getVariantsCount;

/**
 Returns image.
 @param index index of image in range [0..getVariantsCount)
 @param offset offset of image in points
 */
- (PlatformImage *_Nonnull)getVariant:(NSInteger)index offset:(CGPoint *_Nonnull)offset;

/**
 Returns number of images to draw
 */
- (NSInteger)getImagesCount;

/**
 Fills infromation for image
 @param index index of image in range [0..getImagesCount)
 @param variant index of image to draw in range [0..getVarriantsCount)
 @param position position where to draw image
 */
- (void)getImageInfo:(NSInteger)index vairiant:(uint32_t *_Nonnull)variant position:(GLMapPoint *_Nonnull)position;

@end

/**
 `GLMapImageGroup` is a bridge class, to work with GLMap internal representation of image group.
 Image groups used to display small set of images for the large number of locations. E.g. 1000 locations on map, but only with 10 different images.
 */
EXPORT @interface GLMapImageGroup : GLMapDrawObject

/// Plain -init is disabled
- (instancetype _Nonnull)init __attribute__((unavailable("GLMapImageGroup should be created with - `[GLMapImageGroup initWithCallback: andDrawOrder:]`")));

/**
 Initializes instance of `GLMapImageGroup`
 Not if `GLMapImageGroup` added to many mapViews miltiple updates can happened at one time (`[GLMapImageGroupDataSource startUpdate]` and
 `[GLMapImageGroupDataSource endUpdate]` will be ballanced)
 */
- (instancetype _Nonnull)initWithCallback:(id<GLMapImageGroupDataSource> _Nonnull)callback andDrawOrder:(int)drawOrder;

#pragma mark - Methods
/**
 Starts updating of image group
 @param updateVariants if YES image variants will be updated otherwise only images and there positions will be updated
 */
- (void)setNeedsUpdate:(BOOL)updateVariants;

@end
