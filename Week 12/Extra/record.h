#include "draw.h"

struct storage;
typedef struct storage storage;

void midDraw(storage *s, int prevLen);

void getValue(storage *s);

void moveMain(storage *s);

void lineMain(storage *s);

void clearMain(storage *s);

void restartMain(storage *s);

void selRGB(storage *s);

void selA(storage *s);

void colourMain(storage *s);

int recordMove(storage *s, int i);

int recordLine(storage *s, display *d, int i);

int recordClear(display *d, int i);

int recordColour(storage *s, display *d, int i);

int recordPause(storage *s, display *d, int i);

void recordMain(storage *s);

void mainMenu(storage *s);
