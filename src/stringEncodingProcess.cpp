#include "stringEncodingProcess.h"

#define getStrByte(n, str) ((str).c_str()[n])
#define keep8to23bit(n) (n & 0x00FFFF00)
#define fileLenWarning cout << "Too short string length, check file and its access permission" << endl
using namespace std;

// struct targetSequence
// {
//     size_t firstCharPos;
//     string target;
// };

// enum encodingType
// {
//     UTF16BE,//utf-16 big endian
//     UTF16LE,//utf-16 little endian
//     UTF8WITHBOM,//utf-8 with BOM
//     ASCII//ASCii
// };

//CRLF /r/n 0xD 0xA
bool deleteCR(string &raw)
{
    return true;
}

bool deleteEmptyCode(string &raw)
{
    return true;
}

void judgeFromjudgeNumber(int judgeNumber, encodingType &type)
{
    if (judgeNumber == 0x00EFBBBF)
    {
        type = UTF8WITHBOM;
    }
    else if (keep8to23bit(judgeNumber) == 0x00FEFF00)
    {
        type = UTF16BE;
    }
    else if (keep8to23bit(judgeNumber) == 0x00FFFE00)
    {
        type = UTF16LE;
    }
    else
    {
        type = ASCII;
    }
}

// check the string encoding, check the encoding is with BOM or not, judge what type of BOM it has
bool isBOMExists(string raw, encodingType &type)
{
    size_t strLen = raw.length();
    int judgeNumber = 0;
    if (strLen >= 3)
    {
        judgeNumber = (getStrByte(0, raw) << 16) + (getStrByte(1, raw) << 8) + getStrByte(2, raw);
        judgeFromjudgeNumber(judgeNumber, type);
    }
    else if (strLen >= 2)
    {
        judgeNumber = (getStrByte(0, raw) << 16) + (getStrByte(1, raw) << 8);
        judgeFromjudgeNumber(judgeNumber, type);
        fileLenWarning;
    }
    else
    {
        type = ASCII;
        fileLenWarning;
    }
    if (type < ASCII)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// delete BOM and header && adjust CRLF (to ASCII)
bool transAnySupportedEncodingToASCII(string raw, string &result, bool BOMExists)
{
    return true;
}
