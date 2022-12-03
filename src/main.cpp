#include"fileIo.h"
#include"stringEncodingProcess.h"
using namespace std;

//TODO: Add file i/o check
int main()
{
    string testString;
    encodingType ecType;
    bool BOMStatus;
    readFile("testFileUTF16LE.txt",testString);
    cout<<testString<<endl;
    BOMStatus = isBOMExists(testString,ecType);
    cout<<BOMStatus<<endl;
    transAnySupportedEncodingToASCII(testString,BOMStatus,ecType);
    cout<<testString<<endl;
    writeFile("testFileASCII3.txt",testString);
}