#include "duo_list.h"
#include "whole_number.h"
#include "string_data.h"
#include "float_data.h"

#include <conio.h>
using std::cin; using std::cout; using std::endl;

namespace global
{	
	bool loop = true;
	duo_list list;
};

void Add(char);
void drawMenu();
void chooseMenu();
void list_pop_back();
void list_pop_head();
void list_clear();
void list_show_all();
void list_show_first();
void list_show_last();
void quit();


void list_pop_back()
{
	using namespace global;
	if (list.empty())
		cout << "-list are empty-\n\n";
	if (list.pop_back())
		cout << "\nLast object was deleted\n" << endl;
}
void list_pop_head()
{
	using namespace global;
	if (list.empty())
		cout << "-list are empty-\n\n";
	if (list.pop_head())
		cout << "\nFirst object was deleted\n" << endl;
}
void list_clear()
{
	using namespace global;
	list.clear();
	cout << "\nList cleared.\n";
}
void list_show_all()
{
	using namespace global;
	cout << "\nOutput all :\n" << list
		<< "\nEnd of list objects\n" << endl;
}
void list_show_first()
{
	using namespace global;
	if (!list.empty())
		cout << "\n\tFirst object:" << *list.Head() << endl;
	else
		cout << "\n-list are empty-\n\n";
}
void list_show_last()
{
	using namespace global;
	if (!list.empty())
	{
		duo_list::iterator iter;
		iter = list.Tail();
		--iter;
		cout << "\n\tLast object:" << *iter << endl;
	}
	else
		cout << "-list are empty-\n\n";
}
void quit()
{
	using namespace global;
	cout << "\n\tThank you, for using this program.\nGood Luck!\n";
	loop = false;
}


void Add(char symbol)
{
	using namespace global;

	object_data* new_object;
	switch (symbol)
	{
		case 'i':
			new_object = new whole_number();
			if (new_object == NULL)
				return;
			break;
		case 'f':
			new_object = new float_data();
			if (new_object == NULL)
				return;
			break;
		case 's':
			new_object = new string_data();
			if (new_object == NULL)
				return;
			break;
	default:
		break;
	}		
	cout << "\nInput please:";
	cin >> *new_object;
	list.push_back(new_object);
	cout << "\nObject was added to list\n"<<endl;
}
void drawMenu()
{
	cout<< "###################   MENU  #################\n"
		<< "press button to choose operation\n"
		<< "(i) - add integer to list\n"
		<< "(f) - add float to list\n"
		<< "(s) - add string to list\n"
		<< "\n(p) - delete last object in list\n"
		<< "(h) - delete first object in list\n"
		<< "(c) - delete ALL object in list\n"
		<< "\n(o) - show all object from list to console\n"
		<< "(b) - show first object from list to console\n"
		<< "(l) - show last object from list to console\n\n"
		<< "(ESC) - to exit program\n"
		<< "--------------------------------------------\n";
	
}
void chooseMenu()
{
	using namespace global;
	char symbol;
	symbol = _getch();
	switch (symbol)
		{
		case 'i':
			Add(symbol);
			break;
		case 'f':
			Add(symbol);
			break;
		case 's':
			Add(symbol);
			break;
		case 'p':
			list_pop_back();
			break;
		case 'h':
			list_pop_head();
			break;
		case 'c':
			list_clear();
			break;
		case 'o':
			list_show_all();
			break;
		case 'b':
			list_show_first();
			break;
		case 'l':
			list_show_last();
			break;
		case 27:
			quit();
			break;
		default:
			break;
		}
}

int main()
{
	using namespace global;

	while (loop)
	{
		drawMenu();
		chooseMenu();
	}
	return 0;
}