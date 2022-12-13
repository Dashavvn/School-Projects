#ifndef CAR_H
#define CAR_H
#include <string>
#include <iostream>

using namespace std;


class Car
{
	private:
	         string c_name;	
		 int c_id;
		 double c_price;
		 string c_age;
		 double c_size;
		 string c_MPH;
		 bool c_red;

	public:
		Car();
		Car(string,int, double, string, double, string, bool);
                /*Acessors*/		
		int id() const;
		double price() const;
		string age() const;
		double size() const;
		string MPH() const;
		bool red() const;
                /*Mutators*/
		void set_id(const int id);
		void set_price(const double price);
		void set_age(const string age);
		void set_size(const double size);
		void set_MPH(const string MPH);
		bool get_red(const bool red);
		void print();


};
#endif
