#include"fileIo.h"
#include"stringEncodingProcess.h"
#include"stringRegexRuledModify.h"

using namespace std;

//TODO: Add file i/o check
//TODO: rewrite file system
int main()
{
    string testString;
    encodingType ecType;
    size_t byteReadTotal=0;
    vector<pair<size_t,size_t>>target(4000);//reserve space
    bool BOMStatus;
    readFile("changedVersion IFR.txt",testString,byteReadTotal);
    BOMStatus = isBOMExists(testString,ecType);
    transAnySupportedEncodingToASCII(testString,BOMStatus,ecType);
    modifyFFSFile(testString,target);
    writeFile("changedVersion IFR ASCII.txt",testString,byteReadTotal);
}