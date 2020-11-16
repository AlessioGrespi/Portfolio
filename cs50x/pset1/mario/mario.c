#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    } 
    while (h < 1 || h > 8);

    for (int i = 0; i < h; i++)
    {
        int c = h - i;
        
        for (int b = 1; b < c; b++)
        {
            printf(" ");
        }
            
        for (int a = 0; a < i + 1; a++)
        {
            printf("#");
        }
        
        printf("  ");
        
        
        
        for (int a = 0; a < i + 1; a++)
        {
            printf("#");
        }
        
        printf("\n");
    }
}
