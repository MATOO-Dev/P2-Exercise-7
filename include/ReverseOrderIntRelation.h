#include "BinaryRelation.h"

class ReverseOrderIntRelation : public BinaryRelation<unsigned int, unsigned int>
{
	inline bool inRelation(unsigned int a, unsigned int b)
    {
        return a >= b;
    }
};