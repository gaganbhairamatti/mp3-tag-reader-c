#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"

/* Map option to ID3 frame ID */
static const char *get_frame_id(char *mode)
{
    if (strcmp(mode, "-t") == 0)
        return "TIT2";   // Title
    else if (strcmp(mode, "-a") == 0)
        return "TPE1";   // Artist
    else if (strcmp(mode, "-A") == 0)
        return "TALB";   // Album
    else if (strcmp(mode, "-y") == 0)
        return "TYER";   // Year
    else if (strcmp(mode, "-c") == 0)
        return "COMM";   // Comment
    else if (strcmp(mode, "-g") == 0)
        return "TCON";   // Genre
    else
        return NULL;
}

/* ===================== EDIT TAG ===================== */
Status edit_tags(char *mode, char *data, char *mp3file)
{
    const char *frame_id = get_frame_id(mode);
    if (!frame_id)
    {
        printf("Error : Unsupported edit option\n");
        return FAILURE;
    }

    FILE *fp = fopen(mp3file, "rb+");
    if (!fp)
    {
        printf("Error : Unable to open MP3 file\n");
        return FAILURE;
    }

    /* Skip ID3 header */
    fseek(fp, 10, SEEK_SET);

    while (1)
    {
        char id[5];
        unsigned char size_buf[4];

        /* Read frame ID */
        if (fread(id, 1, 4, fp) != 4)
            break;

        id[4] = '\0';

        /* Read frame size */
        fread(size_buf, 1, 4, fp);
        int size = convert_size(size_buf);

        /* Skip flags */
        fseek(fp, 2, SEEK_CUR);

        if (strcmp(id, frame_id) == 0)
        {
            /* Read old frame data */
            char *old = malloc(size);
            fread(old, 1, size, fp);

            int new_len = strlen(data);

            /* if new_len is greater than size*/
            if (new_len + 1 > size)
            {
                printf("Error : New value is too large for this frame\n");
                free(old);
                fclose(fp);
                return FAILURE;
            }

            /* Move back to start of frame data to write*/
            fseek(fp, -size, SEEK_CUR);

            /* Preserve first one byte */
            unsigned char encoding = old[0];
            fwrite(&encoding, 1, 1, fp);

            /* Write new text */
            fwrite(data, 1, new_len, fp);

            /* Pad remaining bytes with NULL */
            for (int i = new_len + 1; i < size; i++)
                fputc('\0', fp);

            free(old);
            fclose(fp);

            printf("Tag updated successfully\n");
            return SUCCESS;
        }
        else
        {
            /* Skip this frame’s data */
            fseek(fp, size, SEEK_CUR);
        }
    }

    fclose(fp);
    printf("Error : Tag not found in MP3 file\n");
    return FAILURE;
}