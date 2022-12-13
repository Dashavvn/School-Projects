#include <string>
using namespace std;

string getInitials (string phrase)
{
string [] output = phrase.Split(' ');
foreach(string s in output)
{
 string initials = initials + (s[0]+" ") ;
}
 return initials;

}
