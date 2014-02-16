/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5
#define DEBUG_MODE 1

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

void match_song(int i, regex_t *regex) {
    int re_err_status = regexec(regex, tracks[i], 0, NULL, 0);
    if (!re_err_status) {
	printf("%i: %s\n", i, tracks[i]);
    } else if (re_err_status != REG_NOMATCH) {
	char msgbuf[100];        
	regerror(re_err_status, regex, msgbuf, sizeof(msgbuf));
	fprintf(stderr, "Regex match failed: %s\n", msgbuf);
	exit(1);
    }
}

void compile_re(regex_t *regex, char *pattern) {
    int re_err_status = regcomp(regex, pattern, 0);
    if (re_err_status) { 
	fprintf(stderr, "Could not compile regex\n"); 
	exit(1); 
    }
}

// Prints track number and title, using regex to search.
// Code adapted from http://www.peope.net/old/regex.html
void find_track_regex(char pattern[])
{
    regex_t regex;

    // Compile re
    compile_re(&regex, pattern);

    // Search for match
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
	match_song(i, &regex);
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
    switch (DEBUG_MODE) {
    case 0:
	/* take input from the user and search */
	printf("Search for: ");
	fgets(search_for, 80, stdin);
	rstrip(search_for);

	find_track(search_for);
	//find_track_regex(search_for);

	return 0;

    case 1:
    {
	char regex[] = "[A-S]";
	find_track_regex(regex);
	return 0;
    }
    default:
	return 0;
  }
}
