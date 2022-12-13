/*
   This lab is from the authors of the book.

   You are to complete the following functions using the
   operations listed in legal ops, you may use no more
   than the max number of ops listed.

   You may work in pairs and use your book.  You may not look 
   at the internet (phone or computer).  Both names need to
   be included in the comments at the top of the file.

   The ratings lists the difficulty of each problem. 

   To handin your lab:
   make handin  
   */


/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
*/
#include <iostream>

using namespace std;

int evenBits() {
        int b = 0x55;
        int s = b << 8;
        s = s | b;
        int w = s << 16;
        w = w | s;
 cout << w << endl;

}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
        int y = x >> 31;
        int w = (x + y) ^ y;
       
	cout << w;
         
        return w;
}

/* 
 * isNotEqual - return 0 if x == y, and 1 otherwise 
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y) {

	int s = (x ^ y);
	int w = !!s;
       
	cout << w;

	return w;
}

/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {

        x = ~x;
        int y = x + 1;
        int w =((~w & x)>>31) & 1;

	cout << w;

        return w;
}

/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */

int sign(int x) {
	int w = !!x;
	w = ~w;
	
	cout << w;	
	return w;
}


/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
        int w = 1 + (x >> 31);

        return w;
}

/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {

        int a = x & y;
        int b = ~x & ~y;
        int w = ~a & ~b;


        return w;
}

/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {

int s = 31 + ((~n) + 1);
    int a = 1 << s;
    a |= a + ((~1) + 1);
    x = x >> n;

}


int main(){



        return 0;

}

