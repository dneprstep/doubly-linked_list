#include "float_data.h"

float_data::float_data(const float_data& obj)
{
	if (*this == obj)
		return;
	*this = obj;
}
float_data& float_data::operator=(const float_data& obj)
{
	if (*this == obj)
		return *this;

	this->item = obj.item;
	return *this;
}

bool float_data::operator==(const float_data& obj) const
{
	return this->item == obj.item ? true : false;
}


ostream& float_data::output_data(ostream& out)
{
	return out << this->item;
}
istream& float_data::input_data(istream& in)
{
	bool success = false;
	while (!success)
	{
		in >> this->item;
		if (in.good())
			success = true;
		else
		{
			std::cout << "\tWrong input symbols. Repeat please.\n";
			in.clear();
			in.ignore(in.rdbuf()->in_avail());
		}

	}
	return in;
}


ostream& operator<<(ostream& out, float_data& obj)
{
	//check stream flag and clear it
	if (out.rdstate() != std::ios_base::goodbit)
		out.clear();
	out.flush();

	obj.output_data(out);

	if (out.rdstate() != std::ios_base::goodbit)
		out.clear();
	out.flush();

	return out;
}

istream& operator>>(istream& in, float_data& obj)
{
	//check stream flag and clear it
	if (in.rdstate() != std::ios_base::goodbit)
		in.clear();
	in.ignore(in.rdbuf()->in_avail());

	obj.input_data(in);

	in.ignore(in.rdbuf()->in_avail());
	if (in.rdstate() != std::ios_base::goodbit)
		in.clear();

	return in;
}

