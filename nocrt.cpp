#pragma once
#include "nocrt.h"


#undef WIN32_NO_STATUS
#include <ntstatus.h>
#include <intrin.h>
void* c_crt::memcpy(void* dest, const void* src, unsigned __int64 count)
{
    char* char_dest = (char*)dest;
    char* char_src = (char*)src;
    if ((char_dest <= char_src) || (char_dest >= (char_src + count)))
    {
        while (count > 0)
        {
            *char_dest = *char_src;
            char_dest++;
            char_src++;
            count--;
        }
    }
    else
    {
        char_dest = (char*)dest + count - 1;
        char_src = (char*)src + count - 1;
        while (count > 0)
        {
            *char_dest = *char_src;
            char_dest--;
            char_src--;
            count--;
        }
    }
    return dest;
}
void* c_crt::memset(void* src, int val, unsigned __int64 count)
{
    __stosb((unsigned char*)((unsigned long long)(volatile char*)src), val, count);
    return src;
}
void* c_crt::memccpy(void* to, const void* from, int c, unsigned __int64 count)
{
    char t;
    unsigned __int64 i;
    char* dst = (char*)to;
    const char* src = (const char*)from;
    for (i = 0; i < count; i++)
    {
        dst[i] = t = src[i];
        if (t == 0) break;
        if (t == c) return &dst[i + 1];
    }
    return 0;
}

void* c_crt::memchr(const void* s, int c, unsigned __int64 n)
{
    if (n)
    {
        const char* p = (const char*)s;
        do
        {
            if (*p++ == c) return (void*)(p - 1);
        } while (--n != 0);
    }
    return 0;
}

int  c_crt::memcmp(const void* s1, const void* s2, unsigned __int64 n)
{
    if (n != 0)
    {
        const unsigned char* p1 = (unsigned char*)s1, * p2 = (unsigned char*)s2;
        do
        {
            if (*p1++ != *p2++) return (*--p1 - *--p2);
        } while (--n != 0);
    }
    return 0;
}
int  c_crt::memicmp(const void* s1, const void* s2, unsigned __int64 n)
{
    if (n != 0)
    {
        const unsigned char* p1 = (unsigned char*)s1, * p2 = (unsigned char*)s2;
        do
        {
            if (toupper(*p1) != toupper(*p2)) return (*p1 - *p2);
            p1++;
            p2++;
        } while (--n != 0);
    }
    return 0;
}
void* c_crt::memmove(void* dest, const void* src, unsigned __int64 count)
{
    char* char_dest = (char*)dest;
    char* char_src = (char*)src;
    if ((char_dest <= char_src) || (char_dest >= (char_src + count)))
    {
        while (count > 0)
        {
            *char_dest = *char_src;
            char_dest++;
            char_src++;
            count--;
        }
    }
    else
    {
        char_dest = (char*)dest + count - 1;
        char_src = (char*)src + count - 1;
        while (count > 0)
        {
            *char_dest = *char_src;
            char_dest--;
            char_src--;
            count--;
        }
    }
    return dest;
}

int c_crt::toupper(int c)
{
    if (c >= 'a' && c <= 'z') return c - 'a' + 'A';
    return c;
}

int c_crt::tolower(int c)
{
    if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
    return c;
}

char* c_crt::_cslwr(char* x)
{
    char* y = x;
    while (*y)
    {
        *y = tolower(*y);
        y++;
    }
    return x;
}

char* c_crt::_csupr(char* x)
{
    char* y = x;
    while (*y)
    {
        *y = tolower(*y);
        y++;
    }
    return x;
}

int c_crt::strlen(const char* string)
{
    int cnt = 0;
    if (string)
    {
        for (; *string != 0; ++string) ++cnt;
    }
    return cnt;
}

const char* c_crt::strcpy(char* buffer, const char* string)
{
    char* ret = buffer;
    while (*string) *buffer++ = *string++;
    *buffer = 0;
    return ret;
}

const char* c_crt::strcpy(char* buffer, const wchar_t* string)
{
    char* ret = buffer;
    while (*string) *buffer++ = char(*string++);
    *buffer = 0;
    return ret;
}

int c_crt::strcmp(const char* cs, const char* ct)
{
    if (cs && ct)
    {
        while (*cs == *ct)
        {
            if (*cs == 0 && *ct == 0) return 0;
            if (*cs == 0 || *ct == 0) break;
            cs++;
            ct++;
        }
        return *cs - *ct;
    }
    return -1;
}

int c_crt::stricmp(const char* cs, const char* ct)
{
    if (cs && ct)
    {
        while (tolower(*cs) == tolower(*ct))
        {
            if (*cs == 0 && *ct == 0) return 0;
            if (*cs == 0 || *ct == 0) break;
            cs++;
            ct++;
        }
        return tolower(*cs) - tolower(*ct);
    }
    return -1;
}

