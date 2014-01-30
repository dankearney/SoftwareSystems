/* This program prompts the user to enter the cards
   played in a card game and prints the card count 

   Code borrowed from Head First C (O'Reilly)
   Written by Dan Kearney
*/

#include <stdlib.h>
#include <stdio.h>

/* Prompts user for input and saves input to given buffer
   User input is restricted to first two characters

   card_name: buffer where card name is stored
*/
void promptUser(char *card_name) 
{
  puts("Enter the card name:");
  scanf("%2s", card_name);
}

/* Gets card value from string input by user

   card_name: buffer containing user input
*/
int getCardValue(char *card_name) {
    switch (card_name[0]) {
    case 'J':
    case 'Q':
    case 'K':
      return 10;
    case 'A':
      return 11;
    default:
      return atoi(card_name);
    }    
}

/* determines if user value is valid

   val: computed value of user input
*/
int valid(int val) {
  return ((val > 0) && (val <= 11));
}

/* Adjusts count based on value

   val: value of card
   count: current card count
*/
void adjustCount(int val, int *count) {
  if ((val > 2) && (val < 7)) {
    (*count)++;
  } else if (val == 10) {
    (*count)--;
  }  
}

/* Entry point */
int main()
{
  char card_name[3];
  int count = 0;
  int val;
  while (card_name[0] != 'X') {
    promptUser(card_name);
    val = getCardValue(card_name);
    if (valid(val)) 
      adjustCount(val, &count);
    printf("Current count: %i\n\n", count);
  }
  return 0;
}
