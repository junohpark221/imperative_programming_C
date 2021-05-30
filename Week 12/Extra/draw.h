struct display;
typedef struct display display;

display *newDisplay(char *title, int width, int height);

void line(display *d, int x0, int y0, int x1, int y1);

void colour(display *d, int r, int g, int b, int a);

void pause(display *d, int ms);

void clear(display *d);

void end(display *d);
