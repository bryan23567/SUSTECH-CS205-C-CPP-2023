#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "validation.h"
#include "mathematic.h"

int main(int argc, char const *argv[])
{

    if (argc > 4)
    {
        printf("The input cannot be interpret as numbers!\n");
        return 0;
    }

    char *a = (char *)argv[1];
    char *op = (char *)argv[2];
    char *b = (char *)argv[3];

    int loc_of_e_a = -1;
    int loc_of_e_b = -1;

    int loc_of_dot_a = -1;
    int loc_of_dot_b = -1;

    char *eTotal = NULL;

    char *e_of_a = "0";
    char *e_of_b = "0";

    if (!isANumber(a) || !(strcmp(op, "*") || strcmp(op, "+") || strcmp(op, "-") || strcmp(op, "/")) || !isANumber(b))
    {
        printf("The input cannot be interpret as numbers!\n");
        return 0;
    }

 
    a = deleteUnimportantChar(a);
    b = deleteUnimportantChar(b);

    if (isInt(a))
    {
        ;
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

        a = prefixDigitforA;
        if (isInt(a))
        {
            ;
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
        ;
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

        e_of_b = b + loc_of_e_b + 1;
        prefixDigit = (char *)malloc(sizeof(char *) * (loc_of_e_b));
        snprintf(prefixDigit, loc_of_e_b + 1, "%s", b);

        b = prefixDigit;
        if (isInt(b))
        {
            ;
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
        }
    }

    if (op == "-" || op == "+")
    {
        if (atoi(e_of_a) > atoi(e_of_b))
        {
            int change = atoi(e_of_a) - atoi(e_of_b);
            eTotal = e_of_b;

            int aaTrailing = 0;
            if (loc_of_dot_a > 0)
            {
                aaTrailing = strlen(a) - loc_of_dot_a - 1;
                a = delete_char(a, loc_of_dot_a);
            }
            a = deleteUnimportantChar(a);
            change -= aaTrailing;

            if (change < 0)
            {

                int offset = strlen(a[0] == '-' ? a + 1 : a) - abs(change);
                char *res;
                int k = 0;

                if (offset < 0)
                {
                    res = (char *)malloc(sizeof(char) * (abs(offset) + strlen(a) + 2));
                    if (a[0] == '-')
                    {
                        res[k++] = '-';
                        a = a + 1;
                    }
                    res[k++] = '0';
                    res[k++] = '.';
                    loc_of_dot_a = k - 1;
                    for (int i = 0; i < abs(offset); i++, k++)
                    {
                        res[k] = '0';
                    }
                    for (int i = 0; i < strlen(a); i++, k++)
                    {
                        res[k] = a[i];
                    }
                    a = res;
                }
                else if (offset == 0)
                {
                    res = (char *)malloc(sizeof(char) * (strlen(a) + 3));
                    if (a[0] == '-')
                    {
                        res[k++] = '-';
                        a = a + 1;
                    }
                    res[k++] = '0';
                    res[k++] = '.';
                    loc_of_dot_a = k - 1;
                    for (int i = 0; i < strlen(a); i++, k++)
                    {
                        res[k] = a[i];
                    }
                    a = res;
                }
                else
                {
                    if (a[0] == '-')
                    {
                        loc_of_dot_a = offset + 1;
                        a = insertDotAtIndex(a, loc_of_dot_a);
                    }
                    else
                    {
                        loc_of_dot_a = offset;
                        a = insertDotAtIndex(a, loc_of_dot_a);
                    }
                }
            }
            else
            {
                loc_of_dot_a = -1;
                a = addingMoreTrailingZero(a, change);
            }
        }
        else if (atoi(e_of_a) < atoi(e_of_b))
        {
            int change = atoi(e_of_b) - atoi(e_of_a);
            eTotal = e_of_a;

            int bbTrailing = 0;
            if (loc_of_dot_b > 0)
            {
                bbTrailing = strlen(b) - loc_of_dot_b - 1;
                b = delete_char(b, loc_of_dot_b);
            }
            b = deleteUnimportantChar(b);
            change -= bbTrailing;

            if (change < 0)
            {

                int offset = strlen(b[0] == '-' ? b + 1 : b) - abs(change);
                char *res;
                int k = 0;

                if (offset < 0)
                {
                    res = (char *)malloc(sizeof(char) * (abs(offset) + strlen(b) + 2));
                    if (b[0] == '-')
                    {
                        res[k++] = '-';
                        b = b + 1;
                    }
                    res[k++] = '0';
                    res[k++] = '.';
                    loc_of_dot_b = k - 1;
                    for (int i = 0; i < abs(offset); i++, k++)
                    {
                        res[k] = '0';
                    }
                    for (int i = 0; i < strlen(b); i++, k++)
                    {
                        res[k] = b[i];
                    }
                    b = res;
                }
                else if (offset == 0)
                {
                    res = (char *)malloc(sizeof(char) * (strlen(b) + 3));
                    if (b[0] == '-')
                    {
                        res[k++] = '-';
                        b = b + 1;
                    }
                    res[k++] = '0';
                    res[k++] = '.';
                    loc_of_dot_b = k - 1;
                    for (int i = 0; i < strlen(b); i++, k++)
                    {
                        res[k] = b[i];
                    }
                    b = res;
                }
                else
                {
                    if (b[0] == '-')
                    {
                        loc_of_dot_b = offset + 1;
                        b = insertDotAtIndex(b, loc_of_dot_b);
                    }
                    else
                    {
                        loc_of_dot_b = offset;
                        b = insertDotAtIndex(b, loc_of_dot_b);
                    }
                }
            }
            else
            {
                loc_of_dot_b = -1;
                b = addingMoreTrailingZero(b, change);
            }
        }
        else
        {
            eTotal = e_of_a;
        }
    }

    // printf("%s\n", a);
    // printf("%s\n", b);

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
        else if (aTrailing > bTrailing)
        {
            answer = insertDotAtIndex(answer, strlen(answer) - aTrailing);
        }
        else
        {
            if (aTrailing > 0)
            {
                answer = insertDotAtIndex(answer, strlen(answer) - aTrailing);
            }
        }

        if (eTotal == NULL)
        {
            printf("%s\n", answer);
            break;
        }
        printf("%se%s\n", answer, eTotal);
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

        else if (aTrailing > bTrailing)
        {
            answer = insertDotAtIndex(answer, strlen(answer) - aTrailing);
        }
        else
        {
            if (aTrailing > 0)
            {
                answer = insertDotAtIndex(answer, strlen(answer) - aTrailing);
            }
        }

        if (eTotal == NULL)
        {
            printf("%s\n", answer);
            break;
        }
        printf("%se%s\n", answer, eTotal);
        break;
    }
    case '*':
    {
        char *answer;
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
        int totalTrailing = aTrailing + bTrailing;
        answer = multiplication(a, b);

        if (totalTrailing == 0)
        {
            if (strcmp(addition(e_of_a, e_of_b), "0") == 0)
            {
                printf("%s\n", answer);
            }
            else
            {
                printf("%se%s\n", answer, addition(e_of_a, e_of_b));
            }

            break;
        }

        int offset = strlen(answer[0] == '-' ? answer + 1 : answer) - totalTrailing;
        char *res;
        int k = 0;

        if (offset < 0)
        {
            res = (char *)malloc(sizeof(char) * (abs(offset) + strlen(answer) + 2));
            if (answer[0] == '-')
            {
                res[k++] = '-';
                answer = answer + 1;
            }
            res[k++] = '0';
            res[k++] = '.';

            for (int i = 0; i < abs(offset); i++, k++)
            {
                res[k] = '0';
            }
        }
        else if (offset == 0)
        {
            res = (char *)malloc(sizeof(char) * (strlen(answer) + 3));
            if (answer[0] == '-')
            {
                res[k++] = '-';
                answer = answer + 1;
            }
            res[k++] = '0';
            res[k++] = '.';
        }
        else
        {
            if (answer[0] == '-')
            {
                if (addition(e_of_a, e_of_b) == "0")
                {
                    char *help = (char *)malloc(sizeof(char) * (offset + 1));
                    snprintf(help, offset + 2, "%s", insertDotAtIndex(answer, offset));
                    answer = answer + offset;
                    printf("-%s%s\n", help, reverse(deleteUnimportantChar(reverse(answer))));
                }
                else
                {
                    char *help = (char *)malloc(sizeof(char) * (offset + 1));
                    snprintf(help, offset + 2, "%s", insertDotAtIndex(answer, offset));
                    answer = answer + offset;
                    printf("-%s%se%s\n", help, reverse(deleteUnimportantChar(reverse(answer))), addition(e_of_a, e_of_b));
                }
            }
            else
            {
                if (strcmp(addition(e_of_a, e_of_b), "0") == 0)
                {
                    char *help = (char *)malloc(sizeof(char) * (offset + 1));
                    snprintf(help, offset + 2, "%s", insertDotAtIndex(answer, offset));
                    answer = answer + offset;
                    printf("%s%s\n", help, reverse(deleteUnimportantChar(reverse(answer))));
                }
                else
                {
                    char *help = (char *)malloc(sizeof(char) * (offset + 1));
                    snprintf(help, offset + 2, "%s", insertDotAtIndex(answer, offset));
                    answer = answer + offset;
                    printf("%s%se%s\n", help, reverse(deleteUnimportantChar(reverse(answer))), addition(e_of_a, e_of_b));
                }
            }

            break;
        }
        for (int i = 0; i < strlen(answer); i++, k++)
        {
            res[k] = answer[i];
        }
        res[k] = '\0';
        if (strcmp(addition(e_of_a, e_of_b), "0") == 0)
        {
            printf("%s\n", res);
        }
        else
        {
            printf("%se%s\n", res, addition(e_of_a, e_of_b));
        }

        break;
    }
    case '/':
    {
        if (strcmp(substraction(b, "0"), "0")==0)
        {
            printf("A number cannot be divided by zero.\n");
            break;
        }

        char *answer;
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
        int totalTrailing = bTrailing - aTrailing;
        a = deleteUnimportantChar(a);
        b = deleteUnimportantChar(b);
        answer = division(a, b);
        int sec_dot_loc = -1;
        if (isDecimal(answer))
        {
            for (int i = 0; i < strlen(answer); i++)
            {
                if (answer[i] == '.')
                {
                    sec_dot_loc = i;
                    break;
                }
            }
        }
        int cTrailing = 0;
        if (sec_dot_loc > 0)
        {
            cTrailing = strlen(answer) - sec_dot_loc - 1;
            answer = delete_char(answer, sec_dot_loc);
        }
        answer = deleteUnimportantChar(answer);
        totalTrailing -= cTrailing;
        if (totalTrailing == 0)
        {
            if (substraction(e_of_a, e_of_b) == "0")
            {
                printf("%s\n", answer);
            }
            else
            {
                printf("%se%s\n", answer, substraction(e_of_a, e_of_b));
            }

            break;
        }

        if (totalTrailing < 0)
        {

            int offset = strlen(answer[0] == '-' ? answer + 1 : answer) - abs(totalTrailing);
            char *res;
            int k = 0;

            if (offset < 0)
            {
                res = (char *)malloc(sizeof(char) * (abs(offset) + strlen(answer) + 2));
                if (answer[0] == '-')
                {
                    res[k++] = '-';
                    answer = answer + 1;
                }
                res[k++] = '0';
                res[k++] = '.';

                for (int i = 0; i < abs(offset); i++, k++)
                {
                    res[k] = '0';
                }
            }
            else if (offset == 0)
            {
                res = (char *)malloc(sizeof(char) * (strlen(answer) + 3));
                if (answer[0] == '-')
                {
                    res[k++] = '-';
                    answer = answer + 1;
                }
                res[k++] = '0';
                res[k++] = '.';
            }
            else
            {
                if (answer[0] == '-')
                {
                    if (strcmp(substraction(e_of_a, e_of_b), "0") == 0)
                    {
                        printf("-%s\n", insertDotAtIndex(answer + 1, offset));
                    }
                    else
                    {
                        printf("-%se%s\n", insertDotAtIndex(answer + 1, offset), substraction(e_of_a, e_of_b));
                    }
                }
                else
                {
                    if (strcmp(substraction(e_of_a, e_of_b), "0") == 0)
                    {
                        printf("%se\n", insertDotAtIndex(answer, offset));
                    }
                    else
                    {
                        printf("%se%s\n", insertDotAtIndex(answer, offset), substraction(e_of_a, e_of_b));
                    }
                }

                break;
            }
            for (int i = 0; i < strlen(answer); i++, k++)
            {
                res[k] = answer[i];
            }
            res[k] = '\0';
            if (strcmp(substraction(e_of_a, e_of_b), "0") == 0)
            {
                printf("%s\n", res);
            }
            else
            {
                printf("%se%s\n", res, substraction(e_of_a, e_of_b));
            }

            break;
        }

        if (strcmp(substraction(e_of_a, e_of_b), "0") == 0)
        {
            printf("%s\n", addingMoreTrailingZero(answer, totalTrailing));
        }
        else
        {
            printf("%se%s\n", addingMoreTrailingZero(answer, totalTrailing), substraction(e_of_a, e_of_b));
        }

        break;
    }
    default:
        printf("The input cannot be interpret as numbers!\n");
        break;
    }

    return 0;
};
