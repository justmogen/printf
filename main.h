#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
/* Macros */
#define mem_size 1024

/**
 * struct formt - using a structure operator
 * @fun:function to be used
 */
typedef struct formt
{
	char formt;
	int (*fun)(va_list, char[], int, int, int, int);
} fmt_d;

int _printf(const char *format, ...);
int use_print(const char *formt, int *ndx,va_list words,char mem[],
		int flags, int width, int precision, int space);

/*functions Handlers */
int check_flags(const char *format, int *ndx);
int check_width(const char *format, int *ndx, va_list words);
int check_precision(const char *format, int *ndx, va_list words);
int check_space(const char *format, int *ndx);

#endif
