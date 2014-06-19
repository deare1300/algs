#ifndef WORDLADDER_H
#define WORDLADDER_H

#include "include/header.h"
class WordLadder
{
    public:
        WordLadder();
        virtual ~WordLadder();
        int ladderLength(string start, string end, set<string> &dict);
        vector<vector<string> > ladderFind(string start, string end, set<string> &dict);
        vector<vector<string> > ladderFind2(string start, string end, set<string> &dict);
        void bfs(string start, set<string> &dict);
        bool canSwitch(string src, string target);
        map<string, int> dp;

    protected:
    private:
};
void test_word_ladder();
#endif // WORDLADDER_H
