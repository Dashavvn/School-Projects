#ifndef _MAZE_H_
#define _MAZE_H_

#include <vector>
#include <iostream>

#include "Location.h"
using namespace std;

/** Stores a 2D grid-based maze, with walls and open spaces each
  * taking one grid square.  A Maze has one start and one finish.
  * @author Don Blaheta
  * @version 27 Feb 2019 */
class Maze
{
  private:
    vector<vector<char>> data;
    int width = 0;
    int height = 0;
    Location start = Location{-1, -1};
    Location finish = Location{-1, -1};

  public:
    Maze() = default;
    Maze(istream& in) {
      read(in);
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    Location getStart() const { return start; }
    Location getFinish() const { return finish; }

    /** modifies this Maze to be a representation of the text it reads
      * from a given input stream */
    void read(istream& in);
    /** prints this Maze to a given output stream */
    void print (ostream& out) const;

    /** determines whether a given Location is valid for this Maze */
    bool contains (const Location& loc) const;
    /** looks up the element that this Maze that lies at a given
      * valid Location 
      * @pre loc must be valid, i.e. contains(loc) must be true */
    char elementAt (const Location& loc) const;
  //determines whether this Maze has any legal path from its start to its finish
  bool doesPathExist() const;
  
};

#endif
