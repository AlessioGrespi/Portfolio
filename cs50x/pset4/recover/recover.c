#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[])
{

    // Check usage
    if (argc != 2)
    {
        printf("Usage: ./recover image \n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");

    if (!file)
    {
        printf("No such file: %s \n", argv[1]);
        return 1;
    }

    FILE *img;
    unsigned char *buffer = malloc(512);
    char filename[7];
    int fileNumber = 0;


    while(fread(buffer, 512, 1, file))
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if(fileNumber > 0)
            {
                fclose(img);
            }
            
            sprintf(filename, "%03i.jpg", fileNumber);

            img = fopen(filename, "w");
            //fwrite(buffer, 512, 1, img);
            
            if (img == NULL)
            {
                fclose(file);
                free(buffer);
                fprintf(stderr, "Could not create output JPG %s", filename);
                return 3;
            }
            
            fileNumber++;
        }
        
        if(fileNumber > 0)
        {
            fwrite(buffer, 512, 1, img);
        }
    }

    fclose(file);
    fclose(img);
    //free(buffer);
    return 0;

}
