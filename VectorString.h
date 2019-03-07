/*
 * TestProgram.h
 *
 *  Created on: 20 Jul 2018
 *      Author: Sotheareth
 */

#ifndef VectorString_H_
#define VectorString_H_

#include <stdlib.h>
#include <iostream>
#include <string>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <vector>
#include <ctime>
#include <list>
#include "Person.h"


using namespace std;

class VectorString {

private:

	static const int tableSize = 4;

	struct item
	{
		string name;
		string drink;
		item * nextItem;
	};

	item* HashTable[tableSize];

public:
	VectorString();
	~VectorString();
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	sql::PreparedStatement *pstmt;
	Person getPerson();
	vector<Person> getPersonList();
	void connectToMysql();
	void showResult(string query);
	string getIdLabel(string ref);
	int addNumber(int num);
	list<string> addOne(string value);
	int addArray(int arr[],int size);
	float addFloat(float f);
	string testString(string input);
	double addDouble(double d);
	bool checkBoolean(string input);
	int Hash(string key);
	void AddItem(string name, string drink);
	int NumberOfItemsInIndex(int index);
	void PrintTable();
	void PrintItemsInIndex(int index);
	void FindDrink(string name);
	void RemoveItem(string name);
	void ApplyLambda();
};

#endif /* VectorString_H_ */
