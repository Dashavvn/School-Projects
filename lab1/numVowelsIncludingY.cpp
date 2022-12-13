
#include <string>
using namespace std;

int numVowelsIncludingY (string line)
{
    int length = line.length();
        int numvowels = 0;
	for(int i = 0; i < length; i++)
	  {
	    char n = toupper(line[i + 1]);
	    char letter = toupper(line[i]);
	    if(letter == 'A' || letter == 'E' || letter == 'I' ||  letter == 'O' || letter == 'U')
	      {
		numvowels = numvowels + 1;
	      }
	    if(letter == 'y' || letter == 'Y')
	      {
		numvowels = numvowels + 1;
		
		if( n == 'A') 
		  {
		    numvowels--;
		  }
		  if( n  == 'E')
	          {
	             numvowels--;
	          }
	    if( n  == 'O')
                  {
                    numvowels--;
                  }
            if( n  == 'I')
                  {
                    numvowels--;
                  }
            if( n == 'U')
                  {
                    numvowels--;
                  }

		  }
	  }
	return numvowels;
}



