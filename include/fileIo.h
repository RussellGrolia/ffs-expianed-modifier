#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// read file, return success status
bool readFile(string fileName, string &result, size_t &bytesReadTotal);

// write file return succes status
bool writeFile(string fileName, string result, size_t bytesReadTotal);