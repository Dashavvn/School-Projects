#include <string>
#include <cmath>
using namespace std;

bool isRightTriangle (int first, int second, int third)
{

  if((first*first) + (second*second) == third*third)
   return true;

  if((second*second) + (third*third) == first*first)
    return true;
  if((third*third) + (first*first) == second*second)
    return true;
  else
   return false;


}
