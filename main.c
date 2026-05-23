#include <stdio.h>
#include <string.h>
#include "file.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Error : Incorrect command format\n");

        printf("Usage : ./a.out --help\n");
        return FAILURE;
    }

    Operation op = check_operation(argv[1]);

    switch (op)
    {
        case view:
            /* ./a.out -v file.mp3 */
            if (argc != 3)
            {
                printf("Usage : ./a.out -v <file.mp3>\n");
                return FAILURE;
            }

            if (read_and_validate_mp3(argv[2]) == SUCCESS)
            {
                if (view_tags(argv[2]) != SUCCESS)
                    printf("Error : Failed to view tags\n");
            }
            break;

        case edit:
            /* ./a.out -e -t "value" file.mp3 */
            if (argc != 5)
            {
                printf("Usage : ./a.out -e -t \"value\" file.mp3\n");
                return FAILURE;
            }

            if (read_and_validate_mp3(argv[4]) == SUCCESS)
            {
                if (edit_tags(argv[2], argv[3], argv[4]) != SUCCESS)
                    printf("Error : Failed to edit tags\n");
            }
            break;

        case help:
            print_help();
            break;

        default:
            printf("Invalid option\n");
            printf("Use ./a.out --help\n");
            break;
    }

    return SUCCESS;
}

Operation check_operation(char *argv)
{
    if (strcmp(argv, "-e") == 0)
        return edit;
    else if (strcmp(argv, "-v") == 0)
        return view;
    else if (strcmp(argv, "-h") == 0 || strcmp(argv, "--help") == 0)
        return help;
    else
        return unsupported;
}


Status read_and_validate_mp3(char *mp3)
{
    if (!mp3)
    {
        printf("Error : MP3 file not provided\n");
        return FAILURE;
    }

    FILE *fp = fopen(mp3, "rb");
    if (!fp)
    {
        printf("Error : Unable to open file %s\n", mp3);
        return FAILURE;
    }

    char header[3];
    if (fread(header, 1, 3, fp) != 3)
    {
        printf("Error : File too small\n");
        fclose(fp);
        return FAILURE;
    }

    if (strncmp(header, "ID3", 3) != 0)
    {
        printf("Error : Not a valid ID3 MP3 file\n");
        fclose(fp);
        return FAILURE;
    }

    fclose(fp);
    return SUCCESS;
}


void print_help(void)
{
    printf("\nusage: mp3tag -[tTaAycg] \"value\" file.mp3\n");
    printf("       mp3tag -v file.mp3\n\n");

    printf("OPTIONS:\n");
    printf("  -t    Modifies a Title tag\n");

    printf("  -a    Modifies an Artist tag\n");
    printf("  -A    Modifies an Album tag\n");
    printf("  -y    Modifies a Year tag\n");
    printf("  -c    Modifies a Comment tag\n");
    printf("  -g    Modifies a Genre tag\n");
    printf("  -h    Displays this help information\n");
    printf("  -v    Prints version information\n\n");
}