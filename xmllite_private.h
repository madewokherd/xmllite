/*
 * xmllite private definitions
 *
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

#ifndef _XMLLITE_PRIVATE_H
#define _XMLLITE_PRIVATE_H

#if defined(__MSC_VER) || defined(__MINGW32__) || defined(__CYGWIN__)
# define DECLSPEC_HIDDEN
#elif defined(__GNUC__) && ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 3)))
# define DECLSPEC_HIDDEN __attribute__((visibility ("hidden")))
#else
# define DECLSPEC_HIDDEN
#endif

#define CONTAINING_RECORD(address, type, field) \
  ((type *)((char*)(address) - offsetof(type, field)))

#define CP_UTF8       65001

#define heap_alloc malloc
#define heap_realloc realloc
#define heap_free free

typedef XMLWCHAR WCHAR;
typedef XMLWCHAR *LPWSTR;

#define strcmpiW xml_wcsicmp
#define strlenW xml_wcslen
#define strncmpiW xml_wcsnicmp

typedef XMLHRESULT HRESULT;

#define S_OK XML_S_OK
#define E_NOTIMPL XML_E_NOTIMPL
#define E_OUTOFMEMORY XML_E_OUTOFMEMORY
#define E_PENDING XML_E_PENDING

#define FAILED(hr) XML_FAILED(hr)
#define SUCCEEDED(hr) XML_SUCCEEDED(hr)

typedef uint32_t UINT;
typedef uint32_t DWORD;
typedef uint32_t ULONG;
typedef int32_t LONG;
typedef int32_t BOOL;

#define TRUE ((BOOL)1)
#define FALSE ((BOOL)0)

typedef IXmlUnknown IUnknown;
typedef IXmlMalloc IMalloc;
typedef IXmlSequentialStream ISequentialStream;
typedef IXmlStream IStream;

#define IID_IUnknown IID_IXmlUnknown
#define IUnknown_QueryInterface IXmlUnknown_QueryInterface
#define IUnknown_AddRef IXmlUnknown_AddRef
#define IUnknown_Release IXmlUnknown_Release

#define IID_IMalloc IID_IXmlMalloc
#define IMalloc_QueryInterface IXmlMalloc_QueryInterface
#define IMalloc_AddRef IXmlMalloc_AddRef
#define IMalloc_Release IXmlMalloc_Release
#define IMalloc_Alloc IXmlMalloc_Alloc
#define IMalloc_Realloc IXmlMalloc_Realloc
#define IMalloc_Free IXmlMalloc_Free
#define IMalloc_GetSize IXmlMalloc_GetSize
#define IMalloc_DidAlloc IXmlMalloc_DidAlloc
#define IMalloc_HeapMinimize IXmlMalloc_HeapMinimize

#define IID_ISequentialStream IID_IXmlSequentialStream
#define ISequentialStream_QueryInterface IXmlSequentialStream_QueryInterface
#define ISequentialStream_AddRef IXmlSequentialStream_AddRef
#define ISequentialStream_Release IXmlSequentialStream_Release
#define ISequentialStream_Read IXmlSequentialStream_Read
#define ISequentialStream_Write IXmlSequentialStream_Write

#define IID_IStream IID_IXmlStream
#define IStream_QueryInterface IXmlStream_QueryInterface
#define IStream_AddRef IXmlStream_AddRef
#define IStream_Release IXmlStream_Release
#define IStream_Read IXmlStream_Read
#define IStream_Write IXmlStream_Write
#define IStream_Seek IXmlStream_Seek
#define IStream_CopyTo IXmlStream_CopyTo
#define IStream_Commit IXmlStream_Commit
#define IStream_Revert IXmlStream_Revert
#define IStream_LockRegion IXmlStream_LockRegion
#define IStream_UnlockRegion IXmlStream_UnlockRegion
#define IStream_Stat IXmlStream_Stat
#define IStream_Clone IXmlStream_Clone

#ifndef max
#define max(a,b)   (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)   (((a) < (b)) ? (a) : (b))
#endif

extern const char *xml_dbg_sprintf( const char *format, ... );

#define wine_dbg_sprintf xml_dbg_sprintf

extern const char *xml_dbgstr_wn( const XMLWCHAR *str, int n );

#define debugstr_wn xml_dbgstr_wn

extern int xml_debug_level;

extern int xml_get_debug_level(void);

extern void xml_debug_printf( const char *format, ... );

#define DEBUG_PRINT(lvl) (((xml_debug_level == -1) ? xml_get_debug_level() : xml_debug_level) < lvl) ? (void)0 : xml_debug_printf

#define ERR DEBUG_PRINT(1)
#define FIXME DEBUG_PRINT(2)
#define WARN DEBUG_PRINT(3)
#define TRACE DEBUG_PRINT(4)

#endif /* _XMLLITE_PRIVATE_H */

