#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "mathematic.h"

typedef struct division
{
    char *quotient;
    char *remainder;
} Division;

int compare(char *a, char *b) // if 1 then a > b, 0 a==b, -1 a< b
{
    if (a[0] == '-' && b[0] != '-')
    {
        return -1;
    }
    if (b[0] == '-' && a[0] != '-')
    {
        return 1;
    }

    if (strlen(a) > strlen(b))
    {
        return 1;
    }
    if (strlen(a) < strlen(b))
    {
        return -1;
    }
    for (int i = 0; i < strlen(a); i++)
    {
        if (a[i] > b[i])
        {
            return 1;
        }
        if (a[i] < b[i])
        {
            return -1;
        }
    }
    return 0;
}

char *reverse(char *num)
{
    char *rev = (char *)malloc(sizeof(char) * strlen(num));
    char *revRev = (char *)malloc(sizeof(char) * strlen(num));
    for (int i = 0; i < strlen(num); i++)
    {
        rev[strlen(num) - i - 1] = num[i];
    }

    snprintf(revRev, (strlen(num)) + 1, "%s", rev);

    return revRev;
    // get the length of the num, use it to compute the middle index
};
char *addition(char *a, char *b)
{
    if (a[0] == '-' && b[0] != '-') // -a+b
    {
        if (compare(a + 1, b) == 1)
        {
            char *result = subInteger(a + 1, b);
            char *res_new = (char *)malloc(sizeof(char) * (strlen(result) + 2));
            res_new[0] = '-';
            for (int i = 0; i < strlen(result); i++)
            {
                res_new[i + 1] = result[i];
            }
            res_new[strlen(result) + 1] = '\0';
            return res_new;
        }
        else
        {
            return subInteger(b, a + 1);
        }

    }
    if (b[0] == '-' && a[0] != '-') // a+(-b) = a-b
    {
        if (compare(a, b + 1) == 1)
        {
            return subInteger(a, b + 1);
        }
        else
        {
            char *result = subInteger(b + 1, a);
            char *res_new = (char *)malloc(sizeof(char) * (strlen(result) + 2));
            res_new[0] = '-';
            for (int i = 0; i < strlen(result); i++)
            {
                res_new[i + 1] = result[i];
            }
            res_new[strlen(result) + 1] = '\0';
            return res_new;
        }
    }
    if (a[0] == '-' && b[0] == '-') // -a+(-b) = -a-b
    {

        char *result = addInteger(a + 1, b + 1);
        char *res_new = (char *)malloc(sizeof(char) * (strlen(result) + 2));
        res_new[0] = '-';
        for (int i = 0; i < strlen(result); i++)
        {
            res_new[i + 1] = result[i];
        }
        res_new[strlen(result) + 1] = '\0';
        return res_new;
    }

    return addInteger(a, b);
}
char *addInteger(char *a, char *b)
{
    char *reva = reverse(a);
    char *revb = reverse(b);

    char *result = (char *)malloc(sizeof(char) * (strlen(a) > strlen(b) ? strlen(a) + 2 : strlen(b) + 2));

    int carry = 0;
    if (strlen(a) < strlen(b))
    {
        for (int i = 0; i < strlen(a); i++)
        {
            int res = (reva[i] - '0') + (revb[i] - '0') + carry;
            carry = res / 10;
            res = res % 10;
            result[i] = res + '0';
        }
        for (int i = strlen(a); i < strlen(b); i++)
        {
            int res = (revb[i] - '0') + carry;
            carry = res / 10;
            res = res % 10;
            result[i] = res + '0';
        }
        for (int i = strlen(b); i < strlen(b) + 1; i++)
        {
            result[i] = carry + '0';
        }
    }
    else
    {
        for (int i = 0; i < strlen(b); i++)
        {
            int res = (reva[i] - '0') + (revb[i] - '0') + carry;
            carry = res / 10;
            res = res % 10;
            result[i] = res + '0';
        }
        for (int i = strlen(b); i < strlen(a); i++)
        {
            int res = (reva[i] - '0') + carry;
            carry = res / 10;
            res = res % 10;
            result[i] = res + '0';
        }
        for (int i = strlen(a); i < strlen(a) + 1; i++)
        {
            result[i] = carry + '0';
        }
    }

    result[strlen(a) > strlen(b) ? strlen(a) + 1 : strlen(b) + 1] = '\0';
    int deleteSuffix = 0;
    char *answer = reverse(result);
    for (int i = 0; i < strlen(answer); i++)
    {
        if (answer[i] != '0' || i == strlen(answer) - 1)
        {
            deleteSuffix = i;
            break;
        }
    }
    answer = answer + deleteSuffix;
    return answer;
};

