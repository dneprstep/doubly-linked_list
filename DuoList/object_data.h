#ifndef HEADER_OBJECT_DATA
#define HEADER_OBJECT_DATA

#include <iostream>

using std::ostream; using std::istream;

class object_data
{
private:
	void* item;
public:
	object_data(){}
	
	///////////////////////////////////////////////////////////////
	//we need this functions to realise iostream 
	//operators "<<" and ">>" in inherited class
	//  
	virtual ostream& output_data(ostream&) = 0;
	virtual istream& input_data(istream&) = 0;
	/////////////////////////////////////////////////////////////


	virtual ~object_data(){}

	friend ostream& operator<<(ostream&, object_data&);
	friend istream& operator>>(istream&, object_data&);
};


#endif