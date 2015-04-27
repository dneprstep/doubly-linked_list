#ifndef HEADER_DUO_LIST
#define HEADER_DUO_LIST


#include "object_data.h"

class duo_list
{
public:		
	///////////////////////////////////////
	// lists element
	//include pointer to object (not a copy)
	class node
	{
	private:
		node* left;
		node* right;
		
		////////////////////////////////////////////////////
		//object can be like a 
		//"integer class", "float class" or "string class"
		object_data* item;

	public:
		node() :left(NULL), right(NULL), item(NULL){}
		node(object_data* _item, node* nptr = NULL, node* pptr = NULL)
			:left(nptr), right(pptr)
		{	this->item = _item;		}
		
		node(const node& obj) = delete;
		node& operator=(const node&) = delete;

		node* get_left()
		{	return left;	}
		node* get_right()
		{	return right;	}

		object_data* get_item()
		{	return item;	}


		void set_left(node* _left)
		{	this->left = _left;	}
		void set_right(node* _right)
		{	this->right = _right;	}
		void set_item(object_data* new_item)
		{	
			if (this->item != NULL)
				delete this->item;
			this->item = new_item;	
		}

		//undefined return if item==NULL
		object_data& operator*()
		{	return *item;	}

		void clear()
		{
			if (this->item != NULL)
				delete item;
			left = right = NULL;
		}

		virtual ~node(){ clear(); }
	};

	///////////////////////////////////////


	////////////////////////////////
	// list "iterator"
	class iterator
	{
	private:
		node *item;
	public:
		iterator() :item(NULL) {}
		iterator(node *node_ptr) :item(node_ptr) {}
		iterator(const iterator& obj) { this->item = obj.item; }

		iterator& operator=(const iterator& obj) { this->item = obj.item; return *this; }
		virtual ~iterator() { item = NULL; }

		void operator()(node *node_ptr) { this->item = node_ptr; }

		bool operator==(const iterator& obj)
		{	return this->item == obj.item ? true : false;	}

		bool valid_item() { return this->item == NULL ? false : true; }

		node* get_item() { return this->item; }

		void operator++()
		{
			if (item->get_right() == NULL)
				return;
			item = item->get_right();
			return;
		}
		void operator--()
		{
			if (item->get_left() == NULL)
				return;
			item = item->get_left();
			return;
		}
		object_data& operator*() 
		{	return item->operator*();	}
	};

	////////////////////////////////


	duo_list();
	duo_list(const duo_list&) = delete;
	duo_list& operator=(const duo_list&) = delete;

	bool push_back(object_data*);
	bool push_head(object_data*);

	bool pop_back();
	bool pop_head();

	bool insert_after(iterator& iter, object_data* item);
	bool delete_at(iterator& iter);

	iterator Head() { return HEAD; }
	iterator Tail() { return TAIL; }

	void set_separator(char);
	char get_separator();

	///////////////////////////////////////////////////////////
	// transfer all data from list to ostream
	//
	ostream& show_all(std::ostream& out);
	friend ostream& operator<<(ostream& stream, duo_list& obj);

	////////////////////////////////////////////////////////////


	bool empty() const;
	size_t lenght() const;

	void clear();

	virtual ~duo_list()
	{
		clear(); 	
		delete _tail;
		_tail = NULL;
	}


	private:
		//pointer to begin and end of list
		node* _head;
		node* _tail;

		size_t size;

		//separator between objects in list when we output them to console
		char separator = '\n';

		iterator HEAD;
		iterator TAIL;

};


#endif