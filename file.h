#ifndef FILE_H
#define FILE_H

typedef enum
{
    view,
    edit,
    help,
    unsupported
}Operation;

typedef enum Status
{
    SUCCESS,
    FAILURE
}Status;



Operation check_operation(char *argvfiles);
Status read_and_validate_mp3(char *mp3file);
Status convert_size(unsigned char *buf);

Status view_tags(char *mp3file);
Status edit_tags(char *mode, char *data, char *mp3file);
void print_help(void);


#endif