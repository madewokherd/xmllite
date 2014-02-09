/*
 * xmllite public definitions
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

#ifndef _XMLLITE_H
#define _XMLLITE_H

#include <stdint.h>
#include <wctype.h>

typedef struct _XMLGUID
{
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t Data4[8];
} XMLGUID;

#define DEFINE_XML_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    static const XMLGUID name = { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } };

typedef int32_t XMLHRESULT;

#define XML_S_OK ((XMLHRESULT)0)
#define XML_E_NOTIMPL ((XMLHRESULT)0x80004001)
#define XML_E_OUTOFMEMORY ((XMLHRESULT)0x8007000e)
#define XML_E_PENDING ((XMLHRESULT)0x8000000a)

#define XML_FAILED(hr) (((XMLHRESULT)hr) < 0)
#define XML_SUCCEEDED(hr) (((XMLHRESULT)hr) >= 0)

typedef uint16_t XMLWCHAR;

static inline unsigned int xml_wcslen( const XMLWCHAR *str )
{
    const XMLWCHAR *s = str;
    while (*s) s++;
    return s - str;
}

extern int xml_wcsicmp( const XMLWCHAR *str1, const XMLWCHAR *str2 );
extern int xml_wcsnicmp( const XMLWCHAR *str1, const XMLWCHAR *str2, int n );

typedef enum DtdProcessing
{
    DtdProcessing_Prohibit,
    DtdProcessing_Parse,
    _DtdProcessing_Last = DtdProcessing_Parse
} DtdProcessing;

typedef enum XmlError
{
    MX_E_MX = 0xc00cee00,
    MX_E_INPUTEND,
    MX_E_ENCODING,
    MX_E_ENCODINGSWITCH,
    MX_E_ENCODINGSIGNATURE,
    WC_E_WC = 0xc00cee20,
    WC_E_WHITESPACE,
    WC_E_SEMICOLON,
    WC_E_GREATERTHAN,
    WC_E_QUOTE,
    WC_E_EQUAL,
    WC_E_LESSTHAN,
    WC_E_HEXDIGIT,
    WC_E_DIGIT,
    WC_E_LEFTBRACKET,
    WC_E_LEFTPAREN,
    WC_E_XMLCHARACTER,
    WC_E_NAMECHARACTER,
    WC_E_SYNTAX,
    WC_E_CDSECT,
    WC_E_COMMENT,
    WC_E_CONDSECT,
    WC_E_DECLATTLIST,
    WC_E_DECLDOCTYPE,
    WC_E_DECLELEMENT,
    WC_E_DECLENTITY,
    WC_E_DECLNOTATION,
    WC_E_NDATA,
    WC_E_PUBLIC,
    WC_E_SYSTEM,
    WC_E_NAME,
    WC_E_ROOTELEMENT,
    WC_E_ELEMENTMATCH,
    WC_E_UNIQUEATTRIBUTE,
    WC_E_TEXTXMLDECL,
    WC_E_LEADINGXML,
    WC_E_TEXTDECL,
    WC_E_XMLDECL,
    WC_E_ENCNAME,
    WC_E_PUBLICID,
    WC_E_PESINTERNALSUBSET,
    WC_E_PESBETWEENDECLS,
    WC_E_NORECURSION,
    WC_E_ENTITYCONTENT,
    WC_E_UNDECLAREDENTITY,
    WC_E_PARSEDENTITY,
    WC_E_NOEXTERNALENTITYREF,
    WC_E_PI,
    WC_E_SYSTEMID,
    WC_E_QUESTIONMARK,
    WC_E_CDSECTEND,
    WC_E_MOREDATA,
    WC_E_DTDPROHIBITED,
    WC_E_INVALIDXMLSPACE,
    NC_E_NC = 0xc00cee60,
    NC_E_QNAMECHARACTER,
    NC_E_QNAMECOLON,
    NC_E_NAMECOLON,
    NC_E_DECLAREDPREFIX,
    NC_E_UNDECLAREDPREFIX,
    NC_E_EMPTYURI,
    NC_E_XMLPREFIXRESERVED,
    NC_E_XMLNSPREFIXRESERVED,
    NC_E_XMLURIRESERVED,
    NC_E_XMLNSURIRESERVED,
    SC_E_SC = 0xc00cee80,
    SC_E_MAXELEMENTDEPTH,
    SC_E_MAXENTITYEXPANSION,
    WR_E_WR = 0xc00cef00,
    WR_E_NONWHITESPACE,
    WR_E_NSPREFIXDECLARED,
    WR_E_NSPREFIXWITHEMPTYNSURI,
    WR_E_DUPLICATEATTRIBUTE,
    WR_E_XMLNSPREFIXDECLARATION,
    WR_E_XMLPREFIXDECLARATION,
    WR_E_XMLURIDECLARATION,
    WR_E_XMLNSURIDECLARATION,
    WR_E_NAMESPACEUNDECLARED,
    WR_E_INVALIDXMLSPACE,
    WR_E_INVALIDACTION,
    WR_E_INVALIDSURROGATEPAIR,
    XML_E_INVALID_DECIMAL = 0xc00ce01d,
    XML_E_INVALID_HEXIDECIMAL,
    XML_E_INVALID_UNICODE,
    XML_E_INVALIDENCODING = 0xc00ce06e
} XmlError;

typedef enum XmlNodeType {
    XmlNodeType_None                  = 0,
    XmlNodeType_Element               = 1,
    XmlNodeType_Attribute             = 2,
    XmlNodeType_Text                  = 3,
    XmlNodeType_CDATA                 = 4,
    XmlNodeType_ProcessingInstruction = 7,
    XmlNodeType_Comment               = 8,
    XmlNodeType_DocumentType          = 10,
    XmlNodeType_Whitespace            = 13,
    XmlNodeType_EndElement            = 15,
    XmlNodeType_XmlDeclaration        = 17,
    _XmlNodeType_Last                 = 17
} XmlNodeType;

typedef enum XmlReaderProperty
{
    XmlReaderProperty_MultiLanguage,
    XmlReaderProperty_ConformanceLevel,
    XmlReaderProperty_RandomAccess,
    XmlReaderProperty_XmlResolver,
    XmlReaderProperty_DtdProcessing,
    XmlReaderProperty_ReadState,
    XmlReaderProperty_MaxElementDepth,
    XmlReaderProperty_MaxEntityExpansion,
    _XmlReaderProperty_Last = XmlReaderProperty_MaxEntityExpansion
} XmlReaderProperty;

typedef enum XmlReadState
{
    XmlReadState_Initial,
    XmlReadState_Interactive,
    XmlReadState_Error,
    XmlReadState_EndOfFile,
    XmlReadState_Closed
} XmlReadState;

typedef struct XML_LARGE_INTEGER
{
    int64_t QuadPart;
} XML_LARGE_INTEGER;

typedef struct XML_ULARGE_INTEGER
{
    uint64_t QuadPart;
} XML_ULARGE_INTEGER;

typedef struct XML_FILETIME
{
    uint32_t dwLowDateTime;
    uint32_t dwHighDateTime;
} XML_FILETIME;

typedef struct XML_STATSTG
{
    XMLWCHAR *pwcsName;
    uint32_t type;
    XML_ULARGE_INTEGER cbSize;
    XML_FILETIME mtime;
    XML_FILETIME ctime;
    XML_FILETIME atime;
    uint32_t grfMode;
    uint32_t grfLocksSupported;
    XMLGUID clsid;
    uint32_t grfStateBits;
    uint32_t reserved;
} XML_STATSTG;

#ifdef __i386__
# ifdef __GNUC__
#  if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 2)) || defined(__APPLE__)
#   define _xml_stdcall __attribute__((__stdcall__)) __attribute__((__force_align_arg_pointer__))
#  else
#   define _xml_stdcall __attribute__((__stdcall__))
#  endif
# else
#  error You need to define _xml_stdcall for your compiler
# endif
#elif defined(__x86_64__) && defined (__GNUC__)
# define _xml_stdcall __attribute__((ms_abi))
#else
# define _xml_stdcall
#endif

#if defined(__GNUC__) && ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 2)))
# define XMLINLINE inline __attribute__((always_inline))
#else
# define XMLINLINE inline
#endif

DEFINE_XML_GUID(IID_IXmlUnknown, 0x00000000, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
DEFINE_XML_GUID(IID_IXmlMalloc, 0x00000002, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
DEFINE_XML_GUID(IID_IXmlSequentialStream, 0x0c733a30, 0x2a1c, 0x11ce, 0xad, 0xe5, 0x00, 0xaa, 0x00, 0x44, 0x77, 0x3d);
DEFINE_XML_GUID(IID_IXmlStream, 0x0000000c, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
DEFINE_XML_GUID(IID_IXmlReader, 0x7279fc81, 0x709d, 0x4095, 0xb6, 0x3d, 0x69, 0xfe, 0x4b, 0x0d, 0x90, 0x30);
DEFINE_XML_GUID(IID_IXmlReaderInput, 0x0b3ccc9b, 0x9214, 0x428b, 0xa2, 0xae, 0xef, 0x3a, 0xa8, 0x71, 0xaf, 0xda);

typedef struct IXmlUnknown IXmlUnknown;
typedef struct IXmlMalloc IXmlMalloc;
typedef struct IXmlSequentialStream IXmlSequentialStream;
typedef struct IXmlStream IXmlStream;
typedef struct IXmlReader IXmlReader;
typedef struct IXmlUnknown IXmlReaderInput;

/* IXmlUnknown */
#if defined(__cplusplus) && !defined(CINTERFACE)
struct IXmlUnknown {
    virtual XMLHRESULT _xml_stdcall QueryInterface(
        const XMLGUID *riid,
        void **ppvObject) = 0;

