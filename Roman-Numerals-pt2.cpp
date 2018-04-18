/*
A random generator produces a sequence of symbols drawn from the set {I, V, X, L, C, D, M, #}. 
Each item in the sequence is determined by selecting one of these symbols at random, independently of the other items in the sequence. 
At each step, the seven letters are equally likely to be selected, with probability 14% each, but the # symbol only has a 2% chance of selection.
We write down the sequence of letters from left to right as they are generated, and we stop at the first occurrence of the # symbol (without writing it). 
However, we stipulate that what we have written down must always (when non-empty) be a valid Roman numeral representation in minimal form. 
If appending the next letter would contravene this then we simply skip it and try again with the next symbol generated.
Please take careful note of About... 
Roman Numerals for the definitive rules for this problem on what constitutes a "valid Roman numeral representation" and "minimal form". 
For example, the (only) sequence that represents 49 is XLIX. The subtractive combination IL is invalid because of rule (ii), while XXXXIX is valid but not minimal. 
The rules do not place any restriction on the number of occurrences of M, so all integers have a valid representation. 
These are the same rules as were used in Problem 89, and members are invited to solve that problem first.
Find the expected value of the number represented by what we have written down when we stop. 
(If nothing is written down then count that as zero.) Give your answer rounded to 8 places after the decimal point.

Traditional Roman numerals are made up of the following denominations:
I = 1
V = 5
X = 10
L = 50
C = 100
D = 500
M = 1000
Rules for writing roman numbers:
i. Only one I, X, and C can be used as the leading numeral in part of a subtractive pair.
ii. I can only be placed before V and X.
iii. X can only be placed before L and C.
iv. C can only be placed before D and M.
Thus the legal subtractive pairs should be:
IV = 4, IX = 9, XL = 40, XC = 90, CD = 400, CM = 900.
Also, no number should have more than one 'D', 'L' and 'V'
*/

#include <iostream>
#include <ctime>

