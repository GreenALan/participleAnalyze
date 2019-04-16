
#include <stdio.h>
#include <stdlib.h>


#include <vector>
#include <string>
#include <map>
#include <stack>
using namespace std;

// 符号表
enum eType
{
    Symbol
};
map<string, eType> g_mapSymbol;

enum eCharFlag
{
    noFlag,
    explain
};

eCharFlag g_charFlag = noFlag;

vector<string> common_word{
    "if",
    "for",
    "while"
};

void participle(const string &fname, const string &writename, vector<string>& vecWords){
    // 获取输入
    int i=0,j=0,k=0;
    char oneChar;
    // 打开文件
    FILE *fp;
    if ((fp= fopen(fname.c_str(),"r"))== NULL)
    {
        printf("Cannot open infile.\n");
        exit(0);
    }
    
    //int 0i;
    
    // 分析文件
    oneChar=fgetc(fp);
    char oneWord[256]={0};
    int nBuf = 0;
    while (oneChar!=EOF)
    {
        if(nBuf == 0)
        {
            if(oneChar == ' ' || oneChar == '\n' || oneChar == '\t')
            {
                
            }
            else if(oneChar == '(' || oneChar == '{')
            {
                oneWord[nBuf++]    = oneChar;
                string strWord = oneWord;
                vecWords.push_back(strWord);
                nBuf = 0;
                g_charFlag = noFlag;
                memset(oneWord, 0, 256);
                //continue;
            }
            else if(oneChar == ')' || oneChar == '}')
            {
                oneWord[nBuf++]    = oneChar;
                string strWord = oneWord;
                vecWords.push_back(strWord);
                nBuf = 0;
                g_charFlag = noFlag;
                memset(oneWord, 0, 256);
                //continue;
            }
            else if(oneChar == ','){
                vecWords.push_back(",");
                nBuf =0;
                g_charFlag = noFlag;
                memset(oneWord, 0, 256);
            }
            else if(oneChar == ','){
                vecWords.push_back(";");
                nBuf =0;
                g_charFlag = noFlag;
                memset(oneWord, 0, 256);
            }
            else if(oneChar >= '0' && oneChar <= '9')
            {
                /*printf("error, 不可以数字打头");
                 return -1;*/
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar >= 'a' && oneChar <= 'z')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar >= 'A' && oneChar <= 'Z')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '#') //如果是#inclue， #define 的这种。一行为一个字
            {
                vecWords.push_back("#");
                oneChar=fgetc(fp);
                char secondWord[512];

                memset(oneWord, 0, 256);
                nBuf =0;
                while(oneChar != EOF && oneChar != '\n')
                {
                    oneWord[nBuf++]    = oneChar;
                    oneChar=fgetc(fp);
                }
                vecWords.push_back(oneWord);
                nBuf =0;
                memset(oneWord, 0, 256);
            }
            else if(oneChar == ':')
            {
                // 界限符号
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '/')
            {
                // 注释的开始，找第二根横线
                // 或者是路径描述
                //如果是注释，直接过滤掉,
                oneWord[nBuf++]    = oneChar;
                oneChar = fgetc(fp);
                if(oneChar == '/'){
                    oneChar = fgetc(fp);
                    while(oneChar != EOF && oneChar != '\n'){
                        oneChar = fgetc(fp);
                    }
                    nBuf =0;
                    memset(oneWord, 0, 256);
                    continue;
                }
                else if(oneChar == '*'){
                    oneChar = fgetc(fp);
                    char twoChar = fgetc(fp);
                    while(oneChar != '*' && twoChar != '/'){
                        oneChar = twoChar;
                        twoChar = fgetc(fp);
                    }
                    nBuf = 0;
                    memset(oneWord, 0, 256);
                    continue;
                }
                
                oneWord[nBuf++]    = oneChar;
                
                g_charFlag = explain;
            }
            else if(oneChar == '(')
            {
                // 函数的开始，找第二个括号
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == ')')
            {
                // 函数的结束
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '{')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '}')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == ';')
            {
                // 语句结束符
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '~')
            {
                // 析构函数符
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '\"')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '=')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '_')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '?')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '%')
            {
                oneWord[nBuf++] = oneChar;
            }
            else
            {
                //printf("未处理情况：%c", oneChar);
                oneWord[nBuf++]    = oneChar;
            }
        }
        else
        {
            if(oneChar == ' ' || oneChar == '\t' || oneChar == '\n')
            {
                if(g_charFlag != explain)
                {
                    string strWord = oneWord;
                    vecWords.push_back(strWord);
                    nBuf = 0;
                    g_charFlag = noFlag;
                    memset(oneWord, 0, 256);
                }
                else if(g_charFlag == explain && oneChar == '\n')
                {
//                    // 如果是注释状态,则碰到回车才截断
//                    string strWord = oneWord;
//                    vecWords.push_back(strWord);
//                    nBuf = 0;
//                    g_charFlag = noFlag;
//                    memset(oneWord, 0, 256);
                }
            }
            else if(oneChar == '(' || oneChar == '{')
            {
                //oneWord[nBuf++]    = oneChar;
                string strWord = oneWord;
                vecWords.push_back(strWord);
                nBuf = 0;
                g_charFlag = noFlag;
                memset(oneWord, 0, 256);
                continue;
            }
            else if(oneChar == ')' || oneChar == '}')
            {
                //oneWord[nBuf++]    = oneChar;
                string strWord = oneWord;
                vecWords.push_back(strWord);
                nBuf = 0;
                g_charFlag = noFlag;
                memset(oneWord, 0, 256);
                continue;
            }
            else if(oneChar == ',' || oneChar == ';'){
                string strWord = oneWord;
                vecWords.push_back(strWord);
                nBuf = 0;
                g_charFlag = noFlag;
                memset(oneWord, 0, 256);
                continue;
            }
            //else if(oneChar == '\n')
            //{
            //    // 行末, 处理一些情况, 例如注释等
            //}
            else if(oneChar >= '0' && oneChar <= '9')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar >= 'a' && oneChar <= 'z')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar >= 'A' && oneChar <= 'Z')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '_')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == ':')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '(')
            {
                // 函数的开始，找第二个括号
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == ')')
            {
                // 函数的结束
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '{')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '}')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == ';')
            {
                // 语句结束符
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '~')
            {
                // 析构函数符
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '\"')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '*')
            {
                // 定义指针
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '.')
            {
                // .h
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '=')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '/')
            {
                oneWord[nBuf++]    = oneChar;
                oneChar = fgetc(fp);
                if(oneChar == '/'){
                    oneChar = fgetc(fp);
                    while(oneChar != EOF && oneChar != '\n'){
                        oneChar = fgetc(fp);
                    }
                    nBuf =0;
                    memset(oneWord, 0, 256);
                    continue;
                }
                else if(oneChar == '*'){
                    oneChar = fgetc(fp);
                    char twoChar = fgetc(fp);
                    while(oneChar != '*' && twoChar != '/'){
                        oneChar = twoChar;
                        twoChar = fgetc(fp);
                    }
                    nBuf = 0;
                    memset(oneWord, 0, 256);
                    continue;
                }
                
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == ',')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '?')
            {
                oneWord[nBuf++]    = oneChar;
            }
            else if(oneChar == '%')
            {
                oneWord[nBuf++] = oneChar;
            }
            else
            {
                oneWord[nBuf++]    = oneChar;
                //printf("未处理情况：%c", oneChar);
                
                //string strWord = "未处理情况：%s";
                //printf("error, 未处理情况.");
                //return -1;
            }
        }
        oneChar=fgetc(fp);
    }
    fclose(fp);
    // 写入文件
    FILE *fpIn;
    if ((fpIn= fopen(writename.c_str(),"w+"))== NULL)
    {
        printf("Cannot open infile.\n");
        exit(0);
    }
    
    for(int i = 0; i < vecWords.size(); i++)
    {
        char szBuf[300];
        memset(szBuf, 0, 300);
        sprintf(szBuf, "%d. %s\n", i, vecWords[i].c_str());
        fwrite(szBuf, strlen(szBuf), 1, fpIn);
        //printf("%d. %s\n", i, vecWords[i].c_str());
    }
    fclose(fpIn);
}

