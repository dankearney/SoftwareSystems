/* Example code for Software Systems at Olin College.
Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Returns a heap-allocated string with length n, with
// the given string in the middle, surrounded by fillchar.
//
// For example, if s is allen, n is 10 and fillchar is .
// the result is ..allen... 

char *center(char *s, int n, char fillchar)
{

    if (strlen(s) > n) {
	fprintf(stderr, "n must be larger than string");
	exit(1);
    } 

    char *centered = malloc((n+1) * sizeof(char));
    int startWord = (n - strlen(s)) / 2;

    int i;
    int j = 0;
    for (i=0; i<n; i++) {
	if ((i >= startWord) && (i < startWord + strlen(s))) {
	    centered[i] = s[j];
	    j++;
	} else {
	    centered[i] = fillchar;
	}
    }
    return centered;
}


int main (int argc, char *argv[])
{
    char *s = center("Software", 30, '.');
    printf("%s\n", s);

    char *s2 = center("Systems", 31, '-');
    printf("%s\n", s2);

    char *s3 = center("S", 1, '*');
    printf("%s\n", s3);

    char *s4 = center("S", 2, '*');
    printf("%s\n", s4);

    char *s5 = center("Exam 1", 4, '^');
    printf("%s\n", s5);

    return 0;
}