using namespace std;
void displayChar(char roman_number[], int count); // This function displays the roman character set
int main ()
{
  srand(time(0));
  char romans[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M', '#'};
  char roman_number[100];
  int prob, choice;
  int count = 0;
  char roman_char;
  bool invalidNum = false;
  int i = 0;
  do
  {
    prob = rand() % 100;
    choice = rand() % 7;
    if (prob < 2)
    {
       roman_char = romans[7];
       displayChar(roman_number, count);
    } 
    if (prob >= 2)
    {
      roman_char = romans[choice];
      roman_number[count]=roman_char;
      switch(roman_char)
      {
        case 'M': // Legal combinations are "MMMMM" (many 'M's) or "MMCM" (one CM) 
                  { 
                    while (!invalidNum && i < count)
                    {
                      if (roman_number[i-1] != 'M')
                        invalidNum = true;         // No other characters other than strings of 'M' and one 'CM'  are allowed
                      i++;  
                    } 
                    if (roman_number[count-1] != 'C' || roman_number[count-1] != 'M') // 'CM' is legal
                      invalidNum = true;
                    if (!invalidNum)
                      count++;                
                    invalidNum = false;
                    i = 0;
                    break;
                  } 
          
        case 'D': // Legal combinations are 'MMMMD" or "MMMMCD"
                  { 
                    while (!invalidNum && i < count)
                    {
                      if (roman_number[count-1] != 'C' || roman_number[i] != 'M')
                        invalidNum = true;       // No other characters other than strings of 'M' and one 'C'  are allowed
                      i++;  
                    }                     
                    if (!invalidNum)
                      count++;          
                    invalidNum = false;
                    i = 0;
                    break;
                  }
        case 'C': { // Legal and minimal combinations are 'MMC' 'MMCC' 'MMCCC', 'MMCDXC', 'MMCMXC'
                    while (!invalidNum && i < count)
                    {
                      if (roman_number[i-2] == 'D' || roman_number[i-1] == 'X' || roman_number[i] == 'L') // 'CDXC' or 'CMXC' are legal
                        invalidNum = true;
                      else if (roman_number[i] == 'V'|| roman_number[i] == 'I'|| roman_number[i-3] == 'C')
                        invalidNum = true;       // Illegal combination if 'C' is preceded by 'D', 'L', 'V', 'I' and more than one 'X' 
                      i++;  
                    }  
                    if (roman_number[count-1] == 'C' && roman_number[count-2] == 'C' && roman_number[count-3] == 'C')
                      invalidNum = true;         // Minimal representation requires that we do not allow 'CCCC'
                    else if (roman_number[count-2] == 'C'&& roman_number[count-1] == 'M') // 'CMC' is illegal combination
                      invalidNum = true;                     
                    else if (roman_number[count-1] == 'D') // 'DC' is illegal combination
                      invalidNum = true;                     
                    if (!invalidNum)
                      count++;
                    invalidNum = false;
                    i = 0;
                    break;
                  }
        case 'L': { // Legal and minimal combinations are 'MMXL', 'MMCXL', 'MMCDXL', 'MMMDL', 'MMCML', 'MMCCCL', 'CCL', 'MCDL'
                    while (!invalidNum && i < count)
                    {
                      if (roman_number[i-1] == 'X' || roman_number[i] == 'L' || roman_number[i] == 'V' || roman_number[i] == 'I')
                        invalidNum = true;       // 'L' and lower denominations, other that one 'X' for 'XL', can not precede. 
                      i++;  
                    }                             
                    if (!invalidNum)
                      count++;
                    invalidNum = false;
                    i = 0;
                    break;          
                  }
        case 'X': { // Legal and minimal combinations are 'MMMMX', 'MMDX', 'MMMCDX', 'IX', 'XX', 'XXX' 
                    while (!invalidNum && i < count)
                    {
                      if (roman_number[i] == 'L' || roman_number[i] == 'V' || roman_number[i-1] == 'I')
                        invalidNum = true;       // 'C', L' and lower denominations, other that one 'I' for 'IX', can not precede. 
                      i++;  
                    } 
                    if (roman_number[count-1] == 'X' && roman_number[count-2] == 'X' && roman_number[count-3] == 'X')
                      invalidNum = true;         // 'XXXX' is not minimal                   
                    if (roman_number[count-2] == 'X' && roman_number[count-1] == 'C')
                      invalidNum = true;         // 'XCX' is not legal    
                    if (!invalidNum)
                      count++;
                    invalidNum = false;
                    i = 0;
                    break;          
                  }
        case 'V': { // Legal and minimal combinations are 'MMMV', 'MMDV', 'MMCCV', 'MMXCV', 'MMXLV', 'XXXV', 'XLIV',  
                    while (!invalidNum && i < count)
                    {
                      if (roman_number[i] == 'V' || roman_number[i-1] == 'I')
                        invalidNum = true;       // 'V' and lower denomination 'I', other that one 'I' for 'IV', can not precede. 
                      i++;  
                    }                    
                    if (!invalidNum)
                      count++;
                    invalidNum = false;
                    i = 0;
                    break;                       
                  }
        case 'I': { // Legal and minimal combinations are 'MI', 'DI', 'CI', 'LI', 'XI', 'VI', 'II', 'III'
                    if (roman_number[count-2] =='I' && roman_number[count-1] == 'V')
                      invalidNum = true; // 'IVI' is not legal
                    if (roman_number[count-2] == 'I' && roman_number[count-1] == 'X')
                      invalidNum = true;         // 'IXI' is not legal    
                    if (roman_number[count-3] == 'I' && roman_number[count-2] == 'I' && roman_number[count-1] == 'I')
                      displayChar(roman_number, count);  // end of the number
                    if (!invalidNum)
                      count++;
                    invalidNum = false;
                    break;  
                  } 
      }
    
    }
  
  } while (roman_char != romans[7]);
  
  cout << endl;
  return 0;
}

void displayChar(char roman_number[], int count)
{
  roman_number[count] = '\0';
  for (int k = 0; k < count; k++)
    cout << roman_number[k];
  cout << endl;
  exit(0);
}

/* OUTPUT:

*/