#include "include/wordladder.h"
#include "include/header.h"

typedef set<string>::iterator auto1;

WordLadder::WordLadder()
{
    //ctor
}

WordLadder::~WordLadder()
{
    //dtor
}

int  WordLadder::ladderLength(string start, string end, set<string> &dict)
{
    dp.clear();
    dict.insert(end);
    cout<<"-----------"<<endl;
    for(auto1 it = dict.begin(); it != dict.end(); ++it)
    {
        dp[*it] = 0;
    }
    bfs(start, dict);
    return dp[end];
}

void  WordLadder::bfs(string start, set<string> &dict)
{
     queue<string> st;
     for(auto1 it = dict.begin(); it != dict.end(); ++it)
     {
         cout<<"wordLadder"<<endl;
         if(canSwitch(start, *it))
         {
                dp[*it] = 1;
                st.push(*it);
                cout<<*it<<":"<<dp[*it]<<endl;
         }
     }
     while(!st.empty())
     {
         string s = st.front();
         st.pop();
         for(auto1 it = dict.begin(); it != dict.end(); ++it)
         {
             if(dp[*it] == 0 && canSwitch(s, *it))
             {
                 dp[*it] = dp[s] + 1;
                 st.push(*it);
                 cout<<*it<<":"<<dp[*it]<<endl;
             }
         }
     }
}

bool WordLadder::canSwitch(string src, string target)
    {
        int slen = src.length();
        int tlen = target.length();
        int res = 0;
        if(slen != tlen)
        {
            return false;
        }
        for(int i = 0; i < slen; ++i)
        {
            if(src[i] != target[i])
            {
                ++res;
                if(res > 1)
                    break;
            }
        }
        return res == 1;
    }

void buildAdjacent(string start, set<string> &dict, map<string, vector<string> > &link)
{
    size_t len = start.length();
    string temp(start);
    for(size_t i = 0; i < len; ++i)
    {
        for(char c = 'a'; c <= 'z'; ++c)
        {
            if(c != start[i])
            {
                temp[i] = c;
                if(dict.find(temp) != dict.end())
                {
                    link[start].push_back(temp);
                }
            }
        }
        temp[i] = start[i];
    }
}

void buildPath(string start, string end, map<string, vector<string> > &link, vector<vector<string> > &path, vector<string> pre)
{
    pre.push_back(start);
    if(start == end)
    {
        printVector(pre);
        path.push_back(pre);
        return;
    }
    for(vector<string>::iterator iter = link[start].begin(); iter != link[start].end(); ++iter)
    {
        if(find(pre.begin(), pre.end(), *iter) == pre.end())
        {
            buildPath(*iter, end, link, path, pre);
        }
    }
}

vector<vector<string> > WordLadder::ladderFind(string start, string end, set<string> &dict) {
        vector<vector<string> > res;
        vector<vector<string> > path;
        dict.insert(start);
        dict.insert(end);
        int Length = dict.size();
        map<string, vector<string> > link_table;
        map<string, bool> flag;
        for(set<string>::iterator iter = dict.begin(); iter != dict.end(); ++iter)
        {
            buildAdjacent(*iter, dict, link_table);
            flag[*iter] = false;
        }
        queue<pair<string, vector<string> > > q;
        q.push(make_pair(start, vector<string>(1, start)));
        flag[start] = true;
        int preLen = 1;
        int nextLen = 0;
        int count = 0;
        vector<string> visited;
        int i = 0;
        while(!q.empty())
        {
            //cout<<count<<'\t'<<preLen<<'\t'<<nextLen<<endl;
            //cin.get();
            string front = q.front().first;
            vector<string> pre = q.front().second;
            q.pop();
            if(pre.size() >= Length)
                break;
            if(count == preLen)
            {
                preLen = nextLen;
                nextLen = 0;
                count = 0;
                //cout<<"*************************************"<< i++ <<'\t'<<preLen<<endl;
                for(vector<string>::iterator it = visited.begin(); it != visited.end(); ++it)
                 {
                    flag[*it] = true;
                   // cout<<*it<<'\t';
                 }
                 //cout<<endl<<"*************************************"<< i++ <<'\t'<<preLen<<endl;
                 visited.clear();
            }
            //cout<<count<<'\t'<<preLen<<'\t'<<nextLen<<endl;
          //  printVector(pre);
            ++count;
            for(vector<string>::iterator iter = link_table[front].begin(); iter != link_table[front].end(); ++iter)
            {
                if(flag[*iter])
                    continue;
                else
                {
                    ++nextLen;
                    vector<string> t(pre);
                    t.push_back(*iter);
                    visited.push_back(*iter);
                   // q.push(make_pair(*iter, t));

                    if(*iter == end)
                    {
                        Length = t.size();
                        path.push_back(t);
                    }
                    else
                    {
                        q.push(make_pair(*iter, t));
                     //   cout<<"add the pre ------------------------------"<<endl;
                      //  printVector(t);
                      //  cout<<"add the pre ------------------------------"<<endl;
                    }
                }
            }

        }

        return path;
    }

