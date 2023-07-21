#include "main.h"

void print_output_buffer(char output_buffer[], int *output_buff_ind);

/**
 * _printf - Custom printf function
 * @format: The format string.
 * Return: Number of characters printed.
 */
int _printf(const char *format, ...)
{
	int i, printed_chars = 0, chars_printed = 0;
	int flags, width, precision, size, output_buff_ind = 0;
	va_list args_list;
	char output_buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(args_list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			output_buffer[output_buff_ind++] = format[i];
			if (output_buff_ind == BUFF_SIZE)
				print_output_buffer(output_buffer, &output_buff_ind);
			printed_chars++;
		}
		else
		{
			print_output_buffer(output_buffer, &output_buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, args_list);
			precision = get_precision(format, &i, args_list);
			size = get_size(format, &i);
			++i;
			chars_printed = handle_print(format, &i, args_list, output_buffer,
					flags, width, precision, size);
			if (chars_printed == -1)
				return (-1);
			printed_chars += chars_printed;
		}
	}

	print_output_buffer(output_buffer, &output_buff_ind);

	va_end(args_list);

	return (printed_chars);
}

/**
 * print_output_buffer - Prints the contents of the output_buffer if it exists
 * @output_buffer: Array of chars to be printed
 * @output_buff_ind: Index at which to add next char, represents the length.
 */
void print_output_buffer(char output_buffer[], int *output_buff_ind)
{
	if (*output_buff_ind > 0)
		write(1, &output_buffer[0], *output_buff_ind);

	*output_buff_ind = 0;
}

