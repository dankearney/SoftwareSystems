/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5
#define DEBUG_MODE 0

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
	if (strstr(tracks[i], search_for)) {
	    printf("Track %i: '%s'\n", i, tracks[i]);
	}
    }
}

// Uses regex to match song
// Prints song index and title
// Prints regex error
// Code adapted from http://www.peope.net/old/regex.html
void match_song_re(int i, regex_t *regex) {
    int re_err_status = regexec(regex, tracks[i], 0, NULL, 0);
    if (!re_err_status) {
	printf("Track %i: '%s'\n", i, tracks[i]);
    } else if (re_err_status != REG_NOMATCH) {
	char msgbuf[100];        
	regerror(re_err_status, regex, msgbuf, sizeof(msgbuf));
	fprintf(stderr, "Regex match failed: %s\n", msgbuf);
	exit(1);
    }
}

// Compiles re and prints error upon failure
regex_t compile_re(char *pattern) {
    regex_t regex;
    if (regcomp(&regex, pattern, 0)) {
	fprintf(stderr, "Could not compile regex\n"); 
	exit(1); 
    }
    return regex;
}

// Prints track number and title, using regex to search.
void find_track_regex(char pattern[])
{
    // Compile re
    regex_t regex = compile_re(pattern);

    // Search for match
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
	match_song_re(i, &regex);
    }

    regfree(&regex);
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
	*ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];
    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);
    find_track_regex(search_for);
    return 0;
}
