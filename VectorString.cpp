/*
 * VectorString.cpp
 *
 *  Created on: 23 Jul 2018
 *      Author: sotheareth
 */

#include <iostream>
#include <stdlib.h>
#include "VectorString.h"

using namespace std;

VectorString::VectorString()
{
	driver = NULL;
	con = NULL;
	stmt = NULL;
	res = NULL;
	pstmt = NULL;

	for(int i=0; i<tableSize; i++)
	{
		HashTable[i] = new item;
		HashTable[i]->name = "empty";
		HashTable[i]->drink = "empty";
		HashTable[i]->nextItem = NULL;
	}
}

VectorString::~VectorString()
{
	item* Ptr;
	for(int i=0; i<tableSize; i++)
	{
		while(HashTable[i] != NULL)
		{
			Ptr = HashTable[i];
			HashTable[i] = HashTable[i]->nextItem;
			delete Ptr;
		}
	}
}

void VectorString::connectToMysql()
{
	try{
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "sandi", "hmsandi!");
	stmt = con->createStatement();
	stmt->execute("USE eg_db");
	cout << "Connected \n";
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
}

void VectorString::showResult(string query)
{
	res = stmt->executeQuery(query);
	//res = stmt->executeQuery("SELECT * FROM test");
	while (res->next())
	{
		cout << "id = " << res->getInt(1);
		cout << ", label = '" << res->getString("label") << "'" << endl;
	}
	delete res;
	delete stmt;
	delete con;
}

string VectorString::getIdLabel(string ref)
{
	string result;
	res = stmt->executeQuery(ref);

	while(res->next())
	{
		result = res->getString("label");
	}

	delete res;
	delete stmt;

	return result;

}

int VectorString::addNumber(int num)
{
	num = num+1;
	return num;
}

list<string> VectorString::addOne(string value)
{
	cout << "initial ref: " << value << endl;
	list<string> test;
	test.push_back("1");
	test.push_back("2");
	cout << "latest ref: " << value << endl;

	return test;
}

vector<Person> VectorString::getPersonList()
{
	cout << "initial ref: " << endl;
	vector<Person> result;

	Person person1;
	person1.setName("person1");
	person1.setAge(20);
	Address address1("144", "Sangkat Phsar Kandal 2");
	person1.setAddress(address1);
	result.push_back(person1);

	Person person2;
	person2.setName("person2");
	person2.setAge(22);
	Address address2("233", "Sangkat Phsar Thmei 2");
	person2.setAddress(address2);
	result.push_back(person2);

	cout << "count person : " << result.size() << " street: " << person2.getAddress().getStreet() << endl;
	return result;

}

Person VectorString::getPerson()
{
	cout << "initial ref: " << endl;
	Person test;
	test.setName("test");
	test.setAge(22);
	cout << "person : " << test.getName() << " " << test.getAge() << endl;

	return test;
}

int VectorString::addArray(int arr[],int size)
{
	int i, sum=0;
	int arg;
	for(i=0; i<size; ++i)
	{
		sum += arr[i];
	}
	arg = sum/size;
	cout << "Check Average: " << arg << endl;
	return arg;
}

float VectorString::addFloat(float f)
{
	f = f + 1;
	cout << "latest value: " << f << endl;
	return f;

}

string VectorString::testString(string input)
{
	return input;
}

double VectorString::addDouble(double d)
{
	d = d + 1;
	cout << "latest value: " << d << endl;
	return d;
}

bool VectorString::checkBoolean(string input)
{
	if(!input.empty())
	{
		return 1;
	}
	else
		return 0;
}

void VectorString::PrintItemsInIndex(int index)
{
	item* Ptr = HashTable[index];

	if(Ptr->name == "empty")
	{
		cout << "index = " << index << " is empty." << endl;
	}
	else
	{
		cout << "index " << index << " contains the following items\n";

		while(Ptr != NULL)
		{
			cout << "-----------------\n";
			cout << Ptr->name << endl;
			cout << Ptr->drink << endl;
			cout << "-----------------\n";
			Ptr = Ptr->nextItem;
		}
	}
}

int VectorString::Hash(string key)
{
	int hash = 0;
	int index;

	//index = key.length();

	for(int i=0; i<key.length(); i++)
	{
		hash = (hash + (int) key[i]) * 17;
		//cout << "hash = " << hash << endl;
	}

//	cout << "key[0] = " << (int)key[0] << " = " << key[0] << endl;
//	cout << "key[1] = " << (int)key[1] << " = " << key[1] << endl;
//	cout << "key[2] = " << (int)key[2] << " = " << key[2] << endl;
//	cout << "key[3] = " << (int)key[3] << " = " << key[3] << endl;

	index = hash % tableSize;

	return index;
}

