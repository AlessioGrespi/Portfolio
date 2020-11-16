#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
   string text = get_string("Text: \n");

   float letters = 0, words, sentences = 0;
   int length = strlen(text);

   for (int i = 0 ; i < strlen(text) ; i++)
   {
      if((text[i] <= 90 && text[i] >= 65) | (text[i] <= 122 && text[i] >= 97))
      {
         letters = letters + 1;
      }
      else if(text[i] == 32)
      {
         words = words + 1;
      }
      else if(text[i] == 33 | text[i] == 46 | text[i] == 63)
      {
         sentences = sentences + 1;
      }
   }

   words = words + 1;

   //printf("Letters: %.0f\n", letters);
   //printf("Words: %.0f\n", words);
   //printf("Sentences: %.0f\n", sentences);

   float L = (letters / words) * 100; //letters per 100 words
   float S = (sentences / words) * 100; //sentences per 100 words
   float test = 0.0588 * L - 0.296 * S - 15.8;

   //printf("%f \n",L);
   //printf("%f \n", S);

   int grade = round(test);
   //printf("%d\n", grade);

   if(grade >> 0)
   {
      if(grade >= 1)
      {
         if(1 <= grade && grade <= 16)
         {
            printf("Grade %d\n", grade);
         }
         else
         {
            printf("Grade 16+\n");
         }
      }
      else
      {
      printf("Before Grade 1\n");
     }
   }
   else
   {
      printf("Before Grade 1\n");
   }
}