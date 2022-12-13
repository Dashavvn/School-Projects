#include <iostream>
#include "boat.h"
#include <vector>
#include <string>

using namespace std;

Boat::Boat():b_name{" "},b_id{0},b_price{0},b_age{""},b_length{0},b_yacht{"false"}
{}

Boat::Boat(string name,int id, double price, string age, double length, bool yacht)
{
b_name = name;
b_id = id;
b_price = price;
b_age = age;
b_length = length;
b_yacht = yacht;
}

int Boat::id() const
{
return b_id;
}

double Boat::price() const
{
return b_price;
}

string Boat::age() const
{
return b_age;
}

double Boat::length() const
{
return b_length;
}

bool Boat::yacht() const
{
return b_yacht;
}

void Boat::set_id(const int id)
{
b_id = id;
}

void Boat::set_price(const double price)
{
b_price = price;
}

void Boat::set_age(const string age)
{
b_age = age; 
}

void Boat::set_length(const double length)
{
b_length = length;
}

bool Boat::get_yacht(const bool yacht)
{
b_yacht = yacht;
if(b_yacht = true)
	return true;
else
	return false;}
void Boat::boat_print()
{
	if(b_yacht == false)
		cout << b_name <<" " << b_id << " has a MSRP of $" << b_price << "," << " is " << b_age << " years old, has an a length of " << b_length << " and is not a yacht." << endl;
	else
		cout << b_name <<" " << b_id << " has a MSRP of $" << b_price << "," << " is " << b_age << " years old, has an a length of " << b_length << " and is a yacht." << endl;
}


