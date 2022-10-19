#include "main.h"

/**
 * erasor - Peforms erasing operations for _printf.
 * @words: A va_list of arguments provided to _printf.
 * @result: the buffer_t struct.
 */
void erasor(va_list words, buffer_print *result)
{
	va_end(words);
	write(1, result->begn, result->leng);
	free_buffer(result);
}

/**
 * check_printf - checks through format string for _printf.
 * @format: character string to print - may contain directives.
 * @result: A buffer_t struct containing a buffer.
 * @words:va_list of arguments.
 *
 * Return: number of characters stored to result
 */
int check_printf(const char *format, va_list words, buffer_print *result)
{
	int ndx, width, prec, ret = 0;
	char buffer = 0;
	unsigned char leng = 0, flags;
	unsigned int (*fun)(va_list, buffer_print *,
			unsigned char, int, int, unsigned char);

	for (ndx = 0; *(format + ndx); ndx++)
	{
		if (*(format + ndx) == '%')
		{
			flags = check_flags(format + ndx + 1, &buffer);
			width = check_width(words, format + ndx + buffer + 1, &buffer);
			prec = check_precision(words, format + ndx + buffer + 1,
					&buffer);
			leng = check_length(format + ndx + buffer + 1, &buffer);

			fun = check_specifiers(format + ndx + buffer + 1);
			if (fun != NULL)
			{
				ndx += buffer + 1;
				ret += fun(words, result, flags, width, prec, leng);
				continue;
			}
			else if (*(format + ndx + buffer + 1) == '\0')
			{
				ret = -1;
				break;
			}
		}
		ret += _memcpy(result, (format + ndx), 1);
		ndx += (leng != 0) ? 1 : 0;
	}
	erasor(words, result);
	return (ret);
}

/**
 * _printf - Outputs the required formatted string.
 * @format:gives character string to print,can contain directives.
 *
 * Return:number of characters printed.
 */
int _printf(const char *format, ...)
{
	buffer_print *result;
	va_list list;
	int buff;

	if (format == NULL)
		return (-1);
	result = init_buffer();
	if (result == NULL)
		return (-1);

	va_start(list, format);

	buff = check_printf(format, list, result);

	return (buff);
}
