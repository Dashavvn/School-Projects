#include <string>
#include <iostream>
using namespace std;

int main()
{
  string n;
  int words = -1;
  while(n != "STOP")
    {
      cin >> n;
      words++;
    }
  cout << words << endl;
  
}
