#include "chars.h"

#include <stdarg.h>
#include <stdio.h>

extern void chars_catsprintf(struct Chars* chars, const char* format, ...)
{
	if (chars->error) {
		return;
	}

	{
		int count;
		va_list args;
		va_start(args, format);

		count = _vsnprintf_s(
			chars->chars + chars->len, 
			chars->capacity - chars->len - 1, 
			chars->capacity - chars->len, 
			format,
			args);
		
		if (count < 0) {
			chars->error = 1;
		} else {
			chars->len += count;
		}

		va_end(args);
	}
}