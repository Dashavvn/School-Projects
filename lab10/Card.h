#ifndef _CARD_H_
#define _CARD_H_

#include <string>
using namespace std;

/** Represents playing cards for card games
  * @author Don Blaheta
  * @version 6 Oct 2014 */
class Card
{
  private:
    /** Rank i.e. number or face: ace=1, JQK = 11,12,13 */
    int rank;
    /** Suit represented by uppercase first letter of suit (CDHS) */
    char suit;

  public:
  


  /** Constructs a Card with given rank and given suit */
    Card (int r, char s);
    /** Constructs a Card from given string
      * @pre s must be two characters long and in correct format */
    Card (string s);

    /** Returns the rank of this Card (A=1, TJQK = 10,11,12,13 */
    int getRank() const;
    /** Returns the suit of this Card (CDHS) */
    char getSuit() const;

    /** Determines whether this Card has same rank/suit as given other Card */
    bool isEqualTo(const Card& other) const;
    /** Builds string that is standard representation of this Card */
    string toString() const;
  //determines whether two Card objects are equal to each other
  bool operator==(const Card& other) const;
  //determines whether the given Card is equal to the other card
 friend ostream& operator<<(ostream& outStream, const Card& other);
  //Builds output stream for representation of the other Card 
  bool operator<(const Card& other) const;
  //Builds input stream for representation of the other Card
  friend istream& operator<<(istream& in, const Card& other);
  private:
    static int fromChar(char rank);
    static char toChar(int rank);

};

#endif