    virtual uint32_t _xml_stdcall AddRef(
        ) = 0;

    virtual uint32_t _xml_stdcall Release(
        ) = 0;
};
#else
typedef struct IXmlUnknownVtbl {
    /*** IXmlUnknown methods ***/
    XMLHRESULT (_xml_stdcall *QueryInterface)(
        IXmlUnknown* This,
        const XMLGUID * riid,
        void **ppvObject);

    uint32_t (_xml_stdcall *AddRef)(
        IXmlUnknown* This);

    uint32_t (_xml_stdcall *Release)(
        IXmlUnknown* This);
} IXmlUnknownVtbl;
struct IXmlUnknown {
    const IXmlUnknownVtbl* lpVtbl;
};

static XMLINLINE XMLHRESULT IXmlUnknown_QueryInterface(IXmlUnknown *This,const XMLGUID *riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This, riid, ppvObject);
}
static XMLINLINE uint32_t IXmlUnknown_AddRef(IXmlUnknown *This) {
    return This->lpVtbl->AddRef(This);
}
static XMLINLINE uint32_t IXmlUnknown_Release(IXmlUnknown *This) {
    return This->lpVtbl->Release(This);
}
#endif

/* IXmlMalloc */
#if defined(__cplusplus) && !defined(CINTERFACE)
struct IXmlMalloc : public IXmlUnknown {
    virtual void* _xml_stdcall Alloc(
        uint32_t cb) = 0;

