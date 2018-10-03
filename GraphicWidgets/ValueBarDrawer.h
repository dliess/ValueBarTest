#ifndef _VALUE_BAR_DRAWER_H
#define _VALUE_BAR_DRAWER_H

#include <cstdint>
#include "FpWidgetOut_Spec.h"
#include "ValueUtils.h"

class DisplayInterface;

class ValueBarDrawer
{
public:
    using ValueType = int32_t;
    ValueBarDrawer(const fpw::Display::Coord&                        upLeft,
                   const fpw::Display::Size2D&                       size,
                   const value_utils::Range<ValueType>&              valueRange,
                   const fpw::Display::ColorRGB&                     frameColor,
                   const value_utils::Range<fpw::Display::ColorRGB>& barColorRange);
    void initialDraw();
    void draw(DisplayInterface& displayInterface, ValueType value, ValueType modulation = 0);

private:
    struct Frame
    {
        Frame(const fpw::Display::Coord&  upLeft_,
              const fpw::Display::Size2D& size_) : upLeft(upLeft_),size(size_){};
        const fpw::Display::Coord  upLeft;
        const fpw::Display::Size2D size;
    };
    bool                                       m_initialDraw;
    Frame                                      m_frame;
    Frame                                      m_bar;
    value_utils::Range<ValueType>              m_valueRange;
    fpw::Display::ColorRGB                     m_frameColor;
    value_utils::Range<fpw::Display::ColorRGB> m_barColorRange;
    static const fpw::Display::ColorRGB        ClearColor;
    static const fpw::Display::Pixel           MidLineHeight = 4;
    fpw::Display::Pixel                        m_valuePosXLast;
    fpw::Display::Pixel                        m_modulatedValuePosXLast;
};

#endif