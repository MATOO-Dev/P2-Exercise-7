#include "BinaryRelation.h"

class InOrderIntRelation : public BinaryRelation<unsigned int, unsigned int>
{
	inline bool inRelation(unsigned int a, unsigned int b)
    {
        return a <= b;
    }
};