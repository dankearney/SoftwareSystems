/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *tracks[] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};

int totalLen(char *array[], int n) {
    int out = 0;
    int i = 0;
    for (i=0; i<n; i++) {
	out += strlen(array[i]);
    }
    return out;
}

/* Returns a heap-allocated string that contains the strings 
   from the given array, joined up with no spaces between.
*/
char *strjoin(char *array[], int n)
{
    int numChars = totalLen(array, n) + 1;
    char *buf = malloc(sizeof(char)*numChars);
    char *joined = buf;

    int i=0;
    for (i=0; i<n; i++) {
	strcpy(joined, array[i]);
	joined += strlen(array[i]);
    }
    return buf;
}

int main (int argc, char *argv[])
{
    char *s = strjoin(tracks, 5);
    printf("%s\n", s);
    return 0;
}
