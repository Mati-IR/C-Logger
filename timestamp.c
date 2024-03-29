#include "timestamp.h"

static char *my_itoa(int num, char *str)
{
    if(str == NULL)
    {
        return NULL;
    }
    sprintf(str, "%d", num);
    return str;
}

static void Conv1DigitNumberTo2DigitNumber(char * num_p)
{
    *(num_p + 1) = *(num_p);
    *(num_p) = '0';
*   (num_p + 2) = '\0';
}

void GetTimeStamp(char * timestamp_p)
{
    time_t rawtime;
    struct tm * timeinfo;

    /* Enough memory will be allocated to each string, so that it's possible
     * to concatenate them into timestamp of format YYYY:MM:DD:HH:MM:SS
     */
    char * year     = malloc(sizeof(char) * 5);
    char * month    = malloc(sizeof(char) * 3);
    char * day      = malloc(sizeof(char) * 3);
    char * hour     = malloc(sizeof(char) * 3);
    char * min      = malloc(sizeof(char) * 3);
    char * sec      = malloc(sizeof(char) * 3);

    timeinfo        = malloc(sizeof(struct tm));

    *(year + 4) = '\0';


    /* get current time */
    time(&rawtime);
    timeinfo = localtime ( &rawtime );

    /* write time to strings */
    my_itoa((timeinfo->tm_year + TM_YEAR_OFFSET), year);
    my_itoa((timeinfo->tm_mon + TM_MONTH_OFFSET), month);
    my_itoa((timeinfo->tm_mday), day);
    my_itoa((timeinfo->tm_hour), hour);
    my_itoa((timeinfo->tm_min), min);
    my_itoa((timeinfo->tm_sec), sec);

    /* standardize timestamp elements' lengths */
    if(timeinfo->tm_mon < 10)  {Conv1DigitNumberTo2DigitNumber(month);}
    if(timeinfo->tm_mday < 10) {Conv1DigitNumberTo2DigitNumber(day);}
    if(timeinfo->tm_hour < 10) {Conv1DigitNumberTo2DigitNumber(hour);}
    if(timeinfo->tm_min < 10)  {Conv1DigitNumberTo2DigitNumber(min);}
    if(timeinfo->tm_sec < 10)  {Conv1DigitNumberTo2DigitNumber(sec);}

    /* concatenate timestamp elements into one string */
    strcpy(timestamp_p, day);
    strcat(timestamp_p, ":");
    strcat(timestamp_p, month);
    strcat(timestamp_p, ":");
    strcat(timestamp_p, year);
    strcat(timestamp_p, " ");
    strcat(timestamp_p, hour);
    strcat(timestamp_p, ":");
    strcat(timestamp_p, min);
    strcat(timestamp_p, ":");
    strcat(timestamp_p, sec);

    free(year);
    free(month);
    free(day);
    free(hour);
    free(min);
    free(sec);
}
