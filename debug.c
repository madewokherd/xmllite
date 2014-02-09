/*
 * Debug/trace implementation
 *
 * Copyright 2002 Alexandre Julliard
 * Copyright 2014 Vincent Povirk
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "xmllite.h"
#include "xmllite_private.h"

typedef struct {
    char *str_pos;
    char strings[2000];
} tls_data;

__thread tls_data thread_data;

static char *get_temp_buffer( size_t n )
{
    char *res;

    if (!thread_data.str_pos) thread_data.str_pos = thread_data.strings;

    res = thread_data.str_pos;

    if (res + n >= &thread_data.strings[sizeof(thread_data.strings)]) res = thread_data.strings;
    thread_data.str_pos = res + n;
    return res;
}

static void release_temp_buffer( char *ptr, size_t size )
{
    thread_data.str_pos = ptr + size;
}

const char *xml_dbg_sprintf( const char *format, ... )
{
	va_list args;
    int max_size = sizeof(thread_data.strings) - (thread_data.str_pos - thread_data.strings);
    int size;
    char *ret;

    if (!thread_data.str_pos) thread_data.str_pos = thread_data.strings;

    ret = thread_data.str_pos;

	va_start (args, format);
	size = vsnprintf (thread_data.str_pos, max_size, format, args);
	va_end (args);

    if (size >= max_size)
        /* output truncated */
        return NULL;

    thread_data.str_pos += size + 1;
    return ret;    
}

const char *xml_dbgstr_wn( const XMLWCHAR *str, int n )
{
    char *dst, *res;
    size_t size;

    if (!str) return "(null)";
    if (n == -1)
    {
        const WCHAR *end = str;
        while (*end) end++;
        n = end - str;
    }
    if (n < 0) n = 0;
    size = 12 + min( 300, n * 5 );
    dst = res = get_temp_buffer( size );
    *dst++ = 'L';
    *dst++ = '"';
    while (n-- > 0 && dst <= res + size - 10)
    {
        WCHAR c = *str++;
        switch (c)
        {
        case '\n': *dst++ = '\\'; *dst++ = 'n'; break;
        case '\r': *dst++ = '\\'; *dst++ = 'r'; break;
        case '\t': *dst++ = '\\'; *dst++ = 't'; break;
        case '"':  *dst++ = '\\'; *dst++ = '"'; break;
        case '\\': *dst++ = '\\'; *dst++ = '\\'; break;
        default:
            if (c >= ' ' && c <= 126)
                *dst++ = c;
            else
            {
                *dst++ = '\\';
                sprintf(dst,"%04x",c);
                dst+=4;
            }
        }
    }
    *dst++ = '"';
    if (n > 0)
    {
        *dst++ = '.';
        *dst++ = '.';
        *dst++ = '.';
    }
    *dst++ = 0;
    release_temp_buffer( res, dst - res );
    return res;
}

void xml_debug_printf( const char *format, ... )
{
	va_list args;

	va_start (args, format);
	vfprintf (stderr, format, args);
	va_end (args);

    fflush (stderr);
    thread_data.str_pos = thread_data.strings;
}

int xml_debug_level = -1;

int xml_get_debug_level(void)
{
    const char *envvar = getenv("XMLLITE_DEBUG");

    if (envvar)
        xml_debug_level = envvar[0] - '0';
    else
        xml_debug_level = 2;

    return xml_debug_level;
}

