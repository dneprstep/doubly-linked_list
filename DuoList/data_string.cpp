#include "data_string.h"

data_string::data_string(char *str) :size(0), _fill(0)
{
	if (str == NULL)
		return;
	char * tmp = str;
	while (*tmp++ != '\0') this->size++;

	this->str = new char[this->size + 1];
	if (this->str == NULL)
		throw("Error alloc memory");

	tmp = str;
	for (size_t i = 0; i<=this->size; i++, tmp++)
		this->str[i] = *tmp;

	this->_fill = this->lenght();

	Head(this->str);
	Last(this->str + this->fill());
	Tail(this->str + this->lenght());
}
data_string::data_string(const data_string& obj)
{
	if (*this == obj)
		return;
	*this = obj;

	Head(this->str);
	Last(this->str + this->fill());
	Tail(this->str + this->lenght());
}

size_t data_string::str_len(const char *cpy_str)
{
	size_t count;
	for (count = 0; cpy_str[count] != '\0'; count++);
	return count;
}

void data_string::push_back(char symbol)
{
	if (!free_space())
		//add additional space (member: realloc_step) if full
		resize(this->fill() + this->realloc_step);

	this->str[this->fill()] = symbol;	
	_fill++;
	this->str[this->fill()] = '\0';

	Last(this->str + this->fill());
}

int data_string::find_char(const char& ch, const size_t& index)
{
	if (this->fill()>0)
	{
		for (size_t i = index; i < this->fill(); i++)
		{
			if (this->str[i] == ch)
				return i;
		}
	}
	return -1;
}

void data_string::clean_up()
{
	if (this->str != NULL)
		delete[]this->str;
	this->size = 0;
	this->_fill = 0;

	Head(NULL);
	Last(NULL);
	Tail(NULL);
}

void data_string::resize(const size_t& s)
{
	if (s == 0)
	{
		clean_up();
		return;
	}

	char *cur_temp = this->str;
	size_t old_size = this->size;

	this->size = s;

	this->str = new char[this->size + 1];
	if (this->str == NULL) 
		throw("Error alloc memory");

	for (size_t i = 0; i <= old_size && i < this->lenght(); i++)
		this->str[i] = cur_temp[i]; 
		
	this->_fill = old_size>this->lenght() ? this->lenght() : this->fill();

	this->str[this->fill()] = '\0';
	
	delete[] cur_temp;

	Head(this->str);
	Last(this->str + this->fill());
	Tail(this->str + this->lenght());
}

char& data_string::operator[](const size_t i)
{
	if (i < this->fill())
		return str[i];
	else
		throw("Out of range");
}

char data_string::front() const
{
	return *str;
}
char data_string::back() const
{
	return *(str + fill() - 1);
}

data_string& data_string::operator=(char * new_string)
{
	if (!new_string)
		throw("Error memory alloc");

	clean_up();

	char *temp = new_string;

	while (*temp++ != '\0') this->size++;

	this->str = new char[this->size + 1];
	if (this->str == NULL)
		throw("Error Alloc memory");

	temp = new_string;
	for (size_t i = 0; i<=this->lenght(); i++)
		this->str[i] = temp[i];

	this->_fill = this->lenght();

	Head(this->str);
	Last(this->str + this->fill());
	Tail(this->str + this->lenght());

	return *this;
}
data_string& data_string::operator=(const data_string& obj)
{
	if (this->str == obj.str)
		return *this;

	clean_up();

	this->size = obj.lenght();
	this->_fill = obj.fill();

	this->str = new char[this->size + 1];
	if (this->str == NULL)
		throw("Error Alloc memory");

	for (size_t i = 0; i <= this->lenght(); i++)
		this->str[i] = obj.str[i];

	Head(this->str);
	Last(this->str + this->fill());
	Tail(this->str + this->lenght());

	return *this;
}

data_string data_string::operator+(char *cpy_str)
{
	if (!cpy_str)
		throw("Empty operator+ char*");

	char *temp = cpy_str;
	size_t cpy_str_size = 0;

	while (*temp++ != '\0') cpy_str_size++;

	data_string return_data_string(*this);

	return_data_string.resize(return_data_string.fill() + cpy_str_size);

	temp = cpy_str;

	for (size_t i = return_data_string.fill(); i <= return_data_string.lenght(); i++)
		return_data_string.str[i] = *temp++;

	return_data_string._fill += cpy_str_size;
	
	return_data_string.Head(return_data_string.str);
	return_data_string.Last(return_data_string.str + return_data_string.fill());
	return_data_string.Tail(return_data_string.str + return_data_string.lenght());

	return return_data_string;
}
data_string data_string::operator+(const data_string& obj)
{
	data_string return_data_string(*this);

	return_data_string = return_data_string + obj.str;

	return return_data_string;
}
data_string& operator+(char* str, data_string& obj)
{
	if (!str)
		return obj;

	char *temp = str;

	size_t size_str = 0;
	while (*temp++ != '\0') size_str++;
	temp = str;

	obj.resize(obj.fill() + size_str);

	for (size_t i = obj.fill(); i<=obj.lenght(); i++)
		obj.str[i] = *temp++;

	obj._fill += size_str;
	
	obj.Head(obj.str);
	obj.Last(obj.str + obj.fill());
	obj.Tail(obj.str + obj.lenght());

	return obj;
}

data_string& data_string::operator+=(char *cpy_str)
{
	if (cpy_str == NULL)
		return *this;
	*this = *this + cpy_str;

	return *this;
}
data_string& data_string::operator+=(const data_string& obj)
{
	*this = *this + obj;
	return *this;
}

bool data_string::operator==(const char *cpy_str) const
{
	if (!cpy_str)
		return false;

	size_t cpy_size = 0;

	for (size_t i = 0; cpy_str[i] != '\0'; i++)
		cpy_size++;

	if (this->lenght() != cpy_size)
		return false;

	for (size_t i = 0; i<cpy_size; i++)
		if (this->str[i] != cpy_str[i])
			return false;

	return true;
}
bool data_string::operator==(const data_string& obj) const
{
	if (this->lenght() != obj.lenght())
		return false;
	for (size_t i = 0; i<this->lenght(); i++)
		if (this->str[i] != obj.str[i])
			return false;
	return true;
}
bool data_string::operator!=(const char *cpy_str) const
{
	return (*this) == cpy_str ? false : true;
}
bool data_string::operator!=(const data_string& obj) const
{
	return (*this) == obj ? false : true;
}


ostream& operator <<(ostream& stream, const data_string& obj)
{
	//check stream flag and clear it
	if (stream.rdstate() != std::ios_base::goodbit)
		stream.clear();
	stream.flush();

	for (size_t i = 0; i<obj.fill(); i++)
		stream  << obj.str[i] ;

	if (stream.rdstate() != std::ios_base::goodbit)
		stream.clear();
	stream.flush();

	return stream;
}

istream& operator >>(istream& stream, data_string& obj)
{
	//check stream flag and clear it
	if (stream.rdstate() != std::ios_base::goodbit)
		stream.clear();
	stream.ignore(stream.rdbuf()->in_avail());

	char symbol=' ';
	while ((symbol = stream.get()) != '\n')
	{
		obj.push_back(symbol);
	}

	stream.ignore(stream.rdbuf()->in_avail());
	if (stream.rdstate() != std::ios_base::goodbit)
		stream.clear();
	return stream;
}