    virtual void* _xml_stdcall Realloc(
        void *pv,
        uint32_t cb) = 0;

    virtual void _xml_stdcall Free(
        void *pv) = 0;

    virtual uint32_t _xml_stdcall GetSize(
        void *pv) = 0;

    virtual int32_t _xml_stdcall DidAlloc(
        void *pv) = 0;

    virtual void _xml_stdcall HeapMinimize(
        ) = 0;
};
#else
typedef struct IXmlMallocVtbl {
    /*** IXmlMalloc methods ***/
    XMLHRESULT (_xml_stdcall *QueryInterface)(
        IXmlMalloc* This,
        const XMLGUID * riid,
        void **ppvObject);

    uint32_t (_xml_stdcall *AddRef)(
        IXmlMalloc* This);

    uint32_t (_xml_stdcall *Release)(
        IXmlMalloc* This);

    void* (_xml_stdcall *Alloc)(
        IXmlMalloc* This,
        uint32_t cb);

    void* (_xml_stdcall *Realloc)(
        IXmlMalloc* This,
        void *pv,
        uint32_t cb);

    void (_xml_stdcall *Free)(
        IXmlMalloc* This,
        void *pv);

    uint32_t (_xml_stdcall *GetSize)(
        IXmlMalloc* This,
        void *pv);

    int32_t (_xml_stdcall *DidAlloc)(
        IXmlMalloc* This,
        void *pv);

    void (_xml_stdcall *HeapMinimize)(
        IXmlMalloc* This);
} IXmlMallocVtbl;
struct IXmlMalloc {
    const IXmlMallocVtbl* lpVtbl;
};

static XMLINLINE XMLHRESULT IXmlMalloc_QueryInterface(IXmlMalloc *This,const XMLGUID *riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This, riid, ppvObject);
}
static XMLINLINE uint32_t IXmlMalloc_AddRef(IXmlMalloc *This) {
    return This->lpVtbl->AddRef(This);
}
static XMLINLINE uint32_t IXmlMalloc_Release(IXmlMalloc *This) {
    return This->lpVtbl->Release(This);
}
static XMLINLINE void* IXmlMalloc_Alloc(IXmlMalloc *This,uint32_t cb) {
    return This->lpVtbl->Alloc(This, cb);
}
static XMLINLINE void* IXmlMalloc_Realloc(IXmlMalloc *This,void *pv, uint32_t cb) {
    return This->lpVtbl->Realloc(This, pv, cb);
}
static XMLINLINE void IXmlMalloc_Free(IXmlMalloc *This,void *pv) {
    This->lpVtbl->Free(This, pv);
}
static XMLINLINE uint32_t IXmlMalloc_GetSize(IXmlMalloc *This,void *pv) {
    return This->lpVtbl->GetSize(This, pv);
}
static XMLINLINE int32_t IXmlMalloc_DidAlloc(IXmlMalloc *This,void *pv) {
    return This->lpVtbl->DidAlloc(This, pv);
}
static XMLINLINE void IXmlMalloc_HeapMinimize(IXmlMalloc *This) {
    This->lpVtbl->HeapMinimize(This);
}
#endif

