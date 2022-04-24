# IZP1

My first project in subject Introduction to Programming Systems (IZP).

The purpose of the project is to create a program that receives a set of passwords on input and verifies for each of them whether the password meets all (fixed) required rules. The passwords that pass the check will be output, the others will be discarded.
-------

> ./pwcheck LEVEL PARAM [--stats] 

LEVELS:
   - Integer in the interval [1,4]
   1. Password contains at least 1 uppercase and 1 lowercase letter.
    2. The password contains characters from at least X groups (if the number X is greater than 4, this means all groups). The groups considered are:
          - lowercase letters (a-z)
          - uppercase letters (A-Z)
          - numbers (0-9)
          - special characters (at least non-alphanumeric characters from the ASCII table in positions 32-126 must be supported)
    3. The password does not contain the same sequence of characters of length at least X.
    4. The password does not contain two identical substrings of length at least X.
    
PARAM
  - positive integer that specifies an additional rule parameter (LEVEL 2, 3 or 4)

--stats
  - if specified, determines that summary statistics of the analyzed passwords should be displayed at the end of the program.
