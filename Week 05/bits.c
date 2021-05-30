#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// Construct a colour from its components.
unsigned int colour(unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
    unsigned int c = (r << 24) | (g << 16) | (b << 8) | a;
    return c;
}

// Unpack a colour into its components.
void components(unsigned int c, int rgba[4]) {
    rgba[0] = (c >> 24) & 0xFF;
    rgba[1] = (c >> 16) & 0xFF;
    rgba[2] = (c >> 8) & 0xFF;
    rgba[3] = c & 0xFF;
}

// Form a 3D point from three signed 10-bit integers.
unsigned int point(int x, int y, int z) {
    unsigned int x1 = 0, y1 = 0, z1 = 0;
    if(x < 0) x1 = (x & 0x000003FF);
    else x1 = (x & 0x00000FFF);
    if(y < 0) y1 = (y & 0x000003FF);
    else y1 = (y & 0x00000FFF);
    if(z < 0) z1 = (z & 0x000003FF);
    else z1 = (z & 0x00000FFF);

    unsigned int c = (x1 << 20) | (y1 << 10) | z1;
    return c;
}

// Separate a position into three signed 10-bit coordinates.
void coordinates(unsigned int p, int xyz[3]) {
    xyz[0] = ((~0 >> 20) | p) + 1;
    xyz[1] = ((~0 >> 10) | p) + 1;
    xyz[2] = ((~0) | p) + 1;
    printf("%d %d %d\n", xyz[0], xyz[1], xyz[2]);
}

void bin_plus(int n, char s[33]) {
    int exp = 0;
    for(int a = 0; a < 32; a++) {
        if(n > (2^a)) break;
        exp++;
    }
    for(int b = 0; b < 32; b++) {
        if(b == (33 - exp)) {
            s[33 - exp] = n % 2;
            n = n / 2;
        }
        else s[b] = 0;
    }
    s[32] = NULL;
}

// Convert an int into a binary string of 32 bits.
void binary(int n, char s[33]) {
    if(n == 0) {
        for(int i=0; i < 32; i++) s[i] = '0';
        s[32] = NULL;
    }
    else if(n > 0) bin_plus(n, s);
}

// Convert an int into a hex string of 8 hex digits.
void hex(int n, char s[9]) {
    sprintf(s, "%x", n);
}

// ----------------------------------------------------------------------------
// Testing and user interface.

// Tests 1 to 5
void testColour() {
    assert(colour(255,0,0,0) == 0xFF000000);
    assert(colour(0,255,0,0) == 0x00FF0000);
    assert(colour(0,0,255,0) == 0x0000FF00);
    assert(colour(0,0,0,255) == 0x000000FF);
    assert(colour(1,2,3,4) == 0x01020304);
}

// Do a single test of the components function with given input and output.
bool checkComponents(unsigned int c, int r, int g, int b, int a) {
    int rgba[4];
    for (int i=0; i<4; i++) rgba[i] = -1;
    components(c, rgba);
    return rgba[0] == r && rgba[1] == g && rgba[2] == b && rgba[3] == a;
}

// Tests 6 to 10
void testComponents() {
    assert(checkComponents(0xFF000000, 255, 0, 0, 0));
    assert(checkComponents(0x00FF0000, 0, 255, 0, 0));
    assert(checkComponents(0x0000FF00, 0, 0, 255, 0));
    assert(checkComponents(0x000000FF, 0, 0, 0, 255));
    assert(checkComponents(0x01020304, 1, 2, 3, 4));
}

// Tests 11 to 16
void testPoint() {
    assert(point(0,0,0) == 0);
    assert(point(1,3,7) == 0x00100C07);
    assert(point(1,3,-7) == 0x00100FF9);
    assert(point(1,-3,7) == 0x001FF407);
    assert(point(-1,3,7) == 0x3FF00C07);
    assert(point(-1,-3,-7) == 0x3FFFF7F9);
}