/* IXmlSequentialStream */
#if defined(__cplusplus) && !defined(CINTERFACE)
struct IXmlSequentialStream : public IXmlUnknown {
    virtual XMLHRESULT _xml_stdcall Read(
        void *pv,
        uint32_t cb,
        uint32_t *pcbRead) = 0;

    virtual XMLHRESULT _xml_stdcall Write(
        const void *pv,
        uint32_t cb,
        uint32_t *pcbWritten) = 0;
};
#else
typedef struct IXmlSequentialStreamVtbl {
    /*** IXmlSequentialStream methods ***/
    XMLHRESULT (_xml_stdcall *QueryInterface)(
        IXmlSequentialStream* This,
        const XMLGUID * riid,
        void **ppvObject);

    uint32_t (_xml_stdcall *AddRef)(
        IXmlSequentialStream* This);

    uint32_t (_xml_stdcall *Release)(
        IXmlSequentialStream* This);

    XMLHRESULT (_xml_stdcall *Read)(
        IXmlSequentialStream* This,
        void *pv,
        uint32_t cb,
        uint32_t *pcbRead);

    XMLHRESULT (_xml_stdcall *Write)(
        IXmlSequentialStream* This,
        const void *pv,
        uint32_t cb,
        uint32_t *pcbWritten);
} IXmlSequentialStreamVtbl;
struct IXmlSequentialStream {
    const IXmlSequentialStreamVtbl* lpVtbl;
};

static XMLINLINE XMLHRESULT IXmlSequentialStream_QueryInterface(IXmlSequentialStream *This,const XMLGUID *riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This, riid, ppvObject);
}
static XMLINLINE uint32_t IXmlSequentialStream_AddRef(IXmlSequentialStream *This) {
    return This->lpVtbl->AddRef(This);
}
static XMLINLINE uint32_t IXmlSequentialStream_Release(IXmlSequentialStream *This) {
    return This->lpVtbl->Release(This);
}
static XMLINLINE XMLHRESULT IXmlSequentialStream_Read(IXmlSequentialStream *This,void *pv,uint32_t cb,uint32_t *pcbRead) {
    return This->lpVtbl->Read(This, pv, cb, pcbRead);
}
static XMLINLINE XMLHRESULT IXmlSequentialStream_Write(IXmlSequentialStream *This,const void *pv,uint32_t cb,uint32_t *pcbWritten) {
    return This->lpVtbl->Write(This, pv, cb, pcbWritten);
}
#endif

/* IXmlStream */
#if defined(__cplusplus) && !defined(CINTERFACE)
struct IXmlStream : public IXmlSequentialStream {
    virtual XMLHRESULT _xml_stdcall Seek(
        XML_LARGE_INTEGER dlibMove,
        uint32_t dwOrigin,
        XML_ULARGE_INTEGER *plibNewPosition) = 0;

    virtual XMLHRESULT _xml_stdcall SetSize(
        XML_ULARGE_INTEGER libNewSize) = 0;

    virtual XMLHRESULT _xml_stdcall CopyTo(
        IXmlStream *pstm,
        XML_ULARGE_INTEGER cb,
        XML_ULARGE_INTEGER *pcbRead,
        XML_ULARGE_INTEGER *pcbWritten) = 0;

    virtual XMLHRESULT _xml_stdcall Commit(
        uint32_t grfCommitFlags) = 0;

    virtual XMLHRESULT _xml_stdcall Revert(
        ) = 0;

    virtual XMLHRESULT _xml_stdcall LockRegion(
        XML_ULARGE_INTEGER libOffset,
        XML_ULARGE_INTEGER cb,
        uint32_t dwLockType) = 0;

    virtual XMLHRESULT _xml_stdcall UnlockRegion(
        XML_ULARGE_INTEGER libOffset,
        XML_ULARGE_INTEGER cb,
        uint32_t dwLockType) = 0;

    virtual XMLHRESULT _xml_stdcall Stat(
        XML_STATSTG *pstatstg,
        uint32_t grfStatFlag) = 0;

