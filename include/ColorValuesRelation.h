#include "BinaryRelation.h"
#include "Color.h"

class ColorValuesRelation : public BinaryRelation<Color, Color>
{
	inline bool inRelation(Color a, Color b)
    {
        //not 100% sure what is wanted here, so this is just a guess:
        //first check red, then green, then blue
        //if all three are smaller, return true, else false
        //however, this is almost the same as sorting by brightness, so its probably not the desired solution

        bool redRelation = a.getRed() <= b.getRed();
        bool greenRelation = a.getGreen() <= b.getGreen();
        bool blueRelation = a.getBlue() <= b.getBlue();

        return redRelation && greenRelation && blueRelation;
    }
};