typedef struct
{
    string returnName=""; // 返回值
    string funcName = ""; //函数名
    string paramList = ""; //参数类型
    int paramNum = 0; //参数数量
}stFunc;

typedef struct
{
    string name=""; //类名
    vector<stFunc> func; //函数名
    vector<string> variable; //变量
    
}stClass;


void analyze(vector<string> &realWords, vector<string> &vecPath,
             vector<stClass> &vecClass,
             vector<stFunc> &vecFunc,
             vector<string> &notFunc){
    for(int i=0; i < realWords.size(); i++){
        if(realWords[i] == "%include"){
            vecPath.push_back(realWords[i+1]);
        }
        if(realWords[i] == "struct" || realWords[i] == "class"){
            stClass tempClass;
            tempClass.name = realWords[i+1];
            continue;
            while(realWords[i] != "{"){
                i++;
            }
            int stackNum = 1; //模拟栈，初始一个 {, 直到遇到对应的} 类解析结束
            i++;
            while(stackNum != 0){
                if((realWords[i] == "(" && realWords[i+1] == ")")){
                    stFunc f;
                    if(i > 2){ //找到返回值
                        if(find(notFunc.begin(), notFunc.end(), realWords[i-2]) != notFunc.end()){
                            f.returnName = ""; //没有返回值
                        }
                        else{
                            f.returnName = realWords[i-2];
                        }
                    }
                    if(i > 0)
                    {
                        f.funcName = realWords[i-1];
                        f.paramList = "( )";
                        f.paramNum = 0;
                    }
                    tempClass.func.push_back(f);
                    i = i+1; // 处于）
                    if(realWords[i+1] == "{"){ // 函数内容过滤掉
                        int staNum1 = 1; //第二层栈
                        i = i+1;
                        while (staNum1 != 0) {
                            i++;
                            if(realWords[i] == "}"){
                                staNum1--;
                            }
                            else if(realWords[i] == "{"){
                                staNum1++;
                            }
                            
                        }
                    }
                }
                else if(realWords[i] == "("){
                    if(i > 0){
                        if(g_mapSymbol.find(realWords[i]) != g_mapSymbol.end()){//不是函数
                            continue;
                        }
                        else{
                            stFunc f;
                            if(i > 2){ //找到返回值
                                if(find(notFunc.begin(), notFunc.end(), realWords[i-2]) != notFunc.end()){
                                    f.returnName = ""; //没有返回值
                                }
                                else{
                                    f.returnName = realWords[i-2];
                                }
                            }
                            f.funcName = realWords[i-1];
                            int paramNum = 1;
                            string strParamList = "(";
                            while(realWords[i++] != ")"){
                                if(realWords[i] == ","){
                                    paramNum += 1;
                                    f.paramList += ",";
                                    continue;
                                }
                                strParamList += " ";
                                strParamList += realWords[i];
                            }
                            strParamList += realWords[i]; //加一个)
                            f.paramList = strParamList;
                            f.paramNum = paramNum;
                            tempClass.func.push_back(f);
                            i = i+1; // 处于）
                            if(realWords[i+1] == "{"){ // 函数内容过滤掉
                                int staNum1 = 1; //第二层栈
                                i = i+1;
                                while (staNum1 != 0) {
                                    i++;
                                    if(realWords[i] == "}"){
                                        staNum1--;
                                    }
                                    else if(realWords[i] == "{"){
                                        staNum1++;
                                    }
                                    
                                }
                            }
                        }
                    }
                }
                else if(realWords[i] == "{"){
                    stackNum++;
                }
                else if(realWords[i] == "}"){
                    stackNum--;
                }
                
                i++;
                
            }
        }
        else if( (realWords[i] == "(" && realWords[i+1] == ")")){
            stFunc f;
            if(i > 2){ //找到返回值
                if(find(notFunc.begin(), notFunc.end(), realWords[i-2]) != notFunc.end()){
                    f.returnName = ""; //没有返回值
                }
                else{
                    f.returnName = realWords[i-2];
                }
            }
            if(i > 0)
            {
                
                f.funcName = realWords[i-1];
                f.paramList = "( )";
                f.paramNum = 0;
                vecFunc.push_back(f);
                i = i+1; // 处于）
                if(realWords[i+1] == "{"){ // 函数内容过滤掉
                    int staNum1 = 1; //第二层栈
                    i = i+1;
                    while (staNum1 != 0) {
                        i++;
                        if(realWords[i] == "}"){
                            staNum1--;
                        }
                        else if(realWords[i] == "{"){
                            staNum1++;
                        }
                        
                    }
                }
            }
        }
        else if(realWords[i] == "("){
            if(i > 0){
                if(g_mapSymbol.find(realWords[i]) != g_mapSymbol.end()){//不是函数
                    continue;
                }
                else if(realWords[i-1] == "%template" or realWords[i-1] == "CLASS_NAME_DEFINE_OVERRIDE"){
                    continue;
                }
                else if(realWords[i-2] == "="){
                    continue;
                }
                else{
                    stFunc f;
                    if(i > 2){ //找到返回值
                        if(find(notFunc.begin(), notFunc.end(), realWords[i-2]) != notFunc.end()){
                            f.returnName = ""; //没有返回值
                        }
                        else{
                            f.returnName = realWords[i-2];
                        }
                    }
                    f.funcName = realWords[i-1];
                    int paramNum = 1;
                    string strParamList = "(";
                    
                    while(realWords[i] != ")"){
                        i++;
                        
                        if(realWords[i] == ","){
                            paramNum += 1;
                            strParamList += ",";
                            continue;
                        }
                        strParamList += " ";
                        strParamList += realWords[i];
                    }
                    //strParamList += realWords[i]; //加一个)
                    f.paramList = strParamList;
                    f.paramNum = paramNum;
                    vecFunc.push_back(f);
                    if(realWords[i+1] == "{"){ // 函数内容过滤掉
                        int staNum1 = 1; //第二层栈
                        i = i+1;
                        while (staNum1 != 0) {
                            i++;
                            if(realWords[i] == "}"){
                                staNum1--;
                            }
                            else if(realWords[i] == "{"){
                                staNum1++;
                            }
                            
                        }
                    }
                    
                }
            }
        }
        
    }
}

