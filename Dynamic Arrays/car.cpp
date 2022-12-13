#include <iostream>
#include "car.h"
#include <vector>
#include <string>
using namespace std;

Car::Car():c_name{" "},c_id{0},c_price{0},c_age{" "},c_size{0},c_MPH{" "},c_red{" "}
{}

Car::Car(string name, int id, double price, string age,double size, string MPH, bool red)
{
	c_name = name;
	c_id = id;
	c_price = price;
	c_age = age;
	c_size = size;
	c_MPH = MPH;
	c_red = red;
}
int Car::id() const
{
	return c_id;
}

double Car::price() const
{
	return c_price;
}

string Car::age() const
{
	return c_age;
}

double Car::size() const
{
	return c_size;
}

string Car::MPH() const
{
	return c_MPH;
}

bool Car::red() const
{
	return c_red;
}

void Car::set_id(const int id)
{
	c_id = id;
}

void Car::set_price(const double price)
{
	c_price = price;
}

void Car::set_age(const string age)
{
	c_age = age; 
}

void Car::set_size(const double size)
{
	c_size = size;
}

void Car::set_MPH(const string MPH)
{
	c_MPH = MPH;
}

bool Car::get_red(const bool red)
{
	c_red = red;
	return c_red;	
}

void Car::print()
{
	if(c_red == false)
		cout << c_name << " " << c_id << " has a MSRP of $" << c_price <<","<< " is " << c_age << " years old, has an " << c_size << " gallon fuel tank, can reach a top speed of " << c_MPH << " MPH, and is not red." << endl;
	else
		cout << c_name << " " << c_id << " has a MSRP of $" << c_price <<","<< " is " << c_age << " years old, has an " << c_size << " gallon fuel tank, can reach a top speed of " << c_MPH << " MPH, and is red." << endl;
}

