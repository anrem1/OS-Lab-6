#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int strLength(const char *str)

{
    int length = 0;
    while (str[length] != '\0') 
    {
        length++;
    }
    return length;
}


int SaveToFile(const char *filename, const char *word)

{
    int fd=open(filename, O_WRONLY | O_CREATE);
    int length=strLength(word);

    if (write(fd, (const void *)word, length) < 0)
    {
        printf(1, "error to write '%s'.\n", filename);
        close(fd);
        return 1;
    }

    close(fd);
    printf(1, "success: written to file '%s'.\n", filename);
    return 0;
}


int main(int argc, char *argv[])

{
    if (argc != 3)
    {
        printf(1, "usage: save <filename> <string>\n");
        exit();
    }
    if (SaveToFile(argv[1], argv[2]) == 0) {
        printf(1, "successfully written '%s' to the file '%s'.\n", argv[2], argv[1]);
    } else {
        printf(1, "failed to write to the file '%s'.\n", argv[1]);
    }

    exit();
}
