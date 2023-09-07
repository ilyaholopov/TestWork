//
//  GLMapColor.h
//  GLMap
//
//  Created by Arkadi Tolkun on 12.06.23.
//  Copyright © 2023 Evgen Bodunov. All rights reserved.
//

#ifndef GLMapColor_h
#define GLMapColor_h

#ifdef __cplusplus
extern "C" {
#endif

/// `GLMapColor` is color type based on `uint32_t`
typedef struct GLMapColor {
    /// ABGR color
    uint32_t color;

#ifdef __cplusplus
    bool operator==(GLMapColor b) { return color == b.color; }
    bool operator!=(GLMapColor b) { return color != b.color; }
    bool operator<(GLMapColor b) { return color < b.color; }
    bool operator>(GLMapColor b) { return color > b.color; }
#endif
}
/// :nodoc:
GLMapColor;

/// Equals to GLMapColorMake(0, 0, 0, 0);
CF_SWIFT_NAME(GLMapColor.empty)
extern const GLMapColor GLMapColorEmpty;

/// Equals to GLMapColorMake(0xFF, 0xFF, 0xFF, 0xFF);
CF_SWIFT_NAME(GLMapColor.white)
extern const GLMapColor GLMapColorWhite;

/// Equals to GLMapColorMake(0x00, 0x00, 0x00, 0xFF);
CF_SWIFT_NAME(GLMapColor.black)
extern const GLMapColor GLMapColorBlack;

/**
Blend colors with overlay function
 @param tint tint color
 @param color color to blend
*/
CF_SWIFT_NAME(GLMapColor.blendOverlay(self:color:))
GLMapColor BlendColorsOverlay(GLMapColor tint, GLMapColor color);

/**
 Creates new color from int chanel values 0 - 255

 @param r Red channel value
 @param g Green channel value
 @param b Blue channel value
 @param a Alpha channel value

 @return Returns new color object
 */
CF_SWIFT_NAME(GLMapColor.init(red:green:blue:alpha:))
ConstInline GLMapColor GLMapColorMake(uint8_t r, uint8_t g, uint8_t b, uint8_t a) NoExcept
{
    uint32_t color = ((uint32_t)a << 24u) | ((uint32_t)b << 16u) | ((uint32_t)g << 8u) | (uint32_t)r;
    return (GLMapColor){color};
}

/**
 @param color Input color

 @return Returns red channel value
 */
CF_SWIFT_NAME(getter:GLMapColor.red(self:))
ConstInline uint8_t GLMapColorGetRed(GLMapColor color) NoExcept
{
    return (uint8_t)color.color;
}

/**
 @param color Input color

 @return Returns green channel value
 */
CF_SWIFT_NAME(getter:GLMapColor.green(self:))
ConstInline uint8_t GLMapColorGetGreen(GLMapColor color) NoExcept
{
    return (uint8_t)(color.color >> 8);
}

/**
 @param color Input color

 @return Returns blue channel value
 */
CF_SWIFT_NAME(getter:GLMapColor.blue(self:))
ConstInline uint8_t GLMapColorGetBlue(GLMapColor color) NoExcept
{
    return (uint8_t)(color.color >> 16);
}

/**
 @param color Input color

 @return Returns alpha channel value
 */
CF_SWIFT_NAME(getter:GLMapColor.alpha(self:))
ConstInline uint8_t GLMapColorGetAlpha(GLMapColor color) NoExcept
{
    return (uint8_t)(color.color >> 24);
}

/**
 @param color Input color
 @param value new red value
*/
CF_SWIFT_NAME(setter:GLMapColor.red(self:_:))
ConstInline void GLMapColorSetRed(GLMapColor *_Nonnull color, uint8_t value) NoExcept
{
    color->color = (color->color & 0xFFFFFF00) | value;
}

/**
 @param color Input color
 @param value new green value
*/
CF_SWIFT_NAME(setter:GLMapColor.green(self:_:))
ConstInline void GLMapColorSetGreen(GLMapColor *_Nonnull color, uint8_t value) NoExcept
{
    color->color = (color->color & 0xFFFF00FF) | (value << 8);
}

/**
 @param color Input color
 @param value new blue value
*/
CF_SWIFT_NAME(setter:GLMapColor.blue(self:_:))
ConstInline void GLMapColorSetBlue(GLMapColor *_Nonnull color, uint8_t value) NoExcept
{
    color->color = (color->color & 0xFF00FFFF) | (value << 16);
}

/**
 @param color Input color
 @param value new alpha value
*/
CF_SWIFT_NAME(setter:GLMapColor.alpha(self:_:))
ConstInline void GLMapColorSetAlpha(GLMapColor *_Nonnull color, uint8_t value) NoExcept
{
    color->color = (color->color & 0x00FFFFFF) | (value << 24);
}

/**
 Creates new color from float chanel values 0.0 - 1.0

 @param r Red channel value
 @param g Green channel value
 @param b Blue channel value
 @param a Alpha channel value

 @return Returns new color object
 */
ConstInline GLMapColor GLMapColorMakeF(float r, float g, float b, float a) NoExcept
{
    return GLMapColorMake((uint8_t)(r * 255), (uint8_t)(g * 255), (uint8_t)(b * 255), (uint8_t)(a * 255));
}

/**
 @param color Input color

 @return Returns red channel value
 */
CF_SWIFT_NAME(getter:GLMapColor.redF(self:))
ConstInline float GLMapColorGetRedF(GLMapColor color) NoExcept
{
    return (float)GLMapColorGetRed(color) / 255.0f;
}

/**
 @param color Input color

 @return Returns green channel value
 */
CF_SWIFT_NAME(getter:GLMapColor.greenF(self:))
ConstInline float GLMapColorGetGreenF(GLMapColor color) NoExcept
{
    return (float)GLMapColorGetGreen(color) / 255.0f;
}

/**
 @param color Input color

 @return Returns blue channel value
 */
CF_SWIFT_NAME(getter:GLMapColor.blueF(self:))
ConstInline float GLMapColorGetBlueF(GLMapColor color) NoExcept
{
    return (float)GLMapColorGetBlue(color) / 255.0f;
}

/**
 @param color Input color

 @return Returns alpha channel value
 */
CF_SWIFT_NAME(getter:GLMapColor.alphaF(self:))
ConstInline float GLMapColorGetAlphaF(GLMapColor color) NoExcept
{
    return (float)GLMapColorGetAlpha(color) / 255.0f;
}

#ifdef __OBJC__
/**
 Creates `CGColor` object from our `GLMapColor`

 @param color Initial color
 @return New `CGColor` object
 */
struct CGColor *_Nullable CGColorFromGLMapColor(GLMapColor color);
#endif

#ifdef __cplusplus
}
#endif

#endif /* GLMapColor_h */