    virtual XMLHRESULT _xml_stdcall Clone(
        IXmlStream **ppstm) = 0;
};
#else
typedef struct IXmlStreamVtbl {
    /*** IXmlStream methods ***/
    XMLHRESULT (_xml_stdcall *QueryInterface)(
        IXmlStream* This,
        const XMLGUID * riid,
        void **ppvObject);

    uint32_t (_xml_stdcall *AddRef)(
        IXmlStream* This);

    uint32_t (_xml_stdcall *Release)(
        IXmlStream* This);

    XMLHRESULT (_xml_stdcall *Read)(
        IXmlStream* This,
        void *pv,
        uint32_t cb,
        uint32_t *pcbRead);

    XMLHRESULT (_xml_stdcall *Write)(
        IXmlStream* This,
        const void *pv,
        uint32_t cb,
        uint32_t *pcbWritten);

    XMLHRESULT (_xml_stdcall *Seek)(
        IXmlStream* This,
        XML_LARGE_INTEGER dlibMove,
        uint32_t dwOrigin,
        XML_ULARGE_INTEGER *plibNewPosition);

    XMLHRESULT (_xml_stdcall *SetSize)(
        IXmlStream* This,
        XML_ULARGE_INTEGER libNewSize);

    XMLHRESULT (_xml_stdcall *CopyTo)(
        IXmlStream* This,
        IXmlStream *pstm,
        XML_ULARGE_INTEGER cb,
        XML_ULARGE_INTEGER *pcbRead,
        XML_ULARGE_INTEGER *pcbWritten);

    XMLHRESULT (_xml_stdcall *Commit)(
        IXmlStream* This,
        uint32_t grfCommitFlags);

    XMLHRESULT (_xml_stdcall *Revert)(
        IXmlStream* This);

    XMLHRESULT (_xml_stdcall *LockRegion)(
        IXmlStream* This,
        XML_ULARGE_INTEGER libOffset,
        XML_ULARGE_INTEGER cb,
        uint32_t dwLockType);

    XMLHRESULT (_xml_stdcall *UnlockRegion)(
        IXmlStream* This,
        XML_ULARGE_INTEGER libOffset,
        XML_ULARGE_INTEGER cb,
        uint32_t dwLockType);

    XMLHRESULT (_xml_stdcall *Stat)(
        IXmlStream* This,
        XML_STATSTG *pstatstg,
        uint32_t grfStatFlag);

    XMLHRESULT (_xml_stdcall *Clone)(
        IXmlStream* This,
        IXmlStream **ppstm);

} IXmlStreamVtbl;
struct IXmlStream {
    const IXmlStreamVtbl* lpVtbl;
};

static XMLINLINE XMLHRESULT IXmlStream_QueryInterface(IXmlStream *This,const XMLGUID *riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This, riid, ppvObject);
}
static XMLINLINE uint32_t IXmlStream_AddRef(IXmlStream *This) {
    return This->lpVtbl->AddRef(This);
}
static XMLINLINE uint32_t IXmlStream_Release(IXmlStream *This) {
    return This->lpVtbl->Release(This);
}
static XMLINLINE XMLHRESULT IXmlStream_Read(IXmlStream *This,void *pv,uint32_t cb,uint32_t *pcbRead) {
    return This->lpVtbl->Read(This, pv, cb, pcbRead);
}
static XMLINLINE XMLHRESULT IXmlStream_Write(IXmlStream *This,const void *pv,uint32_t cb,uint32_t *pcbWritten) {
    return This->lpVtbl->Write(This, pv, cb, pcbWritten);
}
static XMLINLINE XMLHRESULT IXmlStream_Seek(IXmlStream* This, XML_LARGE_INTEGER dlibMove, uint32_t dwOrigin, XML_ULARGE_INTEGER *plibNewPosition) {
    return This->lpVtbl->Seek(This, dlibMove, dwOrigin, plibNewPosition);
}
static XMLINLINE XMLHRESULT IXmlStream_SetSize(IXmlStream* This, XML_ULARGE_INTEGER libNewSize)
{
    return This->lpVtbl->SetSize(This, libNewSize);
}
static XMLINLINE XMLHRESULT IXmlStream_CopyTo(IXmlStream* This, IXmlStream *pstm, XML_ULARGE_INTEGER cb, XML_ULARGE_INTEGER *pcbRead, XML_ULARGE_INTEGER *pcbWritten)
{
    return This->lpVtbl->CopyTo(This, pstm, cb, pcbRead, pcbWritten);
}
static XMLINLINE XMLHRESULT IXmlStream_Commit(IXmlStream* This, uint32_t grfCommitFlags)
{
    return This->lpVtbl->Commit(This, grfCommitFlags);
}
static XMLINLINE XMLHRESULT IXmlStream_Revert(IXmlStream* This)
{
    return This->lpVtbl->Revert(This);
}
static XMLINLINE XMLHRESULT IXmlStream_LockRegion(IXmlStream* This, XML_ULARGE_INTEGER libOffset, XML_ULARGE_INTEGER cb, uint32_t dwLockType)
{
    return This->lpVtbl->LockRegion(This, libOffset, cb, dwLockType);
}
static XMLINLINE XMLHRESULT IXmlStream_UnlockRegion(IXmlStream* This, XML_ULARGE_INTEGER libOffset, XML_ULARGE_INTEGER cb, uint32_t dwLockType)
{
    return This->lpVtbl->UnlockRegion(This, libOffset, cb, dwLockType);
}
static XMLINLINE XMLHRESULT IXmlStream_Stat(IXmlStream* This, XML_STATSTG *pstatstg, uint32_t grfStatFlag)
{
    return This->lpVtbl->Stat(This, pstatstg, grfStatFlag);
}
static XMLINLINE XMLHRESULT IXmlStream_Clone(IXmlStream* This, IXmlStream **ppstm)
{
    return This->lpVtbl->Clone(This, ppstm);
}
#endif

