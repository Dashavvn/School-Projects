#include <string>
using namespace std;

char lastVowel (string phrase)
{
  int length = phrase.length();
    char Vowel= 'K';

        for (int i = 0; i < length; i++)
        {
          if(phrase[i] == 'a')
            {
              Vowel='a';
            }
            if(phrase[i] == 'e')
              {
              Vowel='e';
              }

              if(phrase[i] == 'i')
                {
                  Vowel='i';
                }
	      if(phrase[i] == 'o')    
		{
		  Vowel='o';
                  }
                   if(phrase[i] == 'u')
                     {
                       Vowel='u';
                     }

                      if(phrase[i] == 'A')
                        {
                        Vowel='A';
                      }
                       if(phrase[i] == 'E')
                        {
                          Vowel='E';
                        }
                        if(phrase[i] == 'I')
                          {
                            Vowel='I';
                          }
                          if(phrase[i] == 'O')
     {
                        Vowel='O';
                      }
			  if(phrase[i] == 'U')
			    {
			      Vowel= 'U';
				}
			  
        }
        if(Vowel=='K')
	  {
	    return '!';
	  }
        char lastvowel = Vowel;
	return lastvowel;
}

