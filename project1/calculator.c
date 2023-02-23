#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "validation.c"
#include "add.c"
// char *normalization(char *num)
// {
//     // if (/* condition */)
//     // {
//     //     /* code */
//     // }
// }
int main(int argc, char const *argv[])
{

    char *a = (char *)argv[1];
    char *op = (char *)argv[2];
    char *b = (char *)argv[3];

    // char *a = "99";
    // char *op = "+";
    // char *b = "9";
    // printf("%s\n", a);

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
    // if (is)
    // {
    //     /* code */
    // }
    switch (op[0])
    {
    case '+':
        // double aa;
        // double bb;
        
        // if (isInt(a) || isDecimal(a))
        // {
        //     aa = atof(a);
        // }
        // else
        // {
        //     char prefixDigit1[50];
        //     int loc_of_e = -1;
        //     for (int i = 0; i < strlen(a); i++)
        //     {
        //         if (a[i] == 'e')
        //         {
        //             loc_of_e = i + 1;
        //             break;
        //         }
        //     }
        //     double multiplyBy = atof(a + loc_of_e);
        //     snprintf(prefixDigit1, loc_of_e , "%s", a);
          
        //     aa = atof(prefixDigit1) * pow(10, multiplyBy);
        // }

        // if (isInt(b) || isDecimal(b))
        // {
        //     bb = atof(b);
        // }
        // else
        // {
        //     char prefixDigit[1];
        //     int loc_of_e = -1;
        //     for (int i = 0; i < strlen(b); i++)
        //     {
        //         if (b[i] == 'e')
        //         {
        //             loc_of_e = i + 1;
        //             break;
        //         }
        //     }
        //     double multiplyBy = atof(b + loc_of_e);

        //     snprintf(prefixDigit, loc_of_e , "%s", b);

        //     bb = atof(prefixDigit) * pow(10, multiplyBy);
        // }
        // printf("%lf + %lf = %lf\n", aa,bb,aa + bb);
        printf("%s\n",addPositiveInteger(a,b));
        break;
    case '-':
        /* code */
        break;
    case '*':
        /* code */
        break;
    case '/':
        /* code */
        break;

    default:
        break;
    }

    return 0;
};