/* IXmlReader */
#if defined(__cplusplus) && !defined(CINTERFACE)
struct IXmlReader : public IXmlUnknown {
    virtual XMLHRESULT _xml_stdcall SetInput(
        IXmlUnknown *input) = 0;

    virtual XMLHRESULT _xml_stdcall GetProperty(
        uint32_t property,
        intptr_t *value) = 0;

    virtual XMLHRESULT _xml_stdcall SetProperty(
        uint32_t property,
        intptr_t value) = 0;

    virtual XMLHRESULT _xml_stdcall Read(
        XmlNodeType *node_type) = 0;

    virtual XMLHRESULT _xml_stdcall GetNodeType(
        XmlNodeType *node_type) = 0;

    virtual XMLHRESULT _xml_stdcall MoveToFirstAttribute(
        ) = 0;

    virtual XMLHRESULT _xml_stdcall MoveToNextAttribute(
        ) = 0;

    virtual XMLHRESULT _xml_stdcall MoveToAttributeByName(
        const XMLWCHAR *property,
        const XMLWCHAR *namespaceUri) = 0;

    virtual XMLHRESULT _xml_stdcall MoveToElement(
        ) = 0;

    virtual XMLHRESULT _xml_stdcall GetQualifiedName(
        const XMLWCHAR **qualifiedName,
        uint32_t *qualifiedName_length) = 0;

    virtual XMLHRESULT _xml_stdcall GetNamespaceUri(
        const XMLWCHAR **namespaceUri,
        uint32_t *namespaceUri_length) = 0;

    virtual XMLHRESULT _xml_stdcall GetLocalName(
        const XMLWCHAR **local_name,
        uint32_t *local_name_length) = 0;

    virtual XMLHRESULT _xml_stdcall GetPrefix(
        const XMLWCHAR **prefix,
        uint32_t *prefix_length) = 0;

    virtual XMLHRESULT _xml_stdcall GetValue(
        const XMLWCHAR **value,
        uint32_t *value_length) = 0;

    virtual XMLHRESULT _xml_stdcall ReadValueChunk(
        XMLWCHAR *buffer,
        uint32_t chunk_size,
        uint32_t *read) = 0;

    virtual XMLHRESULT _xml_stdcall GetBaseUri(
        const XMLWCHAR **baseUri,
        uint32_t *baseUri_length) = 0;

    virtual int32_t _xml_stdcall IsDefault() = 0;

    virtual int32_t _xml_stdcall IsEmptyElement() = 0;

    virtual XMLHRESULT _xml_stdcall GetLineNumber(
        uint32_t *lineNumber) = 0;

    virtual XMLHRESULT _xml_stdcall GetLinePosition(
        uint32_t *linePosition) = 0;

    virtual XMLHRESULT _xml_stdcall GetAttributeCount(
        uint32_t *attributeCount) = 0;

    virtual XMLHRESULT _xml_stdcall GetDepth(
        uint32_t *depth) = 0;

