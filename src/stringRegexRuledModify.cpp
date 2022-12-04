#include "stringRegexRuledModify.h"

using namespace std;

// struct targetSequence
// {
//     size_t firstCharPos;
//     string target;
// };

// open sequence is a special byte sequence, it represents the open stutus of the bios option

bool getOpenSequence(string &openSequence, size_t &seqLen)
{
    int tempChar = 0;
    seqLen = 0;
    string tempNum;
    cin >> seqLen;
    openSequence.clear();
    for (size_t i = 0; i < seqLen; i++)
    {
        cin >> tempNum;
        tempNum.insert(0, "0x");
        tempChar = stoi(tempNum, 0, 16);
        openSequence.append(1, tempChar);
    }
    return true;
}


bool regexFind(string raw,regex payload,vector<pair<size_t,size_t>> &targets)
{
    string sequenceStr, targetPosition, targetLength;
    size_t targetPositionLL=0,targetLengthLL=0;
    auto sequenceBegin = sregex_iterator(raw.begin(), raw.end(), payload);
    auto sequenceEnd = sregex_iterator();
    for (auto i = sequenceBegin; i != sequenceEnd; i++)
    {
        if ((*i).size() == 3)
        {
            sequenceStr = (*i)[0].str();
            targetPosition = (*i)[1].str();
            targetLength = (*i)[2].str();
        }
        targetPositionLL = stoi(targetPosition,0,16);
        targetLengthLL = (targetLength.length()+1)/3;
        targets.push_back(pair<size_t,size_t>(targetPositionLL,targetLengthLL));
    }
    return true;
}

// using regex to match "equal"
// pair<size_t,size_t>the first size_t is the position of the target in ffs file
// the second size_t is the length of the target if not match, will not chanrge a thing
bool modifyFFSFile(string &rawffs, vector<pair<size_t,size_t>> &targets)
{

    regex searchPayLoad("(0x[0-9ABCDEFG]+)\\s+Variable\\s+0x[0-9ABCDEFG]+\\s+equals\\s+0x[0-9ABCDEFG]+\\s+\\{([\\w\\s]+)\\}", regex_constants::ECMAScript | regex_constants::icase);
    regex searchPayLoad2("(0x[0-9ABCDEF]+)\\s+Variable\\s+0x[0-9ABCDEF]+\\s+equals\\s+value\\sin\\slist\\s\\(.+\\)\\s+\\{([\\w\\s]+)\\}", regex_constants::ECMAScript | regex_constants::icase);
    regexFind(rawffs,searchPayLoad,targets);
    //regexFind(rawffs,searchPayLoad2,targets);
    cout<<"Find "<<targets.size()<<" Matches";
    return true;
}
