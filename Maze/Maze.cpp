#include "Maze.h"

#include <stack>
#include <sstream>
#include <stdexcept>

#include "Location.h"
using namespace std;

/** @file Maze.cpp
  * @author Don Blaheta
  * @version 27 Feb 2019 */

void Maze::read(istream& in)
{
  string line;
  getline (in, line); // dimensions
  istringstream dims (line);
  dims >> width >> height;

  data.resize(width);
  for (int x = 0; x < width; ++x)
    data[x].resize(height);

  // read maze in, find start and finish
  for (int y = 0; y < height; ++y)
  {
    getline (in, line);
    for (int x = 0; x < width; ++x)
    {
      char ch = line[x];
      data[x][y] = ch;
      if (ch == 'o')
      {
        start = Location{x,y};
      }
      else if (ch == '*')
      {
        finish = Location{x,y};
      }
    }
  }
}

void Maze::print (ostream& out) const
{
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      out << data[x][y];
    }
    out << endl;
  }
}


bool Maze::contains (const Location& loc) const
{
  return loc.getX() >= 0 and loc.getX() < width
     and loc.getY() >= 0 and loc.getY() < height;
}

char Maze::elementAt (const Location& loc) const
{
  if (!contains(loc))
    throw runtime_error("Location " + loc.toString() 
                          + " not valid in this Maze");
  return data[loc.getX()][loc.getY()];
}

bool Maze::doesPathExist() const
{
  stack<Location> agenda;
  Location start = getStart();
  agenda.push(start);

  

  return false;

}
