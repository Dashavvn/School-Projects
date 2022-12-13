#ifndef _LOCATION_H_
#define _LOCATION_H_

#include <iostream>
using namespace std;

/** Stores an (x,y) coordinate pair.
  * @author Don Blaheta
  * @version 27 Feb 2019 */
class Location 
{
  public:
    Location () : x{0}, y{0}
    { }

    Location (int xx, int yy) : x{xx}, y{yy}
    { }

    int getX() const { return x; }
    int getY() const { return y; }

    /** determines whether this Location is the same as a given
      * other Location. */
    bool isEqualTo (const Location& other) const;

    /** makes a string with the text representation of this Location
      * in the form "(2,7)". */
    string toString() const;
    /** prints text representation of this Location to the given stream. */
    void print (ostream& out) const { out << toString(); }

    /** computes and constructs the Location immediately to the east
      * of this Location. */
    Location east() const { return Location{x+1, y}; }
    /** computes and constructs the Location immediately to the west
      * of this Location. */
    Location west() const { return Location{x-1, y}; }
    /** computes and constructs the Location immediately to the north
      * of this Location. */
    Location north() const { return Location{x, y-1}; }
    /** computes and constructs the Location immediately to the south
      * of this Location. */
    Location south() const { return Location{x, y+1}; }

  private:
    int x, y;
};

#endif