// Do a single test of the coordinates function with given input and output.
bool checkCoordinates(unsigned int p, int x, int y, int z) {
    int xyz[3];
    for (int i=0; i<3; i++) xyz[i] = 1000000000;
    coordinates(p, xyz);
    return xyz[0] == x && xyz[1] == y && xyz[2] == z;
}

// Tests 17 to 22
void testCoordinates() {
    assert(checkCoordinates(0, 0, 0, 0));
    assert(checkCoordinates(0x00100C07, 1, 3, 7));
    assert(checkCoordinates(0x00100FF9, 1, 3, -7));
    assert(checkCoordinates(0x001FF407, 1, -3, 7));
    assert(checkCoordinates(0x3FF00C07, -1, 3, 7));
    assert(checkCoordinates(0x3FFFF7F9, -1, -3, -7));
}

// Do a single test of the binary function with given input and output.
// Initialise s with incorrect values to give predictable results.
bool checkBinary(int in, char out[33]) {
    char s[33];
    for (int i=0; i<33; i++) s[i] = 'x';
    binary(in, s);
    for(int j=0; j<33; j++) printf("%c", s[j]);
    printf("\n");
    return strcmp(s, out) == 0;
}

// Tests 23 to 35
void testBinary() {
    assert(checkBinary(0, "00000000000000000000000000000000"));
    assert(checkBinary(1, "00000000000000000000000000000001"));
    assert(checkBinary(2, "00000000000000000000000000000010"));
    assert(checkBinary(3, "00000000000000000000000000000011"));
    assert(checkBinary(4, "00000000000000000000000000000100"));
    assert(checkBinary(100, "00000000000000000000000001100100"));
    assert(checkBinary(2147483647, "01111111111111111111111111111111"));
    assert(checkBinary(-1, "11111111111111111111111111111111"));
    assert(checkBinary(-2, "11111111111111111111111111111110"));
    assert(checkBinary(-3, "11111111111111111111111111111101"));
    assert(checkBinary(-4, "11111111111111111111111111111100"));
    assert(checkBinary(-100, "11111111111111111111111110011100"));
    assert(checkBinary(-2147483648, "10000000000000000000000000000000"));
}

// Do a single test of the hex function with given input and output.
bool checkHex(int in, char out[9]) {
    char s[9];
    for (int i=0; i<9; i++) s[i] = 'x';
    hex(in, s);
    return strcmp(s, out) == 0;
}

// Tests 36 to 50
void testHex() {
    assert(checkHex(0, "00000000"));
    assert(checkHex(1, "00000001"));
    assert(checkHex(2, "00000002"));
    assert(checkHex(10, "0000000A"));
    assert(checkHex(15, "0000000F"));
    assert(checkHex(16, "00000010"));
    assert(checkHex(100, "00000064"));
    assert(checkHex(2147483647, "7FFFFFFF"));
    assert(checkHex(-1, "FFFFFFFF"));
    assert(checkHex(-2, "FFFFFFFE"));
    assert(checkHex(-3, "FFFFFFFD"));
    assert(checkHex(-4, "FFFFFFFC"));
    assert(checkHex(-16, "FFFFFFF0"));
    assert(checkHex(-100, "FFFFFF9C"));
    assert(checkHex(-2147483648, "80000000"));
}

void test() {
    testColour();
    testComponents();
    testPoint();
    testCoordinates();
    testBinary();
    testHex();
    printf("All tests pass");
}

// Print a number in binary.
void printBinary(int n) {
    char s[33];
    binary(n, s);
    printf("%s\n", s);
}

// Print a number in hex.
void printHex(int n) {
    char s[9];
    hex(n, s);
    printf("%s\n", s);
}

// Print a number in hex or binary, or run tests.
int main(int n, char *args[n]) {
    if (n == 1) test();
    else if (n == 3 && strcmp(args[1],"-h") == 0) printHex(atoi(args[2]));
    else if (n == 3 && strcmp(args[1],"-b") == 0) printBinary(atoi(args[2]));
    else printf("Use:   ./bits   or   ./bits -h n   or   ./bits -b n");
    return 0;
}
