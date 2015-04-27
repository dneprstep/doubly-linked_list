#include "object_data.h"

ostream& operator<<(ostream& out, object_data& obj)
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
istream& operator>>(istream& in, object_data& obj)
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


ostream& object_data::output_data(ostream& out)
{
	return out << this->item;
}
istream& object_data::input_data(istream& in)
{
	return in >> this->item;
}