void VectorString::AddItem(string name, string drink)
{
	int index = Hash(name);

	if(HashTable[index]->name == "empty")
	{
		HashTable[index]->name = name;
		HashTable[index]->drink = drink;
	}
	else
	{
		item* Ptr = HashTable[index];
		item* n = new item;
		n->name = name;
		n->drink = drink;
		n->nextItem = NULL;
		while(Ptr->nextItem != NULL)
		{
			Ptr = Ptr->nextItem;
		}
		Ptr->nextItem = n;
	}
}

int VectorString::NumberOfItemsInIndex(int index)
{
	int count = 0;

	if(HashTable[index]->name == "empty")
	{
		return count;
	}
	else
	{
		count++;
		item* Ptr = HashTable[index];
		while(Ptr->nextItem != NULL)
		{
			count++;
			Ptr = Ptr->nextItem;
		}
	}
	return count;
}

void VectorString::PrintTable()
{
	int number;
	for(int i=0; i<tableSize; i++)
	{
		number = NumberOfItemsInIndex(i);
		cout << "---------------------\n";
		cout << "Index = " << i << endl;
		cout << HashTable[i]->name << endl;
		cout << HashTable[i]->drink << endl;
		cout << "# of items = " << number << endl;
		cout << "---------------------\n";
	}
}

void VectorString::FindDrink(string name)
{
	int index = Hash(name);
	bool foundName = false;
	string drink;

	item* Ptr = HashTable[index];
	while(Ptr != NULL)
	{
		if(Ptr->name == name)
		{
			foundName = true;
			drink = Ptr->drink;
		}
		Ptr = Ptr->nextItem;
	}
	if (foundName == true)
	{
		cout << "Favorite drink = " << drink << endl;
	}
	else
	{
		cout << name << "'s info was not found in the Hash table\n";
	}
}

void VectorString::RemoveItem(string name)
{
	int index = Hash(name);

	item* delPtr;
	item* P1;
	item* P2;

//	Case 0 - bucket is empty
	if(HashTable[index]->name == "empty" && HashTable[index]->drink == "empty")
	{
		cout << name << " was not found in the Hash Table\n";
	}

//	Case 1 - only 1 item contains in bucket and that item has matching name
	else if(HashTable[index]->name == name && HashTable[index]->nextItem == NULL)
	{
		HashTable[index]->name = "empty";
		HashTable[index]->drink = "empty";

		cout << name << " was removed from the Hash Table.\n";
	}

//	Case 2 - match is located in the first item in the bucket but there are more items in the bucket
	else if(HashTable[index]->name== name)
	{
		delPtr = HashTable[index];
		HashTable[index] = HashTable[index]->nextItem;
		delete delPtr;

		cout << name << " was removed from the Hash Table.\n";
	}

//	Case 3 - bucket contains items but first item is not a match
	else
	{
		P1 = HashTable[index]->nextItem;
		P2 = HashTable[index];

		while(P1 != NULL && P1->name != name)
		{
			P2 = P1;
			P1 = P1->nextItem;
		}
		//	Case 3.1 - no match
		if(P1 == NULL)
		{
			cout << name << " was not found in the Hash Table\n";
		}
		//	Case 3.2 - match is found
		else
		{
			delPtr = P1;
			P1 = P1->nextItem;
			P2->nextItem = P1;
			delete delPtr;

			cout << name << " was removed from the Hash Table.\n";
		}
	}
}

void VectorString::ApplyLambda()
{
	int n = [](int x){ return [](int y) {return y*2; } (x) + 3; }(5);
	cout << n << endl;
}

/*
int main(void)
{

	TestProgram t;
	TestProgram p;
	cout << endl;
	cout << "Running 'SELECT 'Hello World!' AS _message'..." << endl;

	try {
		t.getConnection();
		t.getAllResult("SELECT * FROM test");

		p.getConnection();
		p.getAllResult("SELECT * FROM test_level ORDER BY id DESC");

	} catch (sql::SQLException &e) {
	  cout << "# ERR: SQLException in " << __FILE__;
	  cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
	  cout << "# ERR: " << e.what();
	  cout << " (MySQL error code: " << e.getErrorCode();
	  cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	cout << endl;

	return EXIT_SUCCESS;
}
*/
