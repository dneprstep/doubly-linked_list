#include "duo_list.h"

duo_list::duo_list() :size(0), _head(NULL), _tail(NULL)
{
	this->_tail = new node;
	if (this->_tail == NULL)
		throw("Error alloc memory!");

	this->HEAD(this->_head);
	this->TAIL(this->_tail);
}


bool duo_list::push_back(object_data* add_item)
{
	if (add_item == NULL)
		return false;


	if (empty() && push_head(add_item))
		return true;
	else
	{
		node* temp = new node(add_item);
		if (temp == NULL)
			throw("Error alloc memory");

		temp->set_left(_tail->get_left());
		temp->set_right(_tail);

		_tail->get_left()->set_right(temp);
		_tail->set_left(temp);
		
		TAIL(_tail);
		size++;

		return true;
	}
	return false;
}
bool duo_list::push_head(object_data* add_item)
{
	if (add_item == NULL)
		return false;

	node* temp = new node(add_item);
	if (temp == NULL)
		throw("Error alloc memory");

	if (empty())
	{
		_head = temp;
		_head->set_left(NULL);
		_head->set_right(_tail);
		_tail->set_left(_head);
	}
	else
	{
		_head->set_left(temp);
		temp->set_right(_head);
		temp->set_left(NULL);
		_head = temp;
	}
	
	HEAD(_head);
	size++;
	
	return true;
}

bool duo_list::pop_back()
{
	if (!empty())
	{
		node* temp = _tail->get_left();
		if (temp == _head)
		{
			delete temp;
			_head = NULL;
			_tail->set_left(NULL);
			
			HEAD(_head);
		}
		else
		{
			temp->get_left()->set_right(_tail);
			_tail->set_left(temp->get_left());
			delete temp;
		}
		size--;
		return true;
	}
	return false;
}
bool duo_list::pop_head()
{
	if (!empty())
	{
		node* temp = _head;
		if (temp->get_right() == _tail)
		{
			delete temp;
			_head = NULL;
			_tail->set_left(NULL);
		}
		else
		{
			_head->get_right()->set_left(NULL);
			_head = _head->get_right();
			delete temp;
		}

		HEAD(_head);
		size--;
		return true;
	}
	return false;
}

bool duo_list::insert_after(iterator& iter, object_data* item)
{
	if (item == NULL)
		return false;

	if (iter == this->TAIL && push_back(item))
			return true;

	if (!iter.valid_item())
		return false;

	node* temp = iter.get_item()->get_right();

	node* new_node = new node(item, iter.get_item(), temp);
	if (temp == NULL)
		throw("Error alloc memory");

	iter.get_item()->set_right(new_node);
	temp->set_left(new_node);

	size++;
	return true;
}
bool duo_list::delete_at(iterator& iter)
{
	if (iter == TAIL && pop_back())
		return true;
	if (iter.get_item() == NULL)
		return false;
	if (iter == HEAD && pop_head())
		return true;

	node* temp = iter.get_item()->get_right();

	iter.get_item()->get_left()->set_right(iter.get_item()->get_right());
	temp->set_left(iter.get_item()->get_left());

	delete iter.get_item();

	iter(temp);
	size--;
	return true;
}

void duo_list::set_separator(char symbol)
{	this->separator = symbol; }
char duo_list::get_separator()
{	return this->separator; }


bool duo_list::empty() const
{
	return lenght() > 0 ? false : true;
}
size_t duo_list::lenght() const
{
	return this->size;
}


void duo_list::clear()
{
	if (!empty())
	{
		node* temp = _head;
		while (temp != _tail)
		{
			temp = temp->get_right();
			delete _head;
			_head = temp;
		}
		_tail->set_left(NULL);
		_head = NULL;
		size = 0;

		HEAD(_head);
	}	
}


ostream& duo_list::show_all(std::ostream& out)
{
	if (empty())
		return out;
	node* temp = _head;
	while (temp != _tail)
	{
		out << temp->operator*() << this->get_separator();
		temp = temp->get_right();
	}
	return out;
}
ostream& operator<<(ostream& stream, duo_list& obj)
{
	if (obj.empty())
		return stream<<"-list empty-";

	//check stream flag and clear it
	if (stream.rdstate() != std::ios_base::goodbit)
		stream.clear();
	stream.flush();

	obj.show_all(stream);

	if (stream.rdstate() != std::ios_base::goodbit)
		stream.clear();
	stream.flush();

	return stream;
}