    virtual int32_t _xml_stdcall IsEOF() = 0;
};
#else
typedef struct IXmlReaderVtbl {
    /*** IXmlReader methods ***/
    XMLHRESULT (_xml_stdcall *QueryInterface)(
        IXmlReader* This,
        const XMLGUID * riid,
        void **ppvObject);

    uint32_t (_xml_stdcall *AddRef)(
        IXmlReader* This);

    uint32_t (_xml_stdcall *Release)(
        IXmlReader* This);

    XMLHRESULT (_xml_stdcall *SetInput)(
        IXmlReader* This,
        IXmlUnknown *input);

    XMLHRESULT (_xml_stdcall *GetProperty)(
        IXmlReader* This,
        uint32_t property,
        intptr_t *value);

    XMLHRESULT (_xml_stdcall *SetProperty)(
        IXmlReader* This,
        uint32_t property,
        intptr_t value);

    XMLHRESULT (_xml_stdcall *Read)(
        IXmlReader* This,
        XmlNodeType *node_type);

    XMLHRESULT (_xml_stdcall *GetNodeType)(
        IXmlReader* This,
        XmlNodeType *node_type);

    XMLHRESULT (_xml_stdcall *MoveToFirstAttribute)(
        IXmlReader* This);

    XMLHRESULT (_xml_stdcall *MoveToNextAttribute)(
        IXmlReader* This);

    XMLHRESULT (_xml_stdcall *MoveToAttributeByName)(
        IXmlReader* This,
        const XMLWCHAR *property,
        const XMLWCHAR *namespaceUri);

    XMLHRESULT (_xml_stdcall *MoveToElement)(
        IXmlReader* This);

    XMLHRESULT (_xml_stdcall *GetQualifiedName)(
        IXmlReader* This,
        const XMLWCHAR **qualifiedName,
        uint32_t *qualifiedName_length);

    XMLHRESULT (_xml_stdcall *GetNamespaceUri)(
        IXmlReader* This,
        const XMLWCHAR **namespaceUri,
        uint32_t *namespaceUri_length);

    XMLHRESULT (_xml_stdcall *GetLocalName)(
        IXmlReader* This,
        const XMLWCHAR **local_name,
        uint32_t *local_name_length);

    XMLHRESULT (_xml_stdcall *GetPrefix)(
        IXmlReader* This,
        const XMLWCHAR **prefix,
        uint32_t *prefix_length);

    XMLHRESULT (_xml_stdcall *GetValue)(
        IXmlReader* This,
        const XMLWCHAR **value,
        uint32_t *value_length);

    XMLHRESULT (_xml_stdcall *ReadValueChunk)(
        IXmlReader* This,
        XMLWCHAR *buffer,
        uint32_t chunk_size,
        uint32_t *read);

    XMLHRESULT (_xml_stdcall *GetBaseUri)(
        IXmlReader* This,
        const XMLWCHAR **baseUri,
        uint32_t *baseUri_length);

    int32_t (_xml_stdcall *IsDefault)(IXmlReader* This);

    int32_t (_xml_stdcall *IsEmptyElement)(IXmlReader* This);

    XMLHRESULT (_xml_stdcall *GetLineNumber)(
        IXmlReader* This,
        uint32_t *lineNumber);

    XMLHRESULT (_xml_stdcall *GetLinePosition)(
        IXmlReader* This,
        uint32_t *linePosition);

    XMLHRESULT (_xml_stdcall *GetAttributeCount)(
        IXmlReader* This,
        uint32_t *attributeCount);

    XMLHRESULT (_xml_stdcall *GetDepth)(
        IXmlReader* This,
        uint32_t *depth);

    int32_t (_xml_stdcall *IsEOF)(IXmlReader* This);
} IXmlReaderVtbl;
struct IXmlReader {
    const IXmlReaderVtbl* lpVtbl;
};

