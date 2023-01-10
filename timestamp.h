#ifndef WRAPPER_TIMESTAMP_H
#define WRAPPER_TIMESTAMP_H

#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#define TM_YEAR_OFFSET (1900U)
#define TM_MONTH_OFFSET (1U)

#define TIMESTAMP_LENGTH (19U)

extern void GetTimeStamp(char * timestamp_p);

#endif //WRAPPER_TIMESTAMP_H
