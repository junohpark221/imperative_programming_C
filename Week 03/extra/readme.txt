'daycal' is the program that tells us day of the date in 2018.
For example, when we type './daycal 1 1'(./daycal [day] [month]), it says 'Monday'.

First, when we just type './daycal', it tests the codes.
Second, when we type in the form, './daycal [day] [month]', it converts the strings into integers. However, if the intergers are bigger than 31 and 12 which are the maximum values of each days and months, it returns -1.
The returned values go to the 'check' function, which checks whether the date is exist or not. If the date is not exist, it returns Invalid. Checked dates go to the 'calculate' function and monthLength function. In this functions, the values are processed by mathematical way to find the day of date through remainder. Finally, in 'calculate' function, day of the date is returned to the main function, and it goes to the 'print' fuction.

This function is only for 2018.
