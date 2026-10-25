#ifndef STRINGUTILS_H
#define STRINGUTILS_H


#include <stddef.h>

typedef struct {
    char* c_str;
    size_t length;
    size_t size;
    bool temp;
} string_t;

size_t String_LowestPowerOfTwo(size_t in);

void String_Terminate(string_t str);

void String_Fill(string_t str, char c);

void String_PrintStats(string_t str);

string_t String_NewL(size_t length);
string_t String_NewC(const char* str);
string_t String_NewS(string_t s);
string_t String_TempL(size_t length);
string_t String_TempC(const char* str);
string_t String_TempS(string_t s);
string_t String_Empty();

bool String_Compare(string_t a, string_t b);

void String_Resize(string_t* str, size_t size);
// string_t String_AppendS(string_t a, string_t b);
// string_t String_AppendC(string_t a, const char* b);
void String_AddS(string_t* dest, string_t a, string_t b);
void String_AddC(string_t* dest, string_t a, const char* b);


#endif