char *substraction(char *a, char *b)
{

    if (strcmp(a, b) == 0)
    {
        return "0";
    }
    if (a[0] == '-' && b[0] != '-') // -a-b
    {
        char *result = addInteger(a + 1, b);
        char *res_new = (char *)malloc(sizeof(char) * (strlen(result) + 2));
        res_new[0] = '-';
        for (int i = 0; i < strlen(result); i++)
        {
            res_new[i + 1] = result[i];
        }
        res_new[strlen(result) + 1] = '\0';

        return res_new;
    }
    if (b[0] == '-' && a[0] != '-') // a-(-b) = a+b
    {
        return addInteger(b + 1, a);
    }
    if (a[0] == '-' && b[0] == '-') // -a-(-b) = -a+b
    {
        if (compare(a + 1, b + 1) == 1)
        {
            char *result = subInteger(a + 1, b + 1);
            char *res_new = (char *)malloc(sizeof(char) * (strlen(result) + 2));
            res_new[0] = '-';
            for (int i = 0; i < strlen(result); i++)
            {
                res_new[i + 1] = result[i];
            }
            res_new[strlen(result) + 1] = '\0';
            return res_new;
        }
        else
        {
            return subInteger(b + 1, a + 1);
        }
    }
    if (compare(a, b) == 1)
    {
        return subInteger(a, b);
    }
    else
    {
        char *result = subInteger(b, a);
        char *res_new = (char *)malloc(sizeof(char) * (strlen(result) + 2));
        res_new[0] = '-';
        for (int i = 0; i < strlen(result); i++)
        {
            res_new[i + 1] = result[i];
        }
        res_new[strlen(result) + 1] = '\0';
        return res_new;
    }
}

char *subInteger(char *a, char *b) // a>b
{

    bool carry = false;
    char *reva = reverse(a);
    char *revb = reverse(b);

    char *result = (char *)malloc(sizeof(char) * (strlen(a) + 1));

    for (int i = 0; i < strlen(revb); i++)
    {
        int first = reva[i] - '0';
        int second = revb[i] - '0';
        if (carry && first > 0)
        {
            first--;
            carry = false;
        }
        if (carry && first == 0)
        {
            first = 9;
            carry = true;
        }
        if (first < second)
        {
            first += 10;
            carry = true;
        }

        result[i] = (first - second) + '0';
    }

    for (int i = strlen(revb); i < strlen(reva); i++)
    {
        int first = reva[i] - '0';
        if (carry && first > 0)
        {
            first--;
            carry = false;
        }
        result[i] = first + '0';
    }
    
    result[strlen(a)] = '\0';
    int deleteSuffix = 0;
    char *answer = reverse(result);
    for (int i = 0; i < strlen(answer); i++)
    {
        if (answer[i] != '0' || i == strlen(answer) - 1)
        {
            deleteSuffix = i;
            break;
        }
    }
    answer = answer + deleteSuffix;
    return answer;
}

char *multiplication(char *a, char *b)
{
    bool sign = false;
    char *answer;
    if (a[0] == '-' && b[0] == '-')
    {
        answer = multiplyInt(a + 1, b + 1);
    }
    else if (a[0] == '-')
    {
        sign = true;
        answer = multiplyInt(a + 1, b);
    }
    else if (b[0] == '-')
    {
        sign = true;
        answer = multiplyInt(a, b + 1);
    }
    else
    {
        answer = multiplyInt(a, b);
    }

    if (sign)
    {
        char *res_new = (char *)malloc(sizeof(char) * (strlen(answer) + 2));
        res_new[0] = '-';
        for (int i = 0; i < strlen(answer); i++)
        {
            res_new[i + 1] = answer[i];
        }
        res_new[strlen(answer) + 1] = '\0';

        return res_new;
    }
    return answer;
}

