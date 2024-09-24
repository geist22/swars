#ifndef WINDOWS_H
#define WINDOWS_H

#ifdef WIN32
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>

bool sys_get_user_path (char *buffer, size_t size);
bool sys_get_data_path (char *buffer, size_t size);

#endif /* WIN32 */

#endif /* WINDOWS_H */
