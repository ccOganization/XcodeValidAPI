//
//  ValidAPIUtil.hpp
//  ClangValidAPIPlugin
//
//  Created by KyleWong on 14/10/2016.
//
//

#ifndef ValidAPIUtil_hpp
#define ValidAPIUtil_hpp
#include <string>
#include<algorithm>
#include <functional>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "json.hpp"

#define kAppMainEntryClass  "UIApplication"
#define kAppMainEntrySelector  "main"

using namespace std;
using namespace nlohmann;

static vector<string> split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

static inline void remove_blank(string &str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    str.erase(remove(str.begin(), str.end(), '\t'), str.end());
}

static inline bool has_suffix(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
    str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

static inline string &ltrim(std::string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(),
                               not1(ptr_fun<int, int>(isspace))));
    return s;
}

// trim from end
static inline string &rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(),
                    not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline string &trim(string &s) {
    return ltrim(rtrim(s));
}

static inline string absolutePathFromRelative(string relativePath){
    vector<string> pathComs = split(relativePath,'/');
    vector<string> absoPathVec;
    ostringstream oss;
    for(vector<string>::iterator it = pathComs.begin();it!=pathComs.end();it++){
        string path = *it;
        if(!path.compare("") || !path.compare("."))
            continue;
        if(!path.compare("..")){
            absoPathVec.pop_back();
        }
        else{
            absoPathVec.push_back(string("/")+path);
        }
    }
    copy(absoPathVec.begin(), absoPathVec.end(), ostream_iterator<string>(oss));
    return oss.str();
}

class ValidAPIUtil{
public:
    static void setFilename(string fname,bool forceSet);
    static void appendObjcClsMethodImpl(bool isInstanceMethod,string cls,string selector,string filename,unsigned rangeFrom,unsigned rangeTo,string sourcecode);
    static void appendObjcMethodImplCall(bool isInstanceMethod,string cls,string selector,bool calleeIsInstanceMethod,string calleeCls,string calleeSel);
    static void appendObjcCls(string cls,string supCls,vector<string> protoVec,bool inInSrcDi);
    static void appendObjcClsInterf(string cls,bool isInstanceInterf,string selector);
    static void appendObjcClsProperty(string cls,bool isInstanceProperty,string getter,string setter,string property);
    static void appendObjcProto(string proto,vector<string> refProto,bool isInSrcDir);
    static void appendObjcProtoInterf(string proto,bool isInstanceInterf,string selector);
    static void appendObjcProtoProperty(string proto,bool isInstanceProperty,string getter,string setter,string property);
    static void appendObjcAddNotificationCall(bool isInstanceMethod,string cls,string selector,bool calleeIsInstanceMethod,string calleeCls,string calleeSel,string notif);
    static void appendObjcPostNotificationCall(bool isInstanceMethod, string cls, string selector, string notif);
    static void appendObjcProtoInterfCall(bool isInstanceMethod,string cls,string selector,string proto,string protoSel);
    static void appendFunction(string function);
    static void appendEnum(string em);
    static void appendVar(string var);
    static bool writeJsonToFile(json j,string filename);
    static void synchronize();
};
#endif /* ValidAPIUtil_hpp */
