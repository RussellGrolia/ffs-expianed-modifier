#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

struct targetSequence
{
    size_t firstCharPos;
    string target;
};

enum encodingType
{
    UTF16BE,//utf-16 big endian, MSB in low address
    UTF16LE,//utf-16 little endian, MSB in high address
    UTF8WITHBOM,//utf-8 with BOM
    ASCII//Ascii
};

// check the string encoding, check the encoding is with BOM or not, judge what type of BOM it has
bool isBOMExist(string raw,encodingType &type);

// delete BOM and header && adjust CRLF (to ASCII)
bool transAnySupportedEncodingToASCII(string raw, string &result);
