/*
  Parke Lovett
  11/10/2022
  Buffer Gang
  This program adds 2 numbers while protecting against buffer overflow vulnerabilities
*/

#include <iostream>  // std::cin, std::cout
#include <string>    // std::string
#include <iomanip>   // std::setw, std::setfill
#include <algorithm> // std::reverse

                                        //Function declaration 
std::string addTwoNums(std::string num1, std::string num2);

int main() {                           // Main driver followed by original varibale declarations to hold both nums and strike counters
  std::string num1;
  std::string num2;
  int counter1 = 0;
  int counter2 = 0;

  std::cout << "Enter num1: ";
  std::getline(std::cin, num1);        // Prompt user for input and assign to first num variable

  while (num1.find_first_not_of("0123456789.") != std::string::npos || num1[0] == '-') {
    if (counter1 < 2) {
      std::cout << std::endl << "INVALID RE-Enter num: ";
      std::getline(std::cin, num1);
      counter1++;                     // While loop prompts user for another input if previous input is not positive or all digits
    } 
    else {                            // Abort program if user hits 3 strike rule
      std::cout << std::endl << "PROGRAM ABORT" << "\n" << std::endl;
      return;
    }
  }

  std::cout << "Enter num2: ";
  std::getline(std::cin, num2);       // Prompt user for input and assign to second num variable

  while (num2.find_first_not_of("0123456789.") != std::string::npos || num2[0] == '-') {
    if (counter2 < 2) {
      std::cout << std::endl << "INVALID RE-Enter num: ";
      std::getline(std::cin, num2);
      counter2++;                    // While loop prompts user for another input if previous input is not positive or all digits
    } 
    else {                          // Abort program if user hits 3 strike rule
      std::cout << std::endl << "PROGRAM ABORT" << "\n" << std::endl;
      return;
    }
  }

  int higherValueToUse = 0;

  if (num1.size() > num2.size())
    higherValueToUse = num1.size();  // This simply calculates which original num length is longer so we can use it to properly format
  else                               // our output. Our function solves this issue but it is not called until the end of the output
    higherValueToUse = num2.size();

                                    // Function call to add our two inputs and properly output to screen 
  std::cout << std::setfill(' ') << std::setw(higherValueToUse + 2) << std::right << num1 << std::endl;
  std::cout << "+" << std::setw(higherValueToUse + 1) << std::right << num2 << std::endl;
  std::cout << std::setfill('-') << std::setw(higherValueToUse + 2) << '-' << std::endl;
  std::cout << std::setfill(' ') << std::setw(higherValueToUse + 2) << addTwoNums(num1, num2) << std::endl;

return 0;                          // Successful program run

}

//#################################################################################################################
// Function: Long hand addition, reverses arrays to add each element properly then re-reverses to return properly #
// Param:    Two numbers to add together, typically from user input when used in main                             #
// Return:   The two numbers properly added together using the long hand "paper & pencil" addition algorithm      #
//#################################################################################################################

std::string addTwoNums(std::string num1, std::string num2)
{
    // Use std::reverse to reverse the two numbers to start addition from the 1's place
    std::string sum;
    std::reverse(num1.begin(), num1.end());                
    std::reverse(num2.begin(), num2.end());                

    // Resize the smaller number with 0's at the end to make adding each element in the arrays easier 
    if (num1.size() > num2.size())
        num2.resize(num1.size(), '0');
    else
        num1.resize(num2.size(), '0');

    // Add each element in the array.
    // We also have to convert the ASCII 
    // value for each char to its number to properly add
    int carryOverValue = 0;
    for (int i = 0; i < num1.size(); ++i){
        int total = (num1[i] - '0') + (num2[i] - '0') + carryOverValue;
        sum += (total % 10) + '0';
        carryOverValue = total / 10;
    }

    // Make sure the carry over value is taken care of in the leftmost column
    if (carryOverValue > 0)
        sum += (carryOverValue + '0');

    // Reverse the sum and return final results
    std::reverse(sum.begin(), sum.end());        
    return sum;        
}
