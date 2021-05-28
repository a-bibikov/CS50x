#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

#define BUFFER_SIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check input file
    if (argc < 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //init variables
    int counter_JPEG = 0;
    bool isJPEG;

    FILE *input_file = fopen(argv[1], "r");
    BYTE buffer[BUFFER_SIZE];
    FILE *output_file = NULL;

    if (argv[1])
    {
        //if input file does not exists
        if (input_file == NULL)
        {
            printf("Error: can't open file. %s\n", argv[1]);
            return 2;
        }

        while (fread(&buffer, BUFFER_SIZE, 1, input_file))
        {
            //check JPEG files
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                if (isJPEG)
                {
                    fclose(output_file);
                }
                else
                {
                    isJPEG = true;
                }

                //set new file name
                char filename[8];
                sprintf(filename, "%03i.jpg", counter_JPEG);
                output_file = fopen(filename, "w");

                counter_JPEG++;
            }

            //if is JPEG, write data into file
            if (isJPEG)
            {
                fwrite(&buffer, BUFFER_SIZE, 1, output_file);
            }
        }
    }

    //close all files
    if (output_file != NULL)
    {
        fclose(output_file);
    }
    if (input_file != NULL)
    {
        fclose(input_file);
    }
    return 0;
}