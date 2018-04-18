/*Sriparna Majumdar
Roman numerals
Project Euler: Problem 89 
https://projecteuler.net/problem=89
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
#include <fstream>

using namespace std;

int main ()
{
  int eng_num;
  ofstream input_file;
  input_file.open("inputNumbers.txt");
  for (int i = 1; i < 10000; i++)
    input_file << i << endl;
  input_file.close();
  ifstream input;
  input.open("inputNumbers.txt");
  
  cout << "This program will convert an english number into roman numerals\n";
  cout << "\nTraditional Roman numerals are made up of the following denominations:\n"
       << "I = 1\n"
       << "V = 5\n"
       << "X = 10\n"
       << "L = 50\n"
       << "C = 100\n"
       << "D = 500\n"
       << "M = 1000\n";
  cout << "The input file is inputNumbers.txt. The output file is RomanNumerals.txt.\n";
  ofstream output;
  output.open("RomanNumerals.txt");
  output << "A roman integer in the range 1-9999:\n";
  while (input >> eng_num)
  {
    if ((eng_num / 1000) >=1)   // For numbers between 1000 - 9999
    {
      for (int i = 0; i < (eng_num / 1000); i++)  
        output << 'M';                             
      eng_num = eng_num % 1000;
    }
  
    if (eng_num >= 900)    // For numbers between 900 - 999
    {
      output << 'C' << 'M';
      eng_num -= 900;  
    }
    if ((eng_num / 500) >=1) // For numbers between 500 - 899
    {
      output << 'D';
      eng_num -= 500;
    }
  
    if (eng_num >=490)     // For numbers between 490 - 499
    {
      output << 'C' << 'D';
      eng_num = eng_num - 400;
    }
  
    if ((eng_num / 100) >=1) // For numbers between 100 - 489
    {
      for (int i = 0; i < (eng_num / 100); i++)
        output << 'C';
      eng_num = eng_num % 100;
    }
  
    if (eng_num >= 90) // for numbers between 90 - 99
    {
      output << 'X' << 'C';
      eng_num -= 90;
    }
  
    if ((eng_num / 50) >=1) // For numbers between 50 - 90
    {
      output << 'L';
      eng_num -= 50;
    } 
  
    if (eng_num >=40)
    {
      output << 'X' << 'L';
      eng_num = eng_num - 40;
    }
  
    if ((eng_num / 10) >=1) // For numbers between 100 - 489
    {
      for (int i = 0; i < (eng_num / 10); i++) // For numbers between 10 - 39
        output << 'X';
      eng_num = eng_num % 10;
    }
  
    if (eng_num < 4) // For number 1-3
    {
      for (int i = 0; i < eng_num; i++)
        output << 'I';
    }
    
    else if (eng_num == 4)     
      output << 'I' << 'V';  // Number 4
    
    else if (eng_num >= 5 && eng_num < 9) // For numbers between 5 - 8 
    {
      output << 'V';
      eng_num -= 5;
      for (int i = 0; i < eng_num; i++)
        output << 'I';
    }
  
    else
      output << 'I' << 'X'; // number 9
  
    output << endl;
  }
  output.close();
  return 0;
}
