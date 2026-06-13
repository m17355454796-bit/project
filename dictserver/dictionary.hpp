#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include<fstream>
using namespace std;
string defaultDictionary="./dict_words.txt";
string gsep=" ";
class dictionary{
private:
void LoadConf()
{
    ifstream in(_pathname);
    if(!in.is_open())
    {
        cerr<<"打开字典文件失败"<<endl;
        exit(1);
    }
    string line;
    while(getline(in,line))
   {
        auto pos=line.find(gsep);
        if(pos==string::npos)
        {
            cout<<"加载单词失败"<<line;
            continue;
        }
        string key=line.substr(0,pos);
        string value=line.substr(pos+gsep.size());
        _dicthash.insert({key,value});
   } 
    in.close();
}
public:
dictionary(string pathname=defaultDictionary):
    _pathname(pathname)
{
    LoadConf();
}
string translation(string& word){
   auto iter=_dicthash.find(word);
   if(iter==_dicthash.end())
   {
    cout<<"find fail"<<endl;
    return "未找到该单词";
   }
   return iter->second;
}
~dictionary(){}
private:
 string _pathname;
 unordered_map<string, string> _dicthash;
};