vector<vector<string> > WordLadder::ladderFind2(string start, string end, set<string> &dict)
{
    vector<vector<string> > res;
    vector<vector<string> > path;
    dict.insert(start);
    dict.insert(end);
    int Length = dict.size();
    map<string, vector<string> > link_table;
    map<string, bool> flag;
    for(set<string>::iterator iter = dict.begin(); iter != dict.end(); ++iter)
    {
        buildAdjacent(*iter, dict, link_table);
        flag[*iter] = false;
    }
    queue<vector<pair<string, vector<string> > > > q;
    q.push(vector<pair<string, vector<string> > >(1, make_pair(start, vector<string>(1, start))) );
    flag[start] = true;
    while(!q.empty())
    {
        //cout<<"========================================================================="<<endl;
        vector<pair<string, vector<string> > > qvector = q.front();
        vector<string> visited;
        vector<pair<string, vector<string> > > nextPath;
        q.pop();
        for(vector<pair<string, vector<string> > >::iterator iq = qvector.begin(); iq != qvector.end(); ++iq)
        {
            string front = (*iq).first;
            vector<string> pre = (*iq).second;
            if(pre.size() >= Length)
                return path;
            for(vector<string>::iterator iter = link_table[front].begin(); iter != link_table[front].end(); ++iter)
            {
                if(flag[*iter])
                    continue;
                else
                {
                    vector<string> t(pre);
                    t.push_back(*iter);
                    visited.push_back(*iter);
                    //nextPath.push_back(make_pair(*iter, t));
                   // cout<<"----------------path"<<endl;
                    //printVector(t);

                    if(*iter == end)
                    {
                        Length = t.size();
                        path.push_back(t);
                    }
                    else
                    {
                        nextPath.push_back(make_pair(*iter, t));
                    }
                }
            }
        }
        if(!nextPath.empty())
            q.push(nextPath);
        for(vector<string>::iterator it = visited.begin(); it != visited.end(); ++it)
        {
            flag[*it] = true;
            //cout<<*it<<" visited"<<'\t';
        }
        //cout<<endl;
    }

    return path;
}



void test_word_ladder()
{
    WordLadder dl;
    string start =  "nape" ;  //"qa";
    string end =  "mild" ;//"sq";
   // string dv[] = {"si","go","se","cm","so","ph","mt","db","mb","sb","kr","ln","tm","le","av","sm","ar","ci","ca","br","ti","ba","to","ra","fa","yo","ow","sn","ya","cr","po","fe","ho","ma","re","or","rn","au","ur","rh","sr","tc","lt","lo","as","fr","nb","yb","if","pb","ge","th","pm","rb","sh","co","ga","li","ha","hz","no","bi","di","hi","qa","pi","os","uh","wm","an","me","mo","na","la","st","er","sc","ne","mn","mi","am","ex","pt","io","be","fm","ta","tb","ni","mr","pa","he","lr","sq","ye"};
    string dv[] = {"dose","ends","dine","jars","prow","soap","guns","hops","cray","hove","ella","hour","lens","jive","wiry","earl","mara","part","flue","putt","rory","bull","york","ruts","lily","vamp","bask","peer","boat","dens","lyre","jets","wide","rile","boos","down","path","onyx","mows","toke","soto","dork","nape","mans","loin","jots","male","sits","minn","sale","pets","hugo","woke","suds","rugs","vole","warp","mite","pews","lips","pals","nigh","sulk","vice","clod","iowa","gibe","shad","carl","huns","coot","sera","mils","rose","orly","ford","void","time","eloy","risk","veep","reps","dolt","hens","tray","melt","rung","rich","saga","lust","yews","rode","many","cods","rape","last","tile","nosy","take","nope","toni","bank","jock","jody","diss","nips","bake","lima","wore","kins","cult","hart","wuss","tale","sing","lake","bogy","wigs","kari","magi","bass","pent","tost","fops","bags","duns","will","tart","drug","gale","mold","disk","spay","hows","naps","puss","gina","kara","zorn","boll","cams","boas","rave","sets","lego","hays","judy","chap","live","bahs","ohio","nibs","cuts","pups","data","kate","rump","hews","mary","stow","fang","bolt","rues","mesh","mice","rise","rant","dune","jell","laws","jove","bode","sung","nils","vila","mode","hued","cell","fies","swat","wags","nate","wist","honk","goth","told","oise","wail","tels","sore","hunk","mate","luke","tore","bond","bast","vows","ripe","fond","benz","firs","zeds","wary","baas","wins","pair","tags","cost","woes","buns","lend","bops","code","eddy","siva","oops","toed","bale","hutu","jolt","rife","darn","tape","bold","cope","cake","wisp","vats","wave","hems","bill","cord","pert","type","kroc","ucla","albs","yoko","silt","pock","drub","puny","fads","mull","pray","mole","talc","east","slay","jamb","mill","dung","jack","lynx","nome","leos","lade","sana","tike","cali","toge","pled","mile","mass","leon","sloe","lube","kans","cory","burs","race","toss","mild","tops","maze","city","sadr","bays","poet","volt","laze","gold","zuni","shea","gags","fist","ping","pope","cora","yaks","cosy","foci","plan","colo","hume","yowl","craw","pied","toga","lobs","love","lode","duds","bled","juts","gabs","fink","rock","pant","wipe","pele","suez","nina","ring","okra","warm","lyle","gape","bead","lead","jane","oink","ware","zibo","inns","mope","hang","made","fobs","gamy","fort","peak","gill","dino","dina","tier"};
   // string dv[] = {"hot","dot","dog","lot","log"};
    set<string> dict(&dv[0], &dv[sizeof(dv)/sizeof(string)]);

/*
    for(auto1 it = dict.begin(); it != dict.end(); ++it)
        cout<<*it<<endl;
    cout<<dl.ladderLength(start, end, dict)<<endl;
*/
    vector<vector<string> > vvs = dl.ladderFind(start, end, dict);
   // cout<<"------------------------"<<endl;
   // printTVector(vvs);
}
