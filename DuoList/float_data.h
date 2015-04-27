#ifndef HEADER_FLOAT_DATA
#define HEADER_FLOAT_DATA

#include "object_data.h"
class float_data :
	public object_data
{
private:
	float item = 0.0f;
public:
	float_data(){}
	float_data(float _item) :item(_item){}
	float_data(const float_data&);
	float_data& operator=(const float_data&);
	
	virtual ~float_data(){}

	bool operator==(const float_data&) const;

	virtual istream& input_data(istream&);
	virtual ostream& output_data(ostream&);


	friend istream& operator>>(istream&, float_data&);
	friend ostream& operator<<(ostream&, float_data&);
};

#endif