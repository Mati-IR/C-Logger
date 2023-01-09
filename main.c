#include <stdio.h>
#include "library.h"

/* DESCRIPTION
 *
 * This is wrapper that will be used for library testing/showcasing
 */

int main()
{
    LOGGER_Init("my_log.txt");
    printf("%d\n", LOGGER_Init("log.txt"));
    printf("%d\n", LOGGER_Log(PRIORITY_STD, "Hello World!"));
    return 0;
}
