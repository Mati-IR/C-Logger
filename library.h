#ifndef LIB_LIBRARY_H
#define LIB_LIBRARY_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_MESSAGE_LENGTH          (1000U)
#define LOGGER_OK                   (0U)
#define LOGGER_ERROR                (1U)
#define LOGGER_NULL_ARG_MESSAGE_PTR (2U)
#define LOGGER_MESSAGE_TOO_LONG     (3U)
#define LOGGER_FILE_NOT_FOUND       (4U)
#define LOGGER_WRITE_ERROR          (5U)
#define LOGGER_MEM_ALLOC_ERROR      (6U)

typedef enum
{
    PRIORITY_MIN = 0,
    PRIORITY_STD = 1,
    PRIORITY_MAX = 2
} priority_e;

extern int LOGGER_Log(priority_e priority, const char * const message_p);
extern int LOGGER_Init(const char * const filename_p);


#endif //LIB_LIBRARY_H
