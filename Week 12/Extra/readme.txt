This program records the drawing on the SDL.
My program is consits of 'draw.c', 'draw.h', 'record.c', 'record.h' and 'test.c' for testing. And main file is 'record.c'.


Basically, although there is not any memory leak on test.c, but there are memory leaks on draw.c like a program for another 50%, sketch.c.


You can compile display.c and draw.c together to use the recording program, and it can be started with ./draw.
To test the program, you can compile display.c and test.c together and it can be started with ./test.


This program always asks you to choose one of the choice such as '1 to 8' and 'yes or no'. So you should answer the program's question well to run the program.


There are 7 things that the program can do.
First one is moving. You can move your current point.
Second thing is drawing line.
Third one is adding clear in the storage. So you can record clearing.
Fourth one is clearing all. It is similar with restart the program.
Fifth one is changing colour. Because it is hard to know which proportion of red, green and blue means the colour in real world, it just shows choices to us. So it will be possible to add choices in future.
Sixth one is adding pause. So, you can add pause in recording to looks like an animation or just stop for a while.
Last one is showing recorded file. By selecting this choice, you can show the recorded file in storage until now.


There are pause functions between the cleaning, drawing line, showing recorded file and before finishing from 1 second to 5 seconds. So it will be good to wait enough.


Also, after choose drawing line and input the point that you want to draw, there is mid-drawing to show how have you drawn until now, and how dose your inputed drawing looks like.
