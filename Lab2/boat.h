#ifndef BOAT_H
#define BOAT_H
#include <string>
#include <iostream>

using namespace std;

class Boat
{
	private:
	         string b_name;	
		 int b_id;
		 double b_price;
		 string b_age;
		 double b_length;
		 bool b_yacht;

	public:
		Boat();
		Boat(string, int, double, string, double, bool);
                /*Acessors*/		
		int id() const;
		double price() const;
		string age() const;
		double length() const;
		bool yacht() const;
                /*Mutators*/
		void set_id(const int id);
		void set_price(const double price);
		void set_age(const string age);
		void set_length(const double length);
		bool get_yacht(const bool yacht);
		void boat_print();




};
#endif