static XMLINLINE XMLHRESULT IXmlReader_QueryInterface(IXmlReader *This,const XMLGUID *riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This, riid, ppvObject);
}
static XMLINLINE uint32_t IXmlReader_AddRef(IXmlReader *This) {
    return This->lpVtbl->AddRef(This);
}
static XMLINLINE uint32_t IXmlReader_Release(IXmlReader *This) {
    return This->lpVtbl->Release(This);
}
static XMLINLINE XMLHRESULT IXmlReader_SetInput(IXmlReader *This,IXmlUnknown *input) {
    return This->lpVtbl->SetInput(This, input);
}
static XMLINLINE XMLHRESULT IXmlReader_GetProperty(IXmlReader *This,uint32_t property,intptr_t *value) {
    return This->lpVtbl->GetProperty(This, property, value);
}
static XMLINLINE XMLHRESULT IXmlReader_SetProperty(IXmlReader *This,uint32_t property,intptr_t value) {
    return This->lpVtbl->SetProperty(This, property, value);
}
static XMLINLINE XMLHRESULT IXmlReader_Read(IXmlReader *This,XmlNodeType *node_type) {
    return This->lpVtbl->Read(This, node_type);
}
static XMLINLINE XMLHRESULT IXmlReader_GetNodeType(IXmlReader *This,XmlNodeType *node_type) {
    return This->lpVtbl->GetNodeType(This, node_type);
}
static XMLINLINE XMLHRESULT IXmlReader_MoveToFirstAttribute(IXmlReader *This) {
    return This->lpVtbl->MoveToFirstAttribute(This);
}
static XMLINLINE XMLHRESULT IXmlReader_MoveToNextAttribute(IXmlReader *This) {
    return This->lpVtbl->MoveToNextAttribute(This);
}
static XMLINLINE XMLHRESULT IXmlReader_MoveToAttributeByName(IXmlReader *This,const XMLWCHAR *property,const XMLWCHAR *namespaceUri) {
    return This->lpVtbl->MoveToAttributeByName(This, property, namespaceUri);
}
static XMLINLINE XMLHRESULT IXmlReader_MoveToElement(IXmlReader *This) {
    return This->lpVtbl->MoveToElement(This);
}
static XMLINLINE XMLHRESULT IXmlReader_GetQualifiedName(IXmlReader *This,const XMLWCHAR **qualifiedName,uint32_t *qualifiedName_length) {
    return This->lpVtbl->GetQualifiedName(This, qualifiedName, qualifiedName_length);
}
static XMLINLINE XMLHRESULT IXmlReader_GetNamespaceUri(IXmlReader *This,const XMLWCHAR **namespaceUri,uint32_t *namespaceUri_length) {
    return This->lpVtbl->GetNamespaceUri(This, namespaceUri, namespaceUri_length);
}
static XMLINLINE XMLHRESULT IXmlReader_GetLocalName(IXmlReader *This,const XMLWCHAR **local_name,uint32_t *local_name_length) {
    return This->lpVtbl->GetLocalName(This, local_name, local_name_length);
}
static XMLINLINE XMLHRESULT IXmlReader_GetPrefix(IXmlReader *This,const XMLWCHAR **prefix,uint32_t *prefix_length) {
    return This->lpVtbl->GetPrefix(This, prefix, prefix_length);
}
static XMLINLINE XMLHRESULT IXmlReader_GetValue(IXmlReader *This,const XMLWCHAR **value,uint32_t *value_length) {
    return This->lpVtbl->GetValue(This, value, value_length);
}
static XMLINLINE XMLHRESULT IXmlReader_ReadValueChunk(IXmlReader *This,XMLWCHAR *buffer,uint32_t chunk_size,uint32_t *read) {
    return This->lpVtbl->ReadValueChunk(This, buffer, chunk_size, read);
}
static XMLINLINE XMLHRESULT IXmlReader_GetBaseUri(IXmlReader *This,const XMLWCHAR **baseUri,uint32_t *baseUri_length) {
    return This->lpVtbl->GetBaseUri(This, baseUri, baseUri_length);
}
static XMLINLINE int32_t IXmlReader_IsDefault(IXmlReader *This) {
    return This->lpVtbl->IsDefault(This);
}
static XMLINLINE int32_t IXmlReader_IsEmptyElement(IXmlReader *This) {
    return This->lpVtbl->IsEmptyElement(This);
}
static XMLINLINE XMLHRESULT IXmlReader_GetLineNumber(IXmlReader *This,uint32_t *lineNumber) {
    return This->lpVtbl->GetLineNumber(This, lineNumber);
}
static XMLINLINE XMLHRESULT IXmlReader_GetLinePosition(IXmlReader *This,uint32_t *linePosition) {
    return This->lpVtbl->GetLinePosition(This, linePosition);
}
static XMLINLINE XMLHRESULT IXmlReader_GetAttributeCount(IXmlReader *This,uint32_t *attributeCount) {
    return This->lpVtbl->GetAttributeCount(This, attributeCount);
}
static XMLINLINE XMLHRESULT IXmlReader_GetDepth(IXmlReader *This,uint32_t *depth) {
    return This->lpVtbl->GetDepth(This, depth);
}
static XMLINLINE int32_t IXmlReader_IsEOF(IXmlReader *This) {
    return This->lpVtbl->IsEOF(This);
}
#endif

/* IXmlReaderInput */
#if !defined(__cplusplus) || defined(CINTERFACE)
static XMLINLINE XMLHRESULT IXmlReaderInput_QueryInterface(IXmlReaderInput *This,const XMLGUID *riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This, riid, ppvObject);
}
static XMLINLINE uint32_t IXmlReaderInput_AddRef(IXmlReaderInput *This) {
    return This->lpVtbl->AddRef(This);
}
static XMLINLINE uint32_t IXmlReaderInput_Release(IXmlReaderInput *This) {
    return This->lpVtbl->Release(This);
}
#endif

#if defined(__cplusplus)
# define XML_EXTERN_C extern "C"
#else
# define XML_EXTERN_C
#endif

XML_EXTERN_C XMLHRESULT CreateXmlReader(const XMLGUID *riid, void **obj, IXmlMalloc *imalloc);

XML_EXTERN_C XMLHRESULT CreateXmlReaderInputWithEncodingName(IXmlUnknown *stream,
                                                             IXmlMalloc *imalloc,
                                                             const XMLWCHAR *encoding,
                                                             uint32_t hint,
                                                             const XMLWCHAR *base_uri,
                                                             IXmlReaderInput **ppInput);

#endif /* _XMLLITE_H */

