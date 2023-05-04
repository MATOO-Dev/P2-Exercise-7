#pragma once
#include <stdexcept>
template <class S, class T>
class BinaryRelation {

public:
	virtual bool inRelation(S a, T b) = 0;
	//BinaryRelation<S, T>& getSignletonInstance() {return singletonInstance;}
protected:
	//BinaryRelation<S, T>() 
	//{
	//	if(singletonInstance == nullptr) 
	//		singletonInstance = this; 
	//	else 
	//	{
	//		//note: there are nicer ways to do this, but those are too complicated to be worth it for such a small task
	//		throw std::logic_error("Error: attempting to create a second instance of BinaryRelation singleton\n");
	//	}
	//}
	//~BinaryRelation<S, T>() { delete singletonInstance; }
	//static BinaryRelation<S, T>* singletonInstance;
};

