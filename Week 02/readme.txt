I make a program that distinct whether three sides can make right triangle or not, through pythagoras theorem.

In the main function, I first set that this program only can work, if the number of input value with './pythagoras' is three. If not, the messages that tell the usage of the program will output.
When the program can be worked with appropriate number of value, then the values in arraies will go to the compare function. In the function, the values will be changed by int form through the 'atoi'. Then, they will be compared to find the maximum value which will be stored in 'max'. Then, the values, max and others, will go to the distinct function.
In the function, by using the max value, it is distincted that the values satisfy the pythagoras theorem. Then, the function return 1 if it satisfy the theorem, or return 0 if it does not satisfy the theorem. Also, if all three values are not natural number,compare function will return -1 to main function.
The returned value, -1 or 0 or 1 will go to the print function through the main fuction. Each values will indicates different answer.
