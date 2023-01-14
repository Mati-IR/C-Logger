#include <stdio.h>
#include "library.h"

/* DESCRIPTION
 *
 * This is wrapper that will be used for library testing/showcasing
 */

int main()
{
    printf("%d\n", Logger_Init("my_log.txt"));
    printf("%d\n", Log(PRIORITY_STD, "Hello World!\n"));
    printf("%d\n", Log(PRIORITY_MIN, "Sample text"));
    printf("%d\n", Log(PRIORITY_MIN, "Tainted champion\n"));
    printf("%d\n", Log(PRIORITY_MIN, "It's wednesday my dudes"));

    Logger_SetPriority(PRIORITY_MIN);
    printf("%d\n", Log(PRIORITY_STD, "Hello World!\n"));
    printf("%d\n", Log(PRIORITY_MIN, "Sample text"));
    printf("%d\n", Log(PRIORITY_MAX, "Tainted champion\n"));
    return 0;
}
