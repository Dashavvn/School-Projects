#include <iostream>
using namespace std;

int main()
{
  bool prime = true;
  int num;
  while(num != 0)
    {
      cin >> num;

  
  for (int i = 3; i*i < num+1; i += 2) {
      if (num % i == 0)
	{
	 prime = false;
	}
      else
	prime = true;
	}

  if(num == 0)
    {
      break;
    }
  
  if (num == 2 || 3 || 5 || 7)
   {
     prime = true;

   }
  if (num % 2 == 0)
    {
     prime = false;
    }


  if(prime == true)
    cout << "PRIME" << endl;
  else
    cout << "NOT PRIME" << endl;
    }   
}


