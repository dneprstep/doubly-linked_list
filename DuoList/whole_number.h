#ifndef HEADER_WHOLE_NUMBER
#define HEADER_WHOLE_NUMBER

#include "object_data.h"
class whole_number :
	public object_data
{
private:
	int item = 0;
public:
	whole_number(){}
	whole_number(int _item) :item(_item){}
	whole_number(const whole_number&);
	whole_number& operator=(const whole_number&);

	virtual ~whole_number(){}
	
	bool operator==(const whole_number&) const;

	virtual istream& input_data(istream&);
	virtual ostream& output_data(ostream&);


	friend istream& operator>>(istream&, whole_number&);
	friend ostream& operator<<(ostream&, whole_number&);
};


#endif