#include "library.h"


char * LOGGER_LogFileName_p;


int LOGGER_Init(const char * const filename_p)
{
    int fd = open(filename_p, O_WRONLY | O_CREAT | O_TRUNC, LOG_FILE_PERMISSIONS);
    if (fd == -1)
    {
#ifdef DEBUG_MODE
        /* print error information */
        perror("LOGGER_Init file open fail\n");
#endif /* DEBUG_MODE */
        return LOGGER_FILE_NOT_FOUND;
    }
    
    LOGGER_LogFileName_p = malloc(strlen(filename_p) + 1); /* one additional byte for null terminator */
    strcpy(LOGGER_LogFileName_p, filename_p);

    close(fd);
    return LOGGER_OK;
}

/*
 *      Function performing actual writing to file.
 *      This function is not exposed to the user.
 *      This function will not check validity of arguments and files basing on cascade trust.
 * */
static int LOGGER_WriteToLogFile(priority_e priority, const char * const message_p)
{
    unsigned int retVal_u16           = LOGGER_ERROR;
    int          fileDescriptor_i     = -1;
    /* write to logFile_p using posix write() function */

    fileDescriptor_i = open(LOGGER_LogFileName_p, O_WRONLY | O_APPEND);
    if (-1 == fileDescriptor_i)
    {
#ifdef DEBUG_MODE
        /* print error information */
        perror("LOGGER_WriteToLogFile file open fail\n");
#endif /* DEBUG_MODE */
        retVal_u16 = LOGGER_FILE_NOT_FOUND;
    }else
    {
        if (-1 == write(fileDescriptor_i, message_p, strlen(message_p)))
        {
#ifdef DEBUG_MODE
            /* print error information */
            perror("LOGGER_WriteToLogFile write to file fail \n");
#endif /* DEBUG_MODE */
            retVal_u16 = LOGGER_WRITE_ERROR;
        }
        else
        {
            retVal_u16 = LOGGER_OK;
        }
        close(fileDescriptor_i);
    }

    return retVal_u16;
}

int LOGGER_Log(priority_e priority, const char * const message_p)
{
    unsigned int retVal_u16 = LOGGER_ERROR;

    if(NULL == message_p)
    {
        retVal_u16 = LOGGER_NULL_ARG_MESSAGE_PTR;
    }
    else if(MAX_MESSAGE_LENGTH < strlen(message_p))
    {
        retVal_u16 = LOGGER_MESSAGE_TOO_LONG;
    }
    else /* all parameters are valid */
    {
        retVal_u16 = LOGGER_WriteToLogFile(priority, message_p);
    }

    return retVal_u16;
}
