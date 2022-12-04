#include"fileIo.h"
#include"stringEncodingProcess.h"
#include"stringRegexRuledModify.h"

using namespace std;

//TODO: Add file i/o check
//TODO: rewrite file system
int main()
{
    string openSequence,rawIFRStr,rawFFSStr;
    encodingType ecType;
    size_t byteReadTotalIFR=0,byteReadTotalFFS=0,openSequcenceLen=0;
    vector<pair<size_t,size_t>>targets;
    targets.reserve(8000);//reserve space
    bool BOMStatus;

    readFile("changedVersion IFR.txt",rawIFRStr,byteReadTotalIFR);
    BOMStatus = isBOMExists(rawIFRStr,ecType);
    transAnySupportedEncodingToASCII(rawIFRStr,BOMStatus,ecType);
    praseIFRFile(rawIFRStr,targets);

    getOpenSequence(openSequence,openSequcenceLen);
    readFile("changedVersion.ffs",rawFFSStr,byteReadTotalFFS);
    
    replaceFFSBytes(rawFFSStr,targets,openSequence,openSequcenceLen,0);
    writeFile("newVersion.ffs",rawFFSStr,byteReadTotalFFS);
    return 0;
}