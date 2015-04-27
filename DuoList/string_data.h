#ifndef HEADER_STRING_DATA
#define HEADER_STRING_DATA

#include "object_data.h"
#include "data_string.h"

class string_data :
	public object_data
{
private:
	data_string item = ""; //"string" object
public:
	string_data(){}
	string_data(data_string _item) :item(_item){}
	string_data(const string_data&);
	string_data& operator=(const string_data&);


	bool operator==(const string_data&) const;

	virtual istream& input_data(istream&);
	virtual ostream& output_data(ostream&);

	virtual ~string_data(){}
	
	friend istream& operator>>(istream&, string_data&);
	friend ostream& operator<<(ostream&, string_data&);
};

#endif