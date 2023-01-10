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

void GetLogMessage(priority_e priority, const char * const message_p, char * destination_p)
{
    char *log_message_p = malloc(MAX_MESSAGE_LENGTH + 1); /* one additional byte for null terminator */
    char *timestamp_p = malloc(sizeof(char) * (TIMESTAMP_LENGTH + 1)); /* one additional byte for null terminator */
    GetTimeStamp(timestamp_p);
    if ((log_message_p == NULL) || (timestamp_p == NULL) || (destination_p == NULL))
    {
#ifdef DEBUG_MODE
        /* print error information */
        perror("GetLogMessage malloc fail\n");
#endif /* DEBUG_MODE */
    }else
    {
        printf("Timestamp: %s\nMessage: %s", timestamp_p, message_p);
        switch (priority)
        {
            case PRIORITY_MIN:
                strcpy(log_message_p, timestamp_p);
                strcat(log_message_p, " MIN: ");
                strcat(log_message_p, message_p);
                break;
            case PRIORITY_STD:
                strcpy(log_message_p, timestamp_p);
                strcat(log_message_p, " STD: ");
                strcat(log_message_p, message_p);
                break;
            case PRIORITY_MAX:
                strcpy(log_message_p, timestamp_p);
                strcat(log_message_p, " MAX: ");
                strcat(log_message_p, message_p);
                break;
            default:
                strcpy(log_message_p, timestamp_p);
                strcat(log_message_p, " ERR: ");
                strcat(log_message_p, message_p);
                break;
        }
    }
    printf("Log message: %s\n", log_message_p);
    strcpy(destination_p, log_message_p);
    free(timestamp_p);
    free(message_p);
    return;
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
    char        *log_message_p        = malloc(MAX_MESSAGE_LENGTH + 1); /* one additional byte for null terminator */


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
        GetLogMessage(priority, message_p, log_message_p);
        if (-1 == write(fileDescriptor_i, log_message_p, strlen(log_message_p)))
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
