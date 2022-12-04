#include<string>
#include<vector>
#include<regex>
#include<iostream>
#include<tuple>
#include<iterator>
using namespace std;

//
bool getOpenSequence(string &openSequence,size_t &seqLen);

//using regex to match "equal"
//pair<size_t,size_t>the first size_t is the position of the target in ffs file
//the second size_t is the length of the target if not match, will not chanrge a thing 
bool modifyFFSFile(string &rawffs, vector<pair<size_t,size_t>> &targets);

