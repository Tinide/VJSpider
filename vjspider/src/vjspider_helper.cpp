#include <vjspider_helper.h>

static unsigned long int __next_seed = 1;
int VJRand()
{
    __next_seed = __next_seed * 1103515245 + 12345;  
    return (unsigned int)(__next_seed % 1000000000);
}
void VJSrand(unsigned int seed)
{  
    __next_seed = seed;      
}

VJCodeConvert::VJCodeConvert(const char* input, unsigned int fromCodePage, unsigned int toCodePage)
{
    // 先获取转换后的长度
    int len = MultiByteToWideChar(fromCodePage, 0, input, -1, NULL, 0);

    // 分配宽字符空间
    wcharBuf = new wchar_t[len];

    // 转换为宽字符
    MultiByteToWideChar(fromCodePage, 0, input, -1, wcharBuf, len);

    // 获取目标编码格式的字符串长度
    len = WideCharToMultiByte(toCodePage, 0, wcharBuf, -1, NULL, 0, NULL, NULL);

    // 分配目标编码字符串空间
    charBuf = new char[len];

    // 转换到目标编码
    WideCharToMultiByte(toCodePage, 0, wcharBuf, -1, charBuf, len, NULL, NULL);
}

string VJURLHelper::escapeURL(const string &URL)
{
    string result = "";
    for ( unsigned int i=0; i<URL.size(); i++ )
    {
        char c = URL[i];
        if (
            ( '0'<=c && c<='9' ) ||
            ( 'a'<=c && c<='z' ) ||
            ( 'A'<=c && c<='Z' ) ||
            c=='*' || c=='.' ||c=='_' || c=='-'
        ) result += c;
        else if (c==' ') result+='+';
        else if (c=='/') result+="%2F";
        else {
            int j = (short int)c;
            if ( j < 0 ) j += 256;
            int i1, i0;
            i1 = j / 16;
            i0 = j - i1*16;
            result += '%';
            result += dec2hexChar(i1);
            result += dec2hexChar(i0);
        }
    }
    return result;
}
