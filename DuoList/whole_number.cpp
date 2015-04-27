#include "whole_number.h"

whole_number::whole_number(const whole_number& obj)
{
	if (*this == obj)
		return;
	*this = obj;
}
whole_number& whole_number::operator=(const whole_number& obj)
{
	if (*this == obj)
		return *this;

	this->item = obj.item;
	return *this;
}


bool whole_number::operator==(const whole_number& obj) const
{
	return this->item == obj.item ? true : false;
}

ostream& whole_number::output_data(ostream& out)
{
	return out << this->item;
}
istream& whole_number::input_data(istream& in)
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

ostream& operator<<(ostream& out, whole_number& obj)
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
istream& operator>>(istream& in, whole_number& obj)
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
