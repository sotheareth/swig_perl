/*
 * TestProgram.h
 *
 *  Created on: 20 Jul 2018
 *      Author: hsotheareth
 */
#include <iostream>
#include <string>
#include "Address.h"

#ifndef Person_H_
#define Person_H_
using namespace std;

class Person {
private :
	string name;
	int age;
	Address address;

public:
	Person(){}
	Person(const string& name, int age) : name(name), age(age){

	}
	~Person(){}

	string getName(){
		return this->name;
	}

	void setName(const string& name){
		this->name = name;
	}

	int getAge(){
		return this->age;
	}

	void setAge(int age){
		this->age = age;
	}

	Address getAddress(){
		return this->address;
	}

	void setAddress(const Address& address){
		this->address = address;
	}
};

#endif /* Person_H_ */
