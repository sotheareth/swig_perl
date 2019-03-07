/*
 * TestProgram.h
 *
 *  Created on: 20 Jul 2018
 *      Author: hsotheareth
 */
#include <iostream>
#include <string>

#ifndef Address_H_
#define Address_H_
using namespace std;

class Address {
private :
	string street;
	string commune;

public:
	Address(){}
	Address(const string& street,const string& commune) : street(street), commune(commune){

	}
	~Address(){}

	string getStreet(){
		return this->street;
	}

	void setStreet(const string& street){
		this->street = street;
	}

	string getCommune(){
		return this->commune;
	}

	void setCommune(const string& commune){
		this->commune = commune;
	}
};

#endif /* Person_H_ */