int c_crt::stricmp(UCHAR cs, const char* ct)
{
    if (ct)
    {
        while (tolower(cs) == tolower(*ct))
        {
            if (cs == 0 && *ct == 0) return 0;
            if (cs == 0 || *ct == 0) break;

            ct++;
        }
        return tolower(cs) - tolower(*ct);
    }
    return -1;
}

wchar_t* c_crt::_cslwr(wchar_t* x)
{
    wchar_t* y = x;
    while (*y)
    {
        *y = towlower(*y);
        y++;
    }
    return x;
}

wchar_t* c_crt::_csupr(wchar_t* x)
{
    wchar_t* y = x;
    while (*y)
    {
        *y = towupper(*y);
        y++;
    }
    return x;
}

int c_crt::strlen(const wchar_t* string)
{
    int cnt = 0;
    if (string)
    {
        for (; *string != 0; ++string) ++cnt;
    }
    return cnt;
}

const wchar_t* c_crt::strcpy(wchar_t* buffer, const wchar_t* string)
{
    wchar_t* ret = buffer;
    while (*string) *buffer++ = *string++;
    *buffer = L'\0';
    return ret;
}

const wchar_t* c_crt::strcpy(wchar_t* buffer, const char* string)
{
    wchar_t* ret = buffer;
    while (*string) *buffer++ = wchar_t(*string++);
    *buffer = 0;
    return ret;
}

int c_crt::strcmp(const wchar_t* cs, const wchar_t* ct)
{
    if (cs && ct)
    {
        while (*cs == *ct)
        {
            if (*cs == 0 && *ct == 0) return 0;
            if (*cs == 0 || *ct == 0) break;
            cs++;
            ct++;
        }
        return *cs - *ct;
    }
    return -1;
}
int c_crt::stricmp(const wchar_t* cs, const wchar_t* ct)
{
    if (cs && ct)
    {
        while (towlower(*cs) == towlower(*ct))
        {
            if (*cs == 0 && *ct == 0) return 0;
            if (*cs == 0 || *ct == 0) break;
            cs++;
            ct++;
        }
        return towlower(*cs) - towlower(*ct);
    }
    return -1;
}

int c_crt::wtoupper(int c)
{
    if (c >= L'a' && c <= L'z') return c - L'a' + L'A';
    if (c >= L'à' && c <= L'ÿ') return c - L'à' + L'À';
    if (c == L'¸') return L'¨';
    return c;
}

int c_crt::wtolower(int c)
{
    if (c >= L'A' && c <= L'Z') return c - L'A' + L'a';
    if (c >= L'À' && c <= L'ß') return c - L'À' + L'à';
    if (c == L'¨') return L'¸';
    return c;
}

int c_crt::towupper(int c)
{
    if (c >= L'a' && c <= L'z') return c - L'a' + L'A';
    if (c >= L'à' && c <= L'ÿ') return c - L'à' + L'À';
    if (c == L'¸') return L'¨';
    return c;
}
int c_crt::towlower(int c)
{
    if (c >= L'A' && c <= L'Z') return c - L'A' + L'a';
    if (c >= L'À' && c <= L'ß') return c - L'À' + L'à';
    if (c == L'¨') return L'¸';
    return c;
}

int c_crt::wstrlen(const wchar_t* s)
{
    int cnt = 0;
    if (!s) return 0;
    for (; *s != 0; ++s) ++cnt;
    return cnt;
}

int c_crt::wstrcmp(const wchar_t* cs, const wchar_t* ct)
{
    if (cs && ct)
    {
        while (*cs == *ct)
        {
            if (*cs == 0 && *ct == 0) return 0;
            if (*cs == 0 || *ct == 0) break;
            cs++;
            ct++;
        }
        return *cs - *ct;
    }
    return -1;
}
int c_crt::wstricmp(const wchar_t* cs, const wchar_t* ct)
{
    if (cs && ct)
    {
        while (wtolower(*cs) == wtolower(*ct))
        {
            if (*cs == 0 && *ct == 0) return 0;
            if (*cs == 0 || *ct == 0) break;
            cs++;
            ct++;
        }
        return wtolower(*cs) - wtolower(*ct);
    }
    return -1;
}

wchar_t* c_crt::wstrstr(const wchar_t* s, const wchar_t* find)
{
    wchar_t c, sc;
    if ((c = *find++) != 0)
    {
        do
        {
            do
            {
                if ((sc = *s++) == 0)
                    return 0;
            } while (sc != c);
        } while (wstricmp(s, find) != 0);
        s--;
    }
    return (wchar_t*)s;
}

