Lab 1
CMSC 162

The files provided for Lab 1 will help you test your own code (which is
what you'll be handing in) and make sure it is taking arguments and/or
input and providing return values or output in the right formats.  They
also illustrate some testing techniques you might find helpful.

In each case, the filename "yourfilename.cpp" is used as a standin for 
whatever file contains your work for that problem.  Replace it with your
filename as appropriate (in fact, feel free to edit this file to refer
to the actual filenames you've used).

To test problem a:
  compile test-a-lastVowel.u yourfilename.cpp -o test-a
  ./test-a

To test problem b:
  compile test-b-numVowelsIncludingY.u yourfilename.cpp -o test-b
  ./test-b

To test problem c:
  compile test-c-lastNameFirst.u yourfilename.cpp -o test-c
  ./test-c

To test problem d:
  compile test-d-getInitials.u yourfilename.cpp -o test-d
  ./test-d

To test problem e:
  compile test-e-bookPageEntry.u yourfilename.cpp -o test-e
  ./test-e

To test problem f:
  compile test-f-isRightTriangle.u yourfilename.cpp -o test-f
  ./test-f

To test problem g:
  compile test-g-nearestFive.u yourfilename.cpp -o test-g
  ./test-g

To test problem h:
  compile test-h-piFromEuler.u yourfilename.cpp -o test-h
  ./test-h

To test problem i:
  compile test-i-sumOfDigits.u yourfilename.cpp -o test-i
  ./test-i



To test problem j:
  compile yourfilename.cpp -o run-j
  ./run-j < test-j-numWordsUntilSTOP-1.in | diff test-j-numWordsUntilSTOP-1.expect -
  ./run-j < test-j-numWordsUntilSTOP-2.in | diff test-j-numWordsUntilSTOP-2.expect -

To test problem k:
  compile yourfilename.cpp -o run-k
  ./run-k < test-k-acrostic-1.in | diff test-k-acrostic-1.expect -

To test problem l:
  compile yourfilename.cpp -o run-l
  ./run-l < test-l-checkPrimes-1.in | diff test-l-checkPrimes-1.expect -

To test problem m:
  compile yourfilename.cpp -o run-m
  ./run-m < test-m-gradesSummary-1.in | diff test-m-gradesSummary-1.expect -
  ./run-m < test-m-gradesSummary-2.in | diff test-m-gradesSummary-2.expect -

To test problem n:
  compile yourfilename.cpp -o run-n
  ./run-n < test-n-multTable-1.in | diff test-n-multTable-1.expect -
