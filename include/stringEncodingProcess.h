#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

enum encodingType
{
    UTF16BE,     // utf-16 big endian, MSB in low address
    UTF16LE,     // utf-16 little endian, MSB in high address
    UTF8WITHBOM, // utf-8 with BOM
    ASCII        // Ascii
};

// delete all char (one at once) from the string
bool deleteAllchar(string &raw, char charToDelete);

// judge the encoding type from the head character
// since the most coverd encodings(utf-8, GBK) encodes english character just as ASCii, so without BOM and CRLF issue they are the same
void judgeFromjudgeNumber(int judgeNumber, encodingType &type);

// check the string encoding, check the encoding is with BOM or not, judge what type of BOM it has
bool isBOMExists(string raw, encodingType &type);

// delete BOM and header && adjust CRLF (to ASCII)
bool transAnySupportedEncodingToASCII(string &raw, bool BOMExistStatus, encodingType type);