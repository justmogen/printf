#include "main.h"
/**
 * check_mem - check memory for contents and writes it if it exist
 * @char_arr: The array of characters
 * @ndx_len:length of index
 */
void check_mem(char char_arr[], int *ndx_len)
{
	if (*ndx_len > 0)
		write(1, &char_arr[0], *ndx_len);

	*ndx_len = 0;
}
/**
 * _printf -  a function that produces output according to a format
 * @format: a character string
 * Returns: the number of characters printed
 *		(excluding the null byte used to end output to strings)
 */
int _printf(const char *format, ...)
{
	int ndx, mem_ndx, write_mem = 0, flags;
	char mem[mem_size];
	va_list words;
	int width, precision, space, write;

	if (format == NULL)
		return (-1);

	va_start(words, format);

	for (ndx = 0; format && *(format + ndx) != '\0'; ndx++)
		mem_ndx = 0;
		if (format[ndx] != '%')
		{
			mem[mem_ndx++] = format[ndx];
			if (mem_ndx == mem_size)
				check_mem(mem, &mem_ndx);
			write_mem++;
		}
		else
		{
			check_mem(mem, &mem_ndx);
			flags = check_flags(format, &ndx);
			wid = check_width(format, &ndx, words);
			prec = check_precision(format, &ndx, words);
			space = check_space(format, &ndx);
			++ndx;

			write = 0;
			write = use_print(format, &ndx, words, mem, flags, width,
					precision, space);
			if (write == -1)
				return (-1);
			write_mem += write;
		}
	check_mem(mem,&mem_ndx);
	va_end(words);

	return (write_mem);
}
