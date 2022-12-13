#include <string>
using namespace std;

string lastNameFirst (string fullname)
{
  int npos = fullname.length();
  int pos = fullname.find(" ");
  pos = pos + 1;  
  string last = fullname.substr(pos,npos);
  string first = fullname.substr(0,pos-1);
      string lastNameFirst = last + ", " + first;
  return lastNameFirst;
}
