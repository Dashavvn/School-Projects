#include <string>
using namespace std;

string bookPageEntry (string title, string author)
{
   int t = title.length();
   int a = author.length();
   int length = t + a;
   int left= 70 - length;
  int space= left % 2;
  int times= (left-1) / 2;
  string s = "";
  string d = ""; 
  for(int i =0; i < times; i++)
    {
      d = d + " .";
    }

  string entry = title + d + s + author;

  if(entry.length()==69)
    {
      entry= title + d + s + " " + author;
    }
      if(entry.length()==68)
    {
      entry= title + d + s + "  " + author;
    }
  
  
  return entry;
}
