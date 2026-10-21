#include "stringutils.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

size_t String_LowestPowerOfTwo(size_t in)
{
    size_t r;
    if (in <= 1) r = 1;
    else
    {
        in++;
        size_t nl = in;
        size_t mult = 1;
        char d = 0;
        for (int i = 0; i < 64 && nl > 1; i++)
        {
            size_t ln = nl;
            nl = nl >> 1;
            if (nl * 2 != ln) d = 1;
            mult *= 2;
        }
        if (d) mult *= 2;
        r = mult;
    }
    return r;
}

void String_Fill(string_t str, char c)
{
    if (!str.c_str || !str.length || !str.size) return;
    memset(str.c_str, c, str.size);
}

void String_PrintStats(string_t str)
{
    if (!str.c_str)
    {
        printf("String is empty!\n");
        return;
    }

    printf("String: len=%lld, size=%lld, str='%s'\n", str.length, str.size, str.c_str);
}

string_t String_NewL(size_t length)
{
    string_t r;
    r.length = length;
    r.size = String_LowestPowerOfTwo(length);
    r.c_str = (char*)malloc(r.size * sizeof(char));
    String_Fill(r, 0);
    return r;
}
string_t String_NewC(const char* str)
{
    if (!str) return String_Empty();

    string_t r;
    r.length = strlen(str);
    r.size = String_LowestPowerOfTwo(r.length);
    r.c_str = (char*)malloc(r.size * sizeof(char));
    String_Fill(r, 0);
    memcpy_s(r.c_str, r.length, str, r.length);
    return r;
}
string_t String_Empty()
{
    return (string_t){};
}

void String_Resize(string_t* str, size_t size)
{
    if(!str) return;

    size = String_LowestPowerOfTwo(size);
    if (size <= str->size) return;
    if (str->c_str)
    {
        str->c_str = (char*)realloc(str->c_str, size * sizeof(char));
    }
    else
    {
        str->c_str = (char*)malloc(size * sizeof(char));
    }
}

void String_AddS(string_t* dest, string_t a, string_t b)
{
    if(!dest) return;
    if (!a.c_str) a.length = 0;
    if (!b.c_str) b.length = 0;
    dest->length = a.length + b.length;

    if (!dest->c_str)
    {
        *dest = String_NewL(dest->length);
        if (a.length) memcpy_s(dest->c_str, dest->length, a.c_str, a.length);
        if (b.length) memcpy_s(dest->c_str + a.length, dest->length - a.length, b.c_str,  b.length);
    }
    else if (dest->c_str == a.c_str)
    {
        String_Resize(dest, dest->length);
        if (b.length) memcpy_s(dest->c_str + a.length, dest->length - a.length, b.c_str,  b.length);
    }
    else
    {
        String_Resize(dest, dest->length);
        String_Fill(*dest, 0);
        if (a.length) memcpy_s(dest->c_str, dest->length, a.c_str, a.length);
        if (b.length) memcpy_s(dest->c_str + a.length, dest->length - a.length, b.c_str,  b.length);
    }
}
void String_AddC(string_t* dest, string_t a, const char* b)
{
    if(!dest) return;

    string_t B;
    B.c_str = (char*)b;
    B.length = strlen(b);
    B.size = 0;
    String_AddS(dest, a, B);
}

void String_Terminate(string_t str)
{
    if(str.c_str) free(str.c_str);
}