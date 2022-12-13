#include <iostream>
using namespace std;

int nearestFive (int cents){
{
  int n = cents % 5;
  if(n == 1 || n == 2 )
    {
    cents = cents - n;
    }
  if(n == 3)
    {
      cents = cents + 2;
    }
      if(n == 4)
    {
      cents = cents + 1;
    }
  return cents; 
}

	  }

