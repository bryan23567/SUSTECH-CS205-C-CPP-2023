#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "validation.c"
#include "mathematic.c"

int main(int argc, char const *argv[])
{

    // char *a = (char *)argv[1];
    // char *op = (char *)argv[2];
    // char *b = (char *)argv[3];

    bool sign = false;

    int loc_of_e_a = -1;
    int loc_of_e_b = -1;

    int loc_of_dot_a = -1;
    int loc_of_dot_b = -1;

    char *e_for_dec_a = NULL;
    char *e_for_dec_b = NULL;

    char *e_tot = NULL;

    char *e_of_a = "0";
    char *e_of_b = "0";

    char *a = "-24352.0002";
    char *op = "-";
    char *b = "-3.3";

    if (!isANumber(a) || !(strcmp(op, "*") || strcmp(op, "+") || strcmp(op, "-") || strcmp(op, "/")) || !isANumber(b))
    {
        printf("The input cannot be interpret as numbers!\n");
        return 0;
    }

    if (atof(b) == 0)
    {
        printf("A number cannot be divied by zero.\n");
        return 0;
    }
    a = deleteUnimportantChar(a);
    b = deleteUnimportantChar(b);

    if (isInt(a))
    {
        // int i;
        // char *newA = (char *)malloc(sizeof(char *) * (strlen(a) + 3));
        // char *newAhelp = (char *)malloc(sizeof(char *) * (strlen(a) + 3));
        // for (i = 0; i < strlen(a); i++)
        // {
        //     newA[i] = a[i];
        // }
        // newA[i] = '.';
        // newA[i + 1] = '0';
        // snprintf(newAhelp, strlen(a) + 3, "%s", newA);
        // a = newAhelp;
    }
    else if (isDecimal(a))
    {
        for (int i = 0; i < strlen(a); i++)
        {
            if (a[i] == '.')
            {
                loc_of_dot_a = i;
                break;
            }
        }
        if (loc_of_dot_a > 0)
        {
            // a = delete_char(a, loc_of_dot_a);
        }
    }
    else if (isScientific(a))
    {
        char *prefixDigitforA;
        for (int i = 0; i < strlen(a); i++)
        {
            if (a[i] == 'e')
            {
                loc_of_e_a = i;
                break;
            }
        }
        // e_of_a = (char *)malloc(sizeof(char) * (strlen(a) - loc_of_e_a - 1));
        e_of_a = a + loc_of_e_a + 1;
        prefixDigitforA = (char *)malloc(sizeof(char *) * (loc_of_e_a));
        snprintf(prefixDigitforA, loc_of_e_a + 1, "%s", a);
        printf("%s\n", prefixDigitforA);
        a = prefixDigitforA;
        if (isInt(a))
        {
            // int i;
            // char *newA = (char *)malloc(sizeof(char *) * (strlen(a) + 3));
            // for (i = 0; i < strlen(a); i++)
            // {
            //     newA[i] = a[i];
            // }
            // newA[i] = '.';
            // newA[i + 1] = '0';
            // snprintf(a, strlen(a) + 3, "%s", newA);
        }
        else
        {
            for (int i = 0; i < strlen(a); i++)
            {
                if (a[i] == '.')
                {
                    loc_of_dot_a = i;
                    break;
                }
            }
            if (loc_of_dot_a > 0)
            {
                // a = delete_char(a, loc_of_dot_a);
            }
        }
    }
    if (isInt(b))
    {
        // int i;
        // char *newB = (char *)malloc(sizeof(char *) * (strlen(b) + 3));
        // char *newBhelp = (char *)malloc(sizeof(char *) * (strlen(b) + 3));
        // for (i = 0; i < strlen(b); i++)
        // {
        //     newB[i] = b[i];
        // }
        // newB[i] = '.';
        // newB[i + 1] = '0';
        // snprintf(newBhelp, strlen(b) + 3, "%s", newB);
        // b = newBhelp;
    }
    else if (isDecimal(b))
    {
        for (int i = 0; i < strlen(b); i++)
        {
            if (b[i] == '.')
            {
                loc_of_dot_b = i;
                break;
            }
        }
        // if (loc_of_dot_b > 0)
        // {
        //     // b = delete_char(b, loc_of_dot_b);
        // }
    }
    else if (isScientific(b))
    {
        char *prefixDigit;
        for (int i = 0; i < strlen(b); i++)
        {
            if (b[i] == 'e')
            {
                loc_of_e_b = i;
                break;
            }
        }
        // e_of_b = (char *)malloc(sizeof(char) * (strlen(b) - loc_of_e_b - 1));
        e_of_b = b + loc_of_e_b + 1;
        prefixDigit = (char *)malloc(sizeof(char *) * (loc_of_e_b));
        snprintf(prefixDigit, loc_of_e_b + 1, "%s", b);
        printf("%s\n", prefixDigit);
        b = prefixDigit;
        if (isInt(b))
        {
            // int i;
            // char *newB = (char *)malloc(sizeof(char *) * (strlen(b) + 3));
            // for (i = 0; i < strlen(b); i++)
            // {
            //     newB[i] = b[i];
            // }
            // newB[i] = '.';
            // newB[i + 1] = '0';
            // snprintf(b, strlen(b) + 3, "%s", newB);
        }
        else
        {
            for (int i = 0; i < strlen(b); i++)
            {
                if (b[i] == '.')
                {
                    loc_of_dot_b = i;
                    break;
                }
            }
            // if (loc_of_dot_b > 0)
            // {
            //     // b = delete_char(b, loc_of_dot_b);
            // }
        }
    }

    // char[]
    printf("%s\n", a);
    printf("%s\n", b);
    // if (strcmp(e_of_a, e_of_b) != 0)
    // {
    //     if (compare(e_of_a, e_of_b) == 1)
    //     {
    //         /* code */
    //     }
    // }

    switch (op[0])
    {
    case '+':
    {
        char *answer;
        // if (loc_of_dot_a > 0 || loc_of_dot_b > 0)
        // {
        int aTrailing = 0;
        int bTrailing = 0;
        if (loc_of_dot_a > 0)
        {
            aTrailing = strlen(a) - loc_of_dot_a - 1;
            a = delete_char(a, loc_of_dot_a);
        }
        if (loc_of_dot_b > 0)
        {
            bTrailing = strlen(b) - loc_of_dot_b - 1;
            b = delete_char(b, loc_of_dot_b);
        }
        if (bTrailing > aTrailing)
        {
            a = addingMoreTrailingZero(a, bTrailing - aTrailing);
        }
        if (aTrailing > bTrailing)
        {
            b = addingMoreTrailingZero(b, aTrailing - bTrailing);
        }

        answer = addition(a, b);

        if (bTrailing > aTrailing)
        {
            answer = insertDotAtIndex(answer, strlen(answer) - bTrailing);
        }

        if (aTrailing > bTrailing)
        {
            answer = insertDotAtIndex(answer, strlen(answer) - aTrailing);
        }

        printf("%s\n", answer);
    }
    break;
    case '-':
    {
        char *answer;
        // if (loc_of_dot_a > 0 || loc_of_dot_b > 0)
        // {
        int aTrailing = 0;
        int bTrailing = 0;
        if (loc_of_dot_a > 0)
        {
            aTrailing = strlen(a) - loc_of_dot_a - 1;
            a = delete_char(a, loc_of_dot_a);
        }
        if (loc_of_dot_b > 0)
        {
            bTrailing = strlen(b) - loc_of_dot_b - 1;
            b = delete_char(b, loc_of_dot_b);
        }
        if (bTrailing > aTrailing)
        {
            a = addingMoreTrailingZero(a, bTrailing - aTrailing);
        }
        if (aTrailing > bTrailing)
        {
            b = addingMoreTrailingZero(b, aTrailing - bTrailing);
        }

        answer = substraction(a, b);

        if (bTrailing > aTrailing)
        {
            answer = insertDotAtIndex(answer, strlen(answer) - bTrailing);
        }

        if (aTrailing > bTrailing)
        {
            answer = insertDotAtIndex(answer, strlen(answer) - aTrailing);
        }

        printf("%s\n", answer);
        break;
    }
    case '*':
    {
        int aTrailing = 0;
        int bTrailing = 0;
        if (loc_of_dot_a > 0)
        {
            aTrailing = strlen(a) - loc_of_dot_a - 1;
            a = delete_char(a, loc_of_dot_a);
        }
        if (loc_of_dot_b > 0)
        {
            bTrailing = strlen(b) - loc_of_dot_b - 1;
            b = delete_char(b, loc_of_dot_b);
        }
        printf("%s\n", multiplication(a, b));
        break;
    }
    case '/':
        printf("%s\n", division(a, b));
        break;
    default:

        break;
    }

    return 0;
};
