/*	Copyright (C) 2004 Garrett A. Kajmowicz

	This file is part of the uClibc++ Library.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#define __UCLIBCXX_COMPILE_OSTREAM__ 1

#include <ostream>

#if 1 /* AWH */
#include <stdio.h>
#include <stdarg.h>
#endif /* AWH */

namespace std{
	

#ifdef __UCLIBCXX_EXPAND_OSTREAM_CHAR__
	
#ifdef __UCLIBCXX_EXPAND_CONSTRUCTORS_DESTRUCTORS__
	template _UCXXEXPORT ostream::~basic_ostream();
#endif //__UCLIBCXX_EXPAND_CONSTRUCTORS_DESTRUCTORS__

	template _UCXXEXPORT ostream & ostream::flush();

	template _UCXXEXPORT ostream & ostream::operator<<(bool n);
	template _UCXXEXPORT ostream & ostream::operator<<(short int n);
	template _UCXXEXPORT ostream & ostream::operator<<(unsigned short int n);
	template _UCXXEXPORT ostream & ostream::operator<<(int n);
	template _UCXXEXPORT ostream & ostream::operator<<(unsigned int n);
	template _UCXXEXPORT ostream & ostream::operator<<(long n);
	template _UCXXEXPORT ostream & ostream::operator<<(unsigned long n);
	template _UCXXEXPORT ostream & ostream::operator<<(float f);
	template _UCXXEXPORT ostream & ostream::operator<<(double f);
	template _UCXXEXPORT ostream & ostream::operator<<(long double f);
	template _UCXXEXPORT ostream & ostream::operator<<(void* p);
	template _UCXXEXPORT ostream & ostream::operator<<(basic_streambuf<char, char_traits<char> >* sb);

#ifdef __UCLIBCXX_EXPAND_CONSTRUCTORS_DESTRUCTORS__

	template _UCXXEXPORT ostream::sentry::sentry(ostream & os);
	template _UCXXEXPORT ostream::sentry::~sentry();

#endif //__UCLIBCXX_EXPAND_CONSTRUCTORS_DESTRUCTORS__

	template _UCXXEXPORT ostream & endl(ostream & os);
	template _UCXXEXPORT ostream & flush(ostream & os);
	template _UCXXEXPORT ostream & operator<<(ostream & out, char c);
	template _UCXXEXPORT ostream & operator<<(ostream & out, const char* c);
	template _UCXXEXPORT ostream & operator<<(ostream & out, unsigned char c);
	template _UCXXEXPORT ostream & operator<<(ostream & out, const unsigned char* c);

#endif


}

#if 1 /* AWH - Missing these funcs for _FORTIFY_CHECK */
int __vfprintf_chk(FILE *f, int flag, const char *fmt, va_list ap)
{
	return vfprintf(f, fmt, ap);
}
int __vsnprintf_chk(char *s, size_t n, int flag, size_t size, const char *fmt, va_list ap)
{
	return vsnprintf(s, n, fmt, ap);
}
int __vsprintf_chk(char *s, int flag, size_t size, const char *fmt, va_list ap)
{
	return vsprintf(s, fmt, ap);
}
int __snprintf_chk(
        char *dest,
        size_t supplied_size,
        int flags,
        size_t dest_len_from_compiler,
        const char *format, ...)
{
    va_list va;
    int retval;

    va_start(va, format);
    retval = __vsnprintf_chk(dest, supplied_size, flags,
                             dest_len_from_compiler, format, va);
    va_end(va);

    return retval;
}
int __fprintf_chk(FILE *stream, int flags, const char *format, ...)
{
    va_list arg;
    int rv;

    va_start(arg, format);
    rv = vfprintf(stream, format, arg);
    va_end(arg);

    return rv;
}
#endif /* AWH */

