#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Confirms there are two arguments included to run the program
    if (argc == 2)
    {
        // Iterates on the key in command line and ensures it is a positive integer
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            // Returns error message if key includes anything other than digits
            if (isdigit(argv[1][i]) == false)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }
    int k = atoi(argv[1]);

    string text = get_string("plaintext: ");
    //printf("\n");

    for (int i = 0; i < strlen(text); i++)
    {
        if((text[i] <= 90 && text[i] >= 65) | (text[i] <= 122 && text[i] >= 97))
        {
            text[i] = text[i] + k;

            if(text[i] >= 91 && text[i] < 97 + k)
            {
                //printf("*");
                int a = text[i] - 91;
                text[i] = a + 65;
            }

            if(text[i] >= 123)
            {
                //printf("-");
                int a = text[i] - 91;
                text[i] = a + 65;
            }
        }
    }

    printf("cipher text: %s\n", text);
}