#include "Card.h"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

/** Shows various library functions that rely on a class having 
  * overloaded operators.
  * @author Don Blaheta
  * @version 27 Mar 2019 */

int main()
{
  Card aceS = Card{1, 'S'};
  Card fiveD = Card{5, 'D'};
  Card tenH = Card{10, 'H'};
  Card jackC = Card{11, 'C'};
  Card queenH = Card{12, 'H'};
  Card kingD = Card{13, 'D'};

  vector<Card> cards = { aceS, fiveD, kingD, jackC, queenH };


  
  cout << count(cards.begin(), cards.end(), jackC) << endl;
  cout << count(cards.begin(), cards.end(), tenH) << endl;

  





  cout << "Orig:\n";
  for (Card c : cards) {
    cout << c << endl;
  }

  replace(cards.begin(), cards.end(), queenH, fiveD);

  cout << "After replace:\n";
  for (Card c : cards) {
    cout << c << endl;
  }
  
  auto newend = remove(cards.begin(), cards.end(), fiveD); //moves it over
  cards.erase (newend, cards.end()); // actually erases extra

  cout << "After remove:\n";
  for (Card c : cards) {
    cout << c << endl;
  }
  
  






  cout << "Before sort:\n";
  for (Card c : cards) {
    cout << c << endl;
  }
  sort (cards.begin(), cards.end());
  cout << "Sorted:\n";
  for (Card c : cards) {
    cout << c << endl;
  }

  


}
