#ifndef _VALUE_BAR_DRAWER_H
#define _VALUE_BAR_DRAWER_H

#include <cstdint>
#include "FpWidgetOut_Spec.h"
#include "ValueUtils.h"
#include "GfxTypes.h"
#include "ColorRGB.h"

class RenderIf;

class ValueBarDrawer
{
public:
    using ValueType = int32_t;
    ValueBarDrawer(const gfxbase::Coord&                        upLeft,
                   const gfxbase::Size2D&                       size,
                   const value_utils::Range<ValueType>&              valueRange,
                   const ColorRGB&                     frameColor,
                   const value_utils::Range<ColorRGB>& barColorRange);
    void initialDraw();
    void draw(RenderIf& r, ValueType value, ValueType modulation = 0);

private:
    struct Frame
    {
        Frame(const gfxbase::Coord&  upLeft_,
              const gfxbase::Size2D& size_) : upLeft(upLeft_),size(size_){};
        const gfxbase::Coord  upLeft;
        const gfxbase::Size2D size;
    };
    bool                                       m_initialDraw;
    Frame                                      m_frame;
    Frame                                      m_bar;
    value_utils::Range<ValueType>              m_valueRange;
    ColorRGB                     m_frameColor;
    value_utils::Range<ColorRGB> m_barColorRange;
    static const ColorRGB        ClearColor;
    static const gfxbase::Pixel           MidLineHeight = 4;
    gfxbase::Pixel                        m_valuePosXLast;
    gfxbase::Pixel                        m_modulatedValuePosXLast;
};

#endif