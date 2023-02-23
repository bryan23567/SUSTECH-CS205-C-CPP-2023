#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "add.h"
void reverse(char *num)
{
  // get the length of the num, use it to compute the middle index
  int length = strlen(num);
  int middle = length / 2;

  // used to swap characters on either side of the num
  char temp;

  // Swaps characters at the beginning of the num with their corresponding 
  // character at the end of the num... i.e. the first character with the 
  // last character, the second character with the second last character, and 
  // on and on until the middle of the num is reached, at which point the 
  // num will be reversed!
  for (int i = 0; i < middle; i++)
  {
    temp = num[i];

    num[i] = num[length - i - 1];

    num[length - i - 1] = temp;
  }
}

char *addPositiveInteger(char *a, char *b)
{
    char *reva = a;
    char *revb = b;
    // a[0] = '9';
    reverse(reva);
    reverse(revb);
    // printf("%s\n",a);
    char *result = (char *)malloc(sizeof(char) * (strlen(a) > strlen(b) ? strlen(a) + 1 : strlen(b) + 1));

    int carry = 0;
    if (strlen(a) < strlen(b))
    {
        for (int i = 0; i < strlen(a); i++)
        {
            int res = (reva[i] - '0') + (revb[i] - '0') + carry;
            carry = res / 10;
            res = res % 10;
            result[i] = res+'0';
        }
        for (int i = strlen(a); i < strlen(b); i++)
        {
            int res = (revb[i] - '0') + carry;
            carry = res / 10;
            res = res % 10;
            result[i] = res+'0';
        }
        for (int i = strlen(b); i < strlen(b) + 1; i++)
        {
            result[i] = carry+'0';
        }
    }
    else
    {
        for (int i = 0; i < strlen(b); i++)
        {
            int res = (reva[i] - '0') + (revb[i] - '0') + carry;
            carry = res / 10;
            res = res % 10;
            result[i] = res+'0';
        }
        for (int i = strlen(b); i < strlen(a); i++)
        {
            int res = (reva[i] - '0') + carry;
            carry = res / 10;
            res = res % 10;
            result[i] = res+'0';
        }
        for (int i = strlen(a); i < strlen(a) + 1; i++)
        {
            result[i] = carry+'0';
        }
    }
    reverse(result);
    return result;
};