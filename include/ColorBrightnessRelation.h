#include "BinaryRelation.h"
#include "Color.h"

class ColorBrightnessRelation : public BinaryRelation<Color, Color>
{
	inline bool inRelation(Color a, Color b)
    {
        int aBrightness = (a.getRed() + a.getGreen() + a.getBlue()) / 3;
        int bBrightness = (b.getRed() + b.getGreen() + b.getBlue()) / 3;
        return (aBrightness <= bBrightness);
    }
};