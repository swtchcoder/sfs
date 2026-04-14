/*
 * C'est un simple logger en C qui utilise les fonctions standards et des
 * macros.
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#define _STR(x) #x
#define STR(x) _STR(x)

#define INFOF(fmt, ...)                                                        \
	printf("INFO  " __FILE__ ":" STR(__LINE__) " " fmt, __VA_ARGS__)

#define INFO(s) printf("INFO  " __FILE__ ":" STR(__LINE__) " " s)

#ifdef _DEBUG
#define DEBUGF(fmt, ...)                                                       \
	printf("\x1b[32mDEBUG " __FILE__ ":" STR(__LINE__) " " fmt "\x1b[0m",  \
	       __VA_ARGS__)

#define DEBUG(s)                                                               \
	printf("\x1b[32mDEBUG " __FILE__ ":" STR(__LINE__) " " s "\x1b[0m")
#else /* _DEBUG */
#define DEBUGF(fmt, ...) ((void)0)
#define DEBUG(s) ((void)0)
#endif /* _DEBUG */

#define WARNF(fmt, ...)                                                        \
	fprintf(stderr,                                                        \
		"\x1b[33mWARN  " __FILE__ ":" STR(__LINE__) " " fmt "\x1b[0m", \
		__VA_ARGS__)

#define WARN(s)                                                                \
	fprintf(stderr,                                                        \
		"\x1b[33mWARN  " __FILE__ ":" STR(__LINE__) " " s "\x1b[0m")

#define ERRORF(fmt, ...)                                                       \
	fprintf(stderr,                                                        \
		"\x1b[31mERROR " __FILE__ ":" STR(__LINE__) " " fmt "\x1b[0m", \
		__VA_ARGS__)

#define ERROR(s)                                                               \
	fprintf(stderr,                                                        \
		"\x1b[31mERROR " __FILE__ ":" STR(__LINE__) " " s "\x1b[0m")

#endif /* LOGGER_H */
