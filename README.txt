* Pietro Baggetta
* 1092160
* March 28, 2022
* CIS*3490 Assignment 4

*** To compile ***
    - Type 'make all'.

*** To clean all object files and execuatbles ***
    - Type 'make clean'.

*** To run the program ***
    - First make sure the program is compiled with the command 'make all'.
    - Then run the program by typing './main'.

Before starting the program:
    - Ensure that there are text files in the same directory as the main.c file, or else the
    program will not be able to execute.
    - data_A4_Q1.txt is a hardcoded file name into the program, so make sure for option 1 and 2, 
    this file nameing is used.
    - Ensure the formatting of the option 3 text files is the same formatting as the text file 
    data_A4_Q2_1.txt or data_A4_Q2_2.txt.

Program Files:
    - main.c:
        > This C program file holds the main function which calls each respective algorithm depending if
          option 1, 2 or 3 are chosen.

    - Option 1 / P11.c:
        > This c program file holds the code for the optimal BST using dynamic programming technique.
        > This program will read in the file data_A4_Q1.txt and create an average number table and root
          table for the text read in.
        > It will then prompt the user to enter a search word, then attempt to fine the key in the text
          using BST dynamic programming, and if the word is not found then it will tell the user so.
        > If a word is found it will tell the user the tree it had to go down and what words are passed
          in that time.

    - Option 2 / P12.c:
        > This c program file has the same functionality as P11.c but it uses the optimal BST using
          Greedy Technique.
    
    - Option 3 / P2.c:
        > This c program file reads a value 'n' and 2 square matricies. The matricies must be compatible
          and must be able to be solved, since this code is for stable marriage.
          ***FOR FORMATTING OF THE FILE LOOK INTO data_A4_Q2_1.txt OR data_A4_Q2_2.txt***
        > The program will read in the file, get the n value from the matrix, then store the two different
          matricies into one 2D array.
        > The program will then itterate through the "males" and propose to each "woman", until every male
          is matched up with a female and there are none left single.
        > The output of this program shows the user which pairs have been put together. The 1 at row i
          and column j represents pairing i and j are married.
