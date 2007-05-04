/* @header@ */

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


#include "emu/emu_string.h"


struct emu_string *emu_string_new()
{
    struct emu_string *s = (struct emu_string *)malloc(sizeof(struct emu_string));
    if( s == NULL )
    {
    	return NULL;
    }
    memset(s, 0, sizeof(struct emu_string));
    return s;
}

void emu_string_free(struct emu_string *s)
{
    free(s->data);
    free(s);
}

char *emu_string_char(struct emu_string *s)
{
    return (char *)s->data;
}


#include <stdio.h>
void emu_string_append_char(struct emu_string *s, const char *data)
{
//	printf("before %i %i|%s|\n", s->size, strlen(data), (char *)s->data);
	s->data = realloc(s->data, s->size + strlen(data) + 1);
	memcpy((unsigned char *)s->data + s->size, data, strlen(data));
	*(unsigned char *)(s->data + s->size + strlen(data)) = 0;
	s->size += strlen(data);
//	printf("after %i |%s|\n", s->size, (char *)s->data);
}

void emu_string_append_format(struct emu_string *s, const char *format, ...)
{
	va_list         ap;
	char            *message;

	va_start(ap, format);
	vasprintf(&message, format, ap);
	va_end(ap);

	emu_string_append_char(s, message);
	free(message);
}
