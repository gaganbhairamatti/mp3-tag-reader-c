#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"

/* ===================== MACRO ===================== */
#define READ_AND_PRINT_TAG(label)                         \
    {                                                     \
    unsigned char size_buf[4];                            \
    fread(size_buf, 1, 4, fp);                            \
    int size = convert_size(size_buf);                    \
    fseek(fp, 2, SEEK_CUR);                               \
                                                          \
    char *str = malloc(size + 1);                         \
    if (!str)                                             \
     return FAILURE;                                      \
                                                          \
    fread(str, 1, size, fp);                              \
    str[size] = '\0';                                     \
                                                          \
    printf("%-8s : %s\n", label, str + 1);                \
    free(str);                                            \
    }

/* ===================== SIZE CONVERSION ===================== */
Status convert_size(unsigned char *buf)
{
    return (buf[0] << 24) |
           (buf[1] << 16) |
           (buf[2] << 8)  |
            buf[3];
}
//Left shift is used to move each byte into its correct position inside a 4-byte integer before combining them.

/* ===================== VIEW TAGS ===================== */
Status view_tags(char *mp3)
{
    FILE *fp = fopen(mp3, "rb");
    if (!fp)
        return FAILURE;

    /* -------- Read ID3 Header -------- */
    unsigned char header[10];
    fread(header, 1, 10, fp);

    printf("----------------------------\n");
    printf("    Version ID : ID3v2.%d.%d\n", header[3], header[4]);
    printf("----------------------------\n");

    printf("\n========================================\n");
    printf("        MP3 TAG READER & EDITOR\n");
    printf("========================================\n\n");

    /* -------- Read only required 6 tags -------- */
    for (int i = 0; i < 6; i++)
    {
        char buf[5];

        if (fread(buf, 1, 4, fp) != 4)
            break;

        buf[4] = '\0'; // makes it proper string 

        if(strcmp(buf, "TIT2") == 0)
            {READ_AND_PRINT_TAG("Title");}
        else if (strcmp(buf, "TPE1") == 0)
            {READ_AND_PRINT_TAG("Artist");}
        else if (strcmp(buf, "TALB") == 0)
            {READ_AND_PRINT_TAG("Album");}
        else if (strcmp(buf, "TYER") == 0)
            {READ_AND_PRINT_TAG("Year");}
        else if (strcmp(buf, "TCON") == 0)
            {READ_AND_PRINT_TAG("Genre");}
        else if (strcmp(buf, "COMM") == 0 || strcmp(buf, "TCOM") == 0)
            {READ_AND_PRINT_TAG("Comment");}
        else
        {
            /* -------- Skip unsupported frame safely -------- */
            unsigned char size_buf[4];
            fread(size_buf, 1, 4, fp);
            int size = convert_size(size_buf);
            fseek(fp, 2 + size, SEEK_CUR);
        }
    }

    printf("\n========================================\n");

    fclose(fp);
    return SUCCESS;
}