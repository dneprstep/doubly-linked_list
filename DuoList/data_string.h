#ifndef HEADER_DATA_STRING
#define HEADER_DATA_STRING
#include <iostream>

using std::ostream; using std::istream;

class data_string
{
public:
	///////////////////////////////
	// iterator simulation
	class iterator
	{
	private:
		char *data;
	public:
		iterator() :data(NULL) {}
		iterator(char *i) :data(i) {}
		
		void operator++()
		{
			if (*data == '\0')
				return;
			else
				data++;
		}
		void operator--()
		{
			char* temp = data;
			if (--temp==NULL)
				return;
			else
				--data;
		}
		char operator*()
		{
			if (data != NULL && *data != '\0')
				return *data;
		}
		void operator()(char *ch)
		{
			if (ch != NULL) data = ch;
		}
		iterator& operator=(const iterator& obj)
		{
			if (this->data == obj.data) return *this;
			else
			{
				this->data = obj.data;
				return *this;
			}
		}
		~iterator(){ data = NULL; }
	};

	///////////////////////////////
	//Constructors
	data_string() :size(0), _fill(0), str(NULL), Head(NULL), Tail(NULL), Last(NULL) {}
	data_string(char*);
	data_string(const data_string&);
	////////////////////////////////

	virtual ~data_string()
	{
		clean_up();
	}
	
	//////////////////////////////

	char& operator[](const size_t);


	size_t lenght()const { return size; }

	//return real fill of object
	size_t fill() const { return _fill; }

	bool empty() const
	{	return this->fill() == 0 ? true : false;	}
	
	////////////////////////////////////////
	//resize object
	//data lost if new size shorter than old
	void resize(const size_t&);

	/////////////////////////////////////////
	//clean all data in object
	void clean_up();

	//////////////////////////////////////////////////
	//find index of searching symbol. start with index
	int find_char(const char&, const size_t& index = 0);

	///////////////////////////////////////////
	//          add symbol
	void push_back(char);


	//////////////////////////////////////////////////////
	//
	//     arithmetic and lexicographically operations
	data_string& operator=(const data_string& obj);
	data_string& operator=(char *);

	data_string operator+(const data_string&);
	data_string operator+(char*);

	data_string& operator+=(char*);
	data_string& operator+=(const data_string&);

	bool operator==(const char*) const;
	bool operator==(const data_string&) const;

	bool operator!=(const char *) const;
	bool operator!=(const data_string&) const;
	
	friend data_string& operator+(char* str, data_string& obj);

	/////////////////////////////////////////////////////


	//requires empty()==false, otherwise result undefined
	char front() const;
	char back() const;


	///////////////////////////////////////////////////
	// get Iterators
	iterator getHead() { return Head; }
	iterator getTail() { return Tail; }
	//////////////////////////////////////////////////

	friend ostream& operator <<(ostream&, const data_string&);
	friend istream& operator >>(istream&, data_string&);


	void set_realloc_size(size_t new_realloc)
	{	this->realloc_step = new_realloc;	}
	size_t get_realloc_size() const
	{	return this->realloc_step;	}

private:

	size_t realloc_step = 5;

	size_t size = 0;//size of allocated array
	size_t _fill = 0;//indicate end of string '\0' in string

	char *str = NULL;

	iterator Head;//indicate begin of string
	iterator Tail;//indicate end of array
	iterator Last;//indicate end of string
	
	/////////////////////////////////////////////
	//auxiliary functions
	bool free_space() const { return lenght() > fill() + 1 ? true : false; }
	size_t str_len(const char *);
};


#endif