wchar_t* c_crt::wstrset(wchar_t* szToFill, int szFill)
{
    wchar_t* t = szToFill;
    while (*szToFill != 0)
    {
        *szToFill = szFill;
        szToFill++;
    }
    return t;
}
wchar_t* c_crt::wstrnset(wchar_t* szToFill, int szFill, unsigned __int64 sizeMaxFill)
{
    wchar_t* t = szToFill;
    int i = 0;
    while (*szToFill != 0 && i < (int)sizeMaxFill)
    {
        *szToFill = szFill;
        szToFill++;
        i++;
    }
    return t;
}
wchar_t* c_crt::wstrrev(wchar_t* s)
{
    wchar_t a, * b, * e;
    b = e = s;
    while (*e) e++;
    e--;
    while (b < e)
    {
        a = *b;
        *b = *e;
        *e = a;
        b++;
        e--;
    }
    return s;
}

int c_crt::wstrnicmp(const wchar_t* s1, const wchar_t* s2, unsigned __int64 n)
{
    if (n == 0) return 0;
    do
    {
        if (wtoupper(*s1) != wtoupper(*s2++)) return wtoupper(*(unsigned const char*)s1) - wtoupper(*(unsigned const char*)--s2);
        if (*s1++ == 0) break;
    } while (--n != 0);
    return 0;
}

wchar_t* c_crt::wstrlwr(wchar_t* x)
{
    wchar_t* y = x;
    while (*y)
    {
        *y = wtolower(*y);
        y++;
    }
    return x;
}

wchar_t* c_crt::wstrchr(const wchar_t* s, wchar_t c)
{
    wchar_t cc = c;
    const wchar_t* sp = (wchar_t*)0;
    while (*s)
    {
        if (*s == cc) sp = s;
        s++;
    }
    if (cc == 0) sp = s;
    return (wchar_t*)sp;
}

wchar_t* c_crt::wstrtok_s(wchar_t* str, const wchar_t* delim, wchar_t** ctx)
{
    if (!str) str = *ctx;
    while (*str && wstrchr(delim, *str)) str++;
    if (!*str)
    {
        *ctx = str;
        return 0;
    }
    *ctx = str + 1;
    while (**ctx && !wstrchr(delim, **ctx)) (*ctx)++;
    if (**ctx) *(*ctx)++ = 0;
    return str;
}

bool c_crt::iswdigit(wchar_t c)
{
    return c >= L'0' && c <= L'9';
}

__int64 c_crt::wtoi64(const wchar_t* nptr)
{
    wchar_t* s = (wchar_t*)nptr;
    __int64 acc = 0;
    int neg = 0;
    if (nptr == 0) return 0;
    while (*s = L' ') s++;
    if (*s == L'-')
    {
        neg = 1;
        s++;
    }
    else if (*s == L'+') s++;
    while (iswdigit(*s))
    {
        acc = 10 * acc + (*s - L'0');
        s++;
    }
    if (neg) acc *= -1;
    return acc;
}
int c_crt::wtoi(const wchar_t* nptr)
{
    wchar_t* s = (wchar_t*)nptr;
    int acc = 0;
    int neg = 0;
    if (nptr == 0) return 0;
    while (*s = L' ') s++;
    if (*s == L'-')
    {
        neg = 1;
        s++;
    }
    else if (*s == L'+') s++;
    while (iswdigit(*s))
    {
        acc = 10 * acc + (*s - L'0');
        s++;
    }
    if (neg) acc *= -1;
    return acc;
}
wchar_t* c_crt::itow(int number, wchar_t* destination, int base)
{
    int count = 0;
    do
    {
        int digit = number % base;
        destination[count++] = (digit > 9) ? digit - 10 + L'A' : digit + L'0';
    } while ((number /= base) != 0);
    destination[count] = 0;
    int i;
    for (i = 0; i < count / 2; ++i)
    {
        wchar_t symbol = destination[i];
        destination[i] = destination[count - i - 1];
        destination[count - i - 1] = symbol;
    }
    return destination;
}


const char* c_crt::strstr(char const* _Str, char const* _SubStr)
{
    const char* bp = _SubStr;
    const char* back_pos;
    while (*_Str != 0 && _Str != 0 && _SubStr != 0)
    {
        back_pos = _Str;
        while (tolower(*back_pos++) == tolower(*_SubStr++))
        {
            if (*_SubStr == 0)
            {
                return (char*)(back_pos - strlen(bp));
            }
        }
        ++_Str;
        _SubStr = bp;
    }
    return 0;
}

char* c_crt::strcatA(char* dest, const char* src)
{
    if ((dest == 0) || (src == 0))
        return dest;

    while (*dest != 0)
        dest++;

    while (*src != 0) {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = 0;
    return dest;
}

wchar_t* c_crt::strcatW(wchar_t* dest, const wchar_t* src)
{
    if ((dest == 0) || (src == 0))
        return dest;

    while (*dest != 0)
        dest++;

    while (*src != 0) {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = 0;
    return dest;
}