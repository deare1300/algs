#ifndef WORDBREAK_H
#define WORDBREAK_H

#include <vector>
#include <string>
#include <set>
#include <set>
using namespace std;
/********************************************************************
Word Break II Total Accepted: 7567 Total Submissions: 49496 My Submissions
Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].
A solution is ["cats and dog", "cat sand dog"].
*******************************************************************************************************/
void test_word_break();
class WordBreak
{
    public:
        WordBreak();
        virtual ~WordBreak();
        vector<string> wordBreak(string s, set<string> &dict);
    protected:
    private:
        vector<vector<bool> > dp;
        vector<string> ret;
};

#endif // WORDBREAK_H
