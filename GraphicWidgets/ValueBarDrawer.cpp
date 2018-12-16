#include "ValueBarDrawer.h"
#include "DisplayRenderInterface.h"
#include "RenderIf.h"

#include <iostream>

const ColorRGB ValueBarDrawer::ClearColor = {0,0,0};


ValueBarDrawer::ValueBarDrawer( const gfxbase::Coord&                        upLeft,
                                const gfxbase::Size2D&                       size,
                                const value_utils::Range<ValueType>&              valueRange,
                                const ColorRGB&                     frameColor,
                                const value_utils::Range<ColorRGB>& barColorRange  ) :
    m_initialDraw(true),
    m_frame(upLeft, size),
    m_bar({upLeft.x + 1, upLeft.y + 1}, {size.w - 2, size.h - 2}),
    m_valueRange(valueRange),
    m_frameColor(frameColor),
    m_barColorRange(barColorRange),
    m_valuePosXLast(0),
    m_modulatedValuePosXLast(0)
{
}

void ValueBarDrawer::initialDraw()
{
    m_initialDraw = true;
}

void ValueBarDrawer::draw(RenderIf& r, ValueType value, ValueType modulation)
{
    if(m_initialDraw)
    {
        m_initialDraw = false;
        r.drawRectangle( gfxbase::Rectangle(
                                            gfxbase::Coord(m_frame.upLeft.x, m_frame.upLeft.y-6),
                                            gfxbase::Size2D(m_frame.size.w, m_frame.size.h + 12)),
                                        {0,0,0},
                                        true);
        r.drawRectangle( gfxbase::Rectangle(m_frame.upLeft, m_frame.size),
                                        m_frameColor,
                                        false);
    }
    value_utils::limitToRange(value, m_valueRange);
    const value_utils::Range<gfxbase::Pixel> barLengthPix(0, m_bar.size.w - 1);
    auto valuePosX = value_utils::mapValue(value, m_valueRange, barLengthPix);

    ValueType modulatedValue = value + modulation;
    value_utils::limitToRange(modulatedValue, m_valueRange);

    gfxbase::Pixel modulatedValuePosX = value_utils::mapValue(modulatedValue, m_valueRange, barLengthPix);

    if (modulatedValuePosX > m_modulatedValuePosXLast)
    {
        for (gfxbase::Pixel i = m_modulatedValuePosXLast; i <= modulatedValuePosX; ++i)
        {
            const int Xpos = m_bar.upLeft.x + i;
            ColorRGB lineColor(
                value_utils::mapValue(i, barLengthPix, value_utils::Range<uint8_t>(m_barColorRange.min.r(), m_barColorRange.max.r())),
                value_utils::mapValue(i, barLengthPix, value_utils::Range<uint8_t>(m_barColorRange.min.g(), m_barColorRange.max.g())),
                value_utils::mapValue(i, barLengthPix, value_utils::Range<uint8_t>(m_barColorRange.min.b(), m_barColorRange.max.b()))   
            );
            r.drawLine(  gfxbase::Coord( Xpos, m_bar.upLeft.y ),
                                        gfxbase::Coord( Xpos, m_bar.upLeft.y + m_bar.size.h - 1 ),
                                        lineColor  );
        }
    }
    else if (modulatedValuePosX < m_modulatedValuePosXLast)
    {
        for (int i = m_modulatedValuePosXLast; i > modulatedValuePosX; --i)
        {
            const int Xpos = m_bar.upLeft.x + i;
            r.drawLine(  gfxbase::Coord( Xpos, m_bar.upLeft.y ),
                                        gfxbase::Coord( Xpos, m_bar.upLeft.y + m_bar.size.h - 1 ),
                                        ClearColor );
        }
    }

    if (valuePosX != m_valuePosXLast)
    {
        const int XposNew = m_bar.upLeft.x + valuePosX;
        const int XposOld = m_bar.upLeft.x + m_valuePosXLast;
        r.drawVLine( gfxbase::Coord(XposOld, m_frame.upLeft.y - MidLineHeight),
                                    MidLineHeight,
                                    ClearColor);
        r.drawVLine( gfxbase::Coord(XposNew, m_frame.upLeft.y - MidLineHeight),
                                    MidLineHeight,
                                    m_frameColor);
        r.drawVLine( gfxbase::Coord(XposOld, m_frame.upLeft.y + m_frame.size.h),
                                    MidLineHeight,
                                    ClearColor);
        r.drawVLine( gfxbase::Coord(XposNew, m_frame.upLeft.y + m_frame.size.h),
                                    MidLineHeight,
                                    m_frameColor);
    }
    m_modulatedValuePosXLast = modulatedValuePosX;
    m_valuePosXLast = valuePosX;
}