char *multiplyInt(char *a, char *b)
{

    char *reva = reverse(a);
    char *revb = reverse(b);

    int *revres = (int *)calloc(strlen(a) + strlen(b), sizeof(int));
    char *revresChar = (char *)malloc((strlen(a) + strlen(b) + 1) * sizeof(char));

    for (int i = 0; i < strlen(a); i++)
    {
        for (int j = 0; j < strlen(b); j++)
        {

            revres[i + j] = revres[i + j] + (reva[i] - '0') * (revb[j] - '0');
        }
    }

    for (int i = 0; i < strlen(a) + strlen(b); i++)
    {
        if (revres[i] > 9)
        {
            revres[i + 1] = revres[i + 1] + revres[i] / 10;
            revres[i] = revres[i] % 10;
        }
    }
    for (int i = strlen(a) + strlen(b) - 1; i >= 0; i--)
    {
        revresChar[i] = revres[i] + '0';
    }
    revresChar[strlen(a) + strlen(b)] = '\0';
    free(revres);
    int deleteSuffix = 0;
    char *answer = reverse(revresChar);
    for (int i = 0; i < strlen(answer); i++)
    {
        if (answer[i] != '0' || i == strlen(answer) - 1)
        {
            deleteSuffix = i;
            break;
        }
    }
    answer = answer + deleteSuffix;

    return answer;
}

char *division(char *a, char *b)
{
    bool sign = false;
    char *answer;
    if (a[0] == '-' && b[0] == '-')
    {
        answer = divInteger(a + 1, b + 1);
    }
    else if (a[0] == '-')
    {
        sign = true;
        answer = divInteger(a + 1, b);
    }
    else if (b[0] == '-')
    {
        sign = true;
        answer = divInteger(a, b + 1);
    }
    else
    {
        answer = divInteger(a, b);
    }

    if (sign)
    {
        char *res_new = (char *)malloc(sizeof(char) * (strlen(answer) + 2));
        res_new[0] = '-';
        for (int i = 0; i < strlen(answer); i++)
        {
            res_new[i + 1] = answer[i];
        }
        res_new[strlen(answer) + 1] = '\0';

        return res_new;
    }
    return answer;
}

Division oneTimeDiv(char *a, char *b) // (a/b)
{
    Division result;
    result.quotient = "0";
    result.remainder = "";

    if (subInteger(b, "0") == "0")
    {
        result.quotient = "wrong";
    }
    else if (subInteger(a, "0") == "0")
    {
        result.quotient = "0";
    }
    else
    {
        for (char *i = "0";; i = addInteger(i, "1"))
        {
            if ((compare(multiplyInt(b, i), a) == -1 || compare(multiplyInt(b, i), a) == 0) && (compare(multiplyInt(b, addInteger(i, "1")), a) == 1))
            {
                result.quotient = i;
                result.remainder = subInteger(a, multiplyInt(b, i));
                break;
            }
        }
    }

    return result;
}
char *divInteger(char *num, char *div)
{
    char *result = (char *)malloc(sizeof(char) * (int)abs((int)strlen(div) - (int)strlen(num) + 10));
    Division temp;
    temp = oneTimeDiv(num, div);
    if (temp.quotient == "wrong")
    {
        return temp.quotient;
    }
    int i = 0;
    for (; i < strlen(temp.quotient); i++)
    {
        result[i] = temp.quotient[i];
    }

    if (strcmp(temp.remainder, "0") == 0)
    {
        result[i] = '\0';
        return result;
    }
    result[i++] = '.';
    while (strcmp(temp.remainder, "0") != 0 && i < (int)abs((int)strlen(div) - (int)strlen(num) + 9))
    {
        char *decNum = (char *)malloc(sizeof(char) * (strlen(temp.remainder) + 2));
        int k;
        for (k = 0; k < strlen(temp.remainder); k++)
        {
            decNum[k] = temp.remainder[k];
        }
        for (; k < strlen(temp.remainder) + 1; k++)
        {
            decNum[k] = '0';
        }

        decNum[k] = '\0';
        temp = oneTimeDiv(decNum, div);
        free(decNum);
        for (int j = 0; j < strlen(temp.quotient); i++, j++)
        {
            result[i] = temp.quotient[j];
        }
    }

    result[i] = '\0';
    return result;
}
