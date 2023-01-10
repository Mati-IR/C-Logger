#include <stdio.h>
#include "library.h"

/* DESCRIPTION
 *
 * This is wrapper that will be used for library testing/showcasing
 */

int main()
{
    printf("%d\n", LOGGER_Init("my_log.txt"));
    printf("%d\n", LOGGER_Log(PRIORITY_STD, "Hello World!\n"));
    printf("%d\n", LOGGER_Log(PRIORITY_MIN, "Sample text"));
    printf("%d\n", LOGGER_Log(PRIORITY_MIN, "Tainted champion\n"));
    printf("%d\n", LOGGER_Log(PRIORITY_MIN, "It's wednesday my dudes"));
    return 0;
}
