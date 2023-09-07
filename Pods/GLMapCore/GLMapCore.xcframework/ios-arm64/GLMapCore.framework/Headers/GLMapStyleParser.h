//
//  GLMapStyleParser.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 7/23/20.
//  Copyright © 2020 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class GLMapVectorCascadeStyle;

/**
`GLMapStyleParser` is calss to parse style and analyze result of parsing
*/
EXPORT @interface GLMapStyleParser : NSObject

/**
 Loads resource from path.
 @param path Directory from where resource will be loaded
 @param name Name of resource
 */
+ (GLMapResource)loadResourceFromPath:(NSString *)path name:(NSString *)name;

/**
 Initialize parser without resources
 */
- (instancetype)init;

/**
 Initialize parser with resources stored in bundle
 @param bundle Bundle object with Style.mapcss and images
*/
- (instancetype)initWithBundle:(NSBundle *)bundle;

/**
 Initialize parser with resources stored in paths
 First it tries to find resource in first path, then in second and so on.
 @param paths Paths where style will search for resources
 */
- (instancetype)initWithPaths:(NSArray<NSString *> *)paths;

/**
 Initialize parser with resource block
 @param resourceBlock block that will provide resources
 */
- (instancetype)initWithBlock:(GLMapResourceBlock)resourceBlock;

/// mask to clamp zoom levels
@property(assign) uint32_t clampZoomMask;

/// All options for @if tests found while parsing.
@property(readonly) NSSet<NSString *> *_Nullable allOptions;

/// Error happened while parsing
@property(readonly) NSError *_Nullable error;

/**
 Sets global options. Will be available in all instances of parser.
 @param options values for options
 */
+ (void)setGlobalOptions:(NSDictionary<NSString *, NSString *> *)options;

/**
 Sets style options
 @param options values for options
 @param defaultValue value used for not set options
 */
- (void)setOptions:(NSDictionary<NSString *, NSString *> *)options defaultValue:(BOOL)defaultValue;

/**
 Parses next chunk of style
 @param data chunk of style to parse
 */
- (BOOL)parseNextBuffer:(NSData *)data;

/**
 Parses next chunk of style
 @param string chunk of style to parse
 */
- (BOOL)parseNextString:(NSString *)string;

/**
 Finishes parsing
 @returns returns result of parsing. If error happened returned value is nil. Check error for details
 */
- (GLMapVectorCascadeStyle *_Nullable)finish;

/**
 Appends data from "Style.mapcss" in resources and finish parsing
 @returns returns result of parsing. If error happened returned value is nil. Check error for details
*/
- (GLMapVectorCascadeStyle *_Nullable)parseFromResources;

@end

NS_ASSUME_NONNULL_END
