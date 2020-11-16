#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float input;
    int total;
    do
    {
        input = get_float("Change owed: ");
        input = input * 100;
        total = round(input);
    }
    while (input <= 0);
    
    int coins25 = total / 25;
    
    if (coins25 >= 1)
    {
        total = total - (25 * coins25);
    }
    
    int coins10 = total / 10;
    
    if (coins10 >= 1)
    {
        total = total - (10 * coins10);
    }
    
    int coins5 = total / 5;
    
    if (coins5 >= 1)
    {
        total = total - (5 * coins5);
    }
    
    int coins1 = total / 1;
    
    if (coins1 >= 1)
    {
        total = total - coins1;
    }
    
    int coins = coins25 + coins10 + coins5 + coins1;
    
    printf("%i", coins);
}