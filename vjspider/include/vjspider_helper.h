/**************************************
 * @file    : vjspider_helper.h
 * @author  : admin@xcoder.in
 * @date    : 2012-5-30
 */
#ifndef VJSPIDER_HELPER_H
#define VJSPIDER_HELPER_H

#include "vjspider_config.h"

/**
 * Class VJCodeConvert
 * Convert code between GB2312 and UTF-8
 */
class VJSPIDER_API VJCodeConvert
{
public:
    VJCodeConvert(const char* input, unsigned int fromCodePage, unsigned int toCodePage);
    ~VJCodeConvert()
    {
        delete [] wcharBuf;
        delete [] charBuf;
    };

    const char*                 ToString()
    {
        return charBuf;
    };

private:
    wchar_t*                    wcharBuf;
    char*                       charBuf;
};

/**
 * The helper to parse the URL
 */
class VJSPIDER_API VJURLHelper
{
public:
    static char dec2hexChar(short int n)
    {
        if (0 <= n && n <= 9) return char(short('0') + n);
        else if (10 <= n && n <= 15) return char(short('A') + n - 10);
        else return char(0);
    }

    static short int hexChar2dec(char c)
    {
        if ('0'<=c && c<='9') return short(c - '0');
        else if ('a' <= c && c <= 'f') return (short(c - 'a') + 10);
        else if ('A' <= c && c <= 'F') return (short(c - 'A') + 10);
        else return -1;
    }

    static string               escapeURL(const string &URL);
};

extern int VJSPIDER_API VJRand();
extern void VJSPIDER_API VJSrand(unsigned int seed);

#endif
