#include "fileIo.h"

#define READ_FILE_ONCE_SIZE 100000000 // 100M
#define fileWarning(str) cout << "File " << str << " FAILED" << endl

using namespace std;

char buffer[READ_FILE_ONCE_SIZE + 1];

bool readFile(string fileName, string &result, size_t &bytesReadTotal)
{
    FILE *inFile = NULL;
    size_t readCount = 0;
    bytesReadTotal = 0;
    try
    {
        inFile = fopen64(fileName.c_str(), "rb");
        if (inFile == NULL)
        {
            fileWarning("open");
            return false;
        }
        do
        {
            readCount = fread(buffer, sizeof(char), READ_FILE_ONCE_SIZE, inFile);
            result.append(buffer, readCount);
            bytesReadTotal += readCount;
        } while (readCount == READ_FILE_ONCE_SIZE);
        // TODO: check if the file read is complete
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << '\n';
        return false;
    }
    fclose(inFile);
    return true;
}

// write file return succes status
bool writeFile(string fileName, string result, size_t bytesToWrite)
{
    FILE *outFile = NULL;
    size_t writeCount = 0;
    try
    {
        outFile = fopen64(fileName.c_str(), "wb");
        if (outFile == NULL)
        {
            fileWarning("open");
            return false;
        }
        writeCount = fwrite(result.c_str(), sizeof(char), bytesToWrite, outFile);
        if (writeCount != bytesToWrite)
        {
            fileWarning("write");
            fclose(outFile);
            return false;
        }
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << '\n';
        return false;
    }
    fclose(outFile);
    return true;
}