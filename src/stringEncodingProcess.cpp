#include "stringEncodingProcess.h"
#include<iomanip> 

#define fileLenWarning() cout << "Too short string length, check file and its access permission" << endl

#define keep16to31bit(n) (n & 0xFFFF0000)
#define keep8to31bit(n) (n & 0xFFFFFF00)
#define offset(n) (8*(sizeof(int)-n-1))

#define getStrByte(n, str) ((str).c_str()[n])
#define getPureNbyte(n,str) ((0x0FF<<offset(n))&(getStrByte(n, str) << offset(n)))
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

bool deleteAllchar(string &raw, char charToDelete)
{
    raw.erase(remove(raw.begin(), raw.end(), charToDelete), raw.end());
    return true;
}

//int xx(char[0])xx(char[1])xx(char[2])xx(char[3])
void judgeFromjudgeNumber(int judgeNumber, encodingType &type)
{
    cout<<setbase(16)<<judgeNumber<<endl;
    if (judgeNumber == 0xEFBBBF00)
    {
        type = UTF8WITHBOM;
    }
    else if (keep16to31bit(judgeNumber) == 0xFEFF0000)
    {
        type = UTF16BE;
    }
    else if (keep16to31bit(judgeNumber) == 0xFFFE0000)
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
        judgeNumber = getPureNbyte(0,raw)+getPureNbyte(1,raw)+getPureNbyte(2,raw);
        judgeFromjudgeNumber(judgeNumber, type);
    }
    else if (strLen >= 2)
    {
        judgeNumber = getPureNbyte(0,raw)+getPureNbyte(1,raw);
        judgeFromjudgeNumber(judgeNumber, type);
        fileLenWarning();
    }
    else
    {
        type = ASCII;
        fileLenWarning();
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
bool transAnySupportedEncodingToASCII(string &raw, bool BOMExistStatus, encodingType type)
{
    if (BOMExistStatus)
    {
        if (type == UTF16BE | type == UTF16LE)
        {
            raw.erase(0, 2);
        }
        else
        {
            raw.erase(0, 3);
        }
    }
    // CRLF: (/r/n 0xD,0xA), to modify the encoding in pure ACSII mode, the CR /r (0x0D) must be removed from the string
    deleteAllchar(raw, (char)0x0D);
    // utf-16 encoding is with 0x0 embedding. remove for speed
    deleteAllchar(raw, (char)0x00);
    return true;
}
