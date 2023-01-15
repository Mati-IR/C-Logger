#ifndef LIB_LIBRARY_H
#define LIB_LIBRARY_H

/* If debug mode is defined, program will print out errno, but will no longer be signal atomic */
#define DEBUG_MODE

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include "timestamp.h"
#ifdef DEBUG_MODE
#include <stdio.h>
#include <errno.h>
#endif /* DEBUG_MODE */


#define MAX_MESSAGE_LENGTH          (1000U)
#define LOG_FILE_PERMISSIONS        (0644)
#define LOGGER_OK                   (0U)
#define LOGGER_ERROR                (1U)
#define LOGGER_NULL_ARG_MESSAGE_PTR (2U)
#define LOGGER_MESSAGE_TOO_LONG     (3U)
#define LOGGER_FILE_NOT_FOUND       (4U)
#define LOGGER_WRITE_ERROR          (5U)
#define LOGGER_MEM_ALLOC_ERROR      (6U)
#define LOGGER_TOO_LOW_PRIORITY     (7U)
#define LOGGER_REINITIALIZATION     (8U)
#define LOGGER_PTHREAD_ERROR        (9U)


#define MIN_PRIORITY_FLAG SIGUSR1
#define STD_PRIORITY_FLAG SIGUSR2
#define MAX_PRIORITY_FLAG SIGWINCH

typedef enum
{
    PRIORITY_MIN = 0,
    PRIORITY_STD = 1,
    PRIORITY_MAX = 2
} priority_e;

extern int Log(priority_e priority, const char * const message_p);
extern int Logger_Init(const char * const filename_p);

/* Set priority of logger, default priority value is PRIORITY_MAX  */
extern int Logger_SetPriority(priority_e priority);


#endif //LIB_LIBRARY_H
