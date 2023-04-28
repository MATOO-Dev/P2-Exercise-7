#pragma once
template <class S, class T>
class BinaryRelation {

public:
	virtual bool inRelation(S a, T b) = 0;
};