int main(int argc, char* argv[])
{
    // 输入常用标识符
    for(int i=0; i < common_word.size(); i++){
        g_mapSymbol[common_word[i]] = Symbol;
    }
    
    //解析script_modularization.i 文件
    vector<string> vecWords; //解析的单词
    string WordsPath = "/Users/lvshaohui1234/Desktop/CodeLove/virtual/virtual/resource/words.txt"; //words 写入的路径
    string modularizationPath = "/Users/lvshaohui1234/lvByteDance/effect_sdk/effect_sdk/dev/src/luasystem/script_modularization.i"; //解析的文件
    participle(modularizationPath, WordsPath, vecWords);
    
    //得到过滤的单词
    int splitNum = 0;
    for(int i=0; i < vecWords.size(); i++){
        if(vecWords[i] == "%" && vecWords[i+1] == "}"){
            splitNum = i+2;
            break;
        }
    }
    vector<string> realWords;
    for(int i=splitNum; i < vecWords.size(); i++){
        realWords.emplace_back(vecWords[i]);
    }
    
    //得到对应的分类
    vector<string> vecPath; //得到其他路径
    vector<stClass> vecClass; //得到类和结构体
    vector<stFunc> vecFunc; //得到对应的函数
    vector<string> notFunc={";","{","virtual","public:","private:", "*/"};
    
    analyze(realWords, vecPath, vecClass, vecFunc, notFunc);
    
    vector<string> deletePath = {"../../../../render_core/render_core/dev/inc/framework/base/Framework.h"};
    
    
     FILE *fpIn;
    
    // Grammar 写入文件
    if ((fpIn= fopen("/Users/lvshaohui1234/Desktop/CodeLove/virtual/virtual/resource/grammer.txt","w+"))== NULL)
    {
        printf("Cannot open infile.\n");
        exit(0);
    }
    
    for(int i = 0; i < vecPath.size(); i++)
    {
        char szBuf[500];
        memset(szBuf, 0, 500);
        sprintf(szBuf, "%d. %s \n", i, vecPath[i].c_str());
        printf("Header: %s\n",vecPath[i].c_str());
        fwrite(szBuf, strlen(szBuf), 1, fpIn);
    }
    
    
    
    fwrite("\n\n\n", 2, 1, fpIn);
    
   //类的函数名
    
    int num = 0;
    for(int i=0; i < vecClass.size(); i++){
        char szBuf[500];
        memset(szBuf, 0, 500);
        for(int j =0 ; j < vecClass[i].func.size(); j++){
            sprintf(szBuf, "%d. %s %s %s %d \n", num+j, vecClass[i].func[j].returnName.c_str(),vecClass[i].func[j].funcName.c_str(),vecClass[i].func[j].paramList.c_str(), vecClass[i].func[j].paramNum);
        }
        num += vecClass.size();
    }
    fwrite("\n\n\n", 2, 1, fpIn);
    // 函数
    for(int i = 0; i < vecFunc.size(); i++)
    {
        char szBuf[500];
        memset(szBuf, 0, 500);
        sprintf(szBuf, "%d. %s %s %s %d \n", i,vecFunc[i].returnName.c_str(), vecFunc[i].funcName.c_str(), vecFunc[i].paramList.c_str(),vecFunc[i].paramNum);
        fwrite(szBuf, strlen(szBuf), 1, fpIn);
        //printf("%d. %s\n", i, vecRealize[i].c_str());
    }
    
    fclose(fpIn);
    
    for(int i=0; i < vecPath.size(); i++){
        vecPath[i] = vecPath[i].substr(1,vecPath[i].length() - 2);
    }
    
    for(int i=0; i  < deletePath.size(); i++){
        for(int j=0; j < vecPath.size(); j++){
            if(vecPath[j] == deletePath[i]){
                vecPath[j] = "";
            }
        }
    }
    
    if ((fpIn= fopen("/Users/lvshaohui1234/Desktop/CodeLove/virtual/virtual/resource/grammer1.txt","w+"))== NULL)
    {
        printf("Cannot open infile.\n");
        exit(0);
    }
    
    //解析其他文件
    vector<vector<string>> allString(vecPath.size());
    vector<vector<stFunc>> allFunc(vecPath.size());
    vector<vector<string>> allPath(vecPath.size());
    vector<vector<stClass>> allClass(vecPath.size());
    string str = "/Users/lvshaohui1234/Desktop/CodeLove/virtual/virtual/resource/words1.txt";
    for(int i=0; i < vecPath.size(); i++){
        if(vecPath[i] == ""){
            continue;
        }
        participle(vecPath[i], str, allString[i]);
        
        //得到过滤的单词
        int splitNum = 0;
        for(int j=0; j < allString[i].size(); j++){
            if(allString[i][j] == "%" && allString[i][j+1] == "}"){
                splitNum = j+2;
                break;
            }
        }
        vector<string> realWords;
        for(int j=splitNum; j < allString[i].size(); j++){
            realWords.emplace_back(allString[i][j]);
        }
        
        analyze(realWords, allPath[i], allClass[i], allFunc[i], notFunc);
        
//        fwrite("Header\n", 7, 1, fpIn);
//        for(int i = 0; i < allPath[i].size(); i++)
//        {
//            char szBuf[500];
//            memset(szBuf, 0, 500);
//            sprintf(szBuf, "%d. %s \n", i, vecPath[i].c_str());
//            printf("Header: %s\n",vecPath[i].c_str());
//            fwrite(szBuf, strlen(szBuf), 1, fpIn);
//        }
//
//        fwrite("\n\n\n", 2, 1, fpIn);
        
        //类的函数名
        
//        int num = 0;
//        for(int i=0; i < allClass[i].size(); i++){
//            char szBuf[500];
//            memset(szBuf, 0, 500);
//            for(int j =0 ; j < vecClass[i].func.size(); j++){
//                sprintf(szBuf, "%d. %s %s %s %d \n", num+j, vecClass[i].func[j].returnName.c_str(),vecClass[i].func[j].funcName.c_str(),vecClass[i].func[j].paramList.c_str(), vecClass[i].func[j].paramNum);
//            }
//            num += vecClass.size();
//        }
//        fwrite("\n\n\n", 2, 1, fpIn);
        // 函数
        string funString = "function" + to_string(i) + "\n";
        fwrite(funString.c_str(), sizeof(funString), 1, fpIn);
        for(int j = 0; j < allFunc[i].size(); j++)
        {
            char szBuf[500];
            memset(szBuf, 0, 500);
            sprintf(szBuf, "%d. %s %s %s %d \n", j,allFunc[i][j].returnName.c_str(), allFunc[i][j].funcName.c_str(), allFunc[i][j].paramList.c_str(),allFunc[i][j].paramNum);
            fwrite(szBuf, strlen(szBuf), 1, fpIn);
            //printf("%d. %s\n", i, vecRealize[i].c_str());
        }
        fwrite("\n\n\n", 2, 1, fpIn);
    }
    
    
    fclose(fpIn);
    

    return 0;
}

