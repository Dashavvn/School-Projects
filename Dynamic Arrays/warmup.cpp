#include <iostream>
#include <fstream>
#include <sstream>
#include "boat.h"
#include "car.h"
#include <vector>
#include <string>

using namespace std;

int main()
{

  vector<Car> car_list;

  vector<Boat> boat_list;

  ifstream fin("inventory.dat");
  string line; 
  while(getline(fin, line))
  {	
    istringstream sin(line); 
    string name;
    sin >> name;

    if(name == "car") {

      int id; 
      double price;
      string age; 
      double size; 
      string MPH; 
      bool red = false;
      string is_red;

      sin >>id >> price >> age >> size >> MPH >> is_red;

      if(is_red == "true")
      {
	red = true;
      }
      Car newCar(name, id, price, age, size, MPH, red);

      car_list.push_back(newCar);

    } 
    else{

      istringstream sin(line); 
      int id; 
      double price; 
      string age;
      double length; 
      bool yacht = false; 
      string is_yacht;

      sin >> name >> id >> price >> age >> length >> is_yacht;
      if(is_yacht == "true")
      {
	yacht = true;
      }
      Boat newBoat(name, id, price, age, length, yacht);

      boat_list.push_back(newBoat);

    }	
  }
  fin.close();

for(int i =0;i < car_list.size(); ++i)
{
car_list[i].print();
}

for(int i =0; i < boat_list.size(); ++i)
{
boat_list[i].boat_print();
}


}
