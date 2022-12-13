#include "Card.h"

/** @file Card.cpp
  * @author Don Blaheta
  * @version 27 Mar 2019 */

Card::Card (int r, char s)
  : rank{r}, suit{s}
{
}

Card::Card (string s)
{
  rank = fromChar(s[0]);
  suit = s[1];
}

int Card::getRank() const
{
  return rank;
}

char Card::getSuit() const
{
  return suit;
}

bool Card::isEqualTo(const Card& other) const
{
  return rank == other.rank && suit == other.suit;
}

string Card::toString() const
{
  return string{""} + toChar(rank) + suit;
}


int Card::fromChar (char rank)
{
  if (rank == 'A') return 1;
  else if (rank == 'T') return 10;
  else if (rank == 'J') return 11;
  else if (rank == 'Q') return 12;
  else if (rank == 'K') return 13;
  else return (rank - '0');
}

char Card::toChar (int rank)
{
  if (rank == 1) return 'A';
  else if (rank == 10) return 'T';
  else if (rank == 11) return 'J';
  else if (rank == 12) return 'Q';
  else if (rank == 13) return 'K';
  else return (rank + '0');
}

bool Card::operator==(const Card& other) const
{3
  return isEqualTo(other);
}

ostream& operator<<(ostream& outStream,const Card& other)
{
  outStream << other.toString();
  return outStream;
}

bool Card::operator<(const Card& other) const
{
  //char rank = Card.getRank();
  char rank1 = other.getRank();

  int ans = fromChar(rank);
  int ans2 = fromChar(rank1);
  if(rank == 1)
    return true;
  if(rank1 == 1)
    return false;
  
      if(ans < ans2)
	{return false;}
  else
    return true;
    
}
istream& operator<<(istream& in,const Card& other)
{
  in << other.toString();
  return in;
}
