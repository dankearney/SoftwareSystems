#include <stdlib.h>
#include <stdio.h>

int main()
{
  char card_name[3];
  int count = 0;
  while (card_name[0] != 'X') {
    puts("Enter the card name:");
    scanf("%2s", card_name);
    int val = 0;
    switch (card_name[0]) {
    case 'J':
    case 'Q':
    case 'K':
      val = 10;
      break;
    case 'A':
      val = 11;
      break;
    default:
      val = atoi(card_name);
      if ((val <= 0) || (val > 10)) {
	continue;
      }
    }  
    if ((val > 2) && (val < 7)) {
      count++;
    } else if (val == 10) {
      count--;
    }
    printf("Current count: %i\n\n", count);
  }
  return 0;
}
