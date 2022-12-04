#include<string>
#include<vector>
#include<regex>
#include<iostream>
#include<tuple>
#include<iterator>
using namespace std;

//mode == 0: only modify sqeuences with the same length (safe mode)
//mode == 1: modify all sequences matched
bool replaceFFSBytes(string &raw,vector<pair<size_t,size_t>>targets,string openSequence,size_t openSequenceLen,int mode);

// open sequence is a special byte sequence, it represents the open stutus of the bios option
bool getOpenSequence(string &openSequence, size_t &seqLen);


bool regexFind(string raw,regex payload,vector<pair<size_t,size_t>> &targets);

// using regex to match "equal"
// pair<size_t,size_t>the first size_t is the position of the target in ffs file
// the second size_t is the length of the target if not match, will not chanrge a thing
bool praseIFRFile(string &rawffs, vector<pair<size_t,size_t>> &targets);


