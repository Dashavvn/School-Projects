#include "Location.h"

#include <sstream>
using namespace std;

/** @file Location.cpp
  * @author Don Blaheta
  * @version 9 Oct 2014 */

bool Location::isEqualTo (const Location& other) const
{
  return x == other.x && y == other.y;
}

string Location::toString () const
{
  ostringstream out;
  out << "(" << x << "," << y << ")";
  return out.str();
}
