#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <execinfo.h>
#include <iostream>
#include <cxxabi.h>

#define BT_BUF_SIZE 100
void test1(void)
{
    int j, nptrs;
    void *buffer[BT_BUF_SIZE];
    char **strings;

    nptrs = backtrace(buffer, BT_BUF_SIZE);
    printf("backtrace() returned %d addresses\n", nptrs);

    /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
would produce similar output to the following: */

    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
        perror("backtrace_symbols");
        exit(EXIT_FAILURE);
    }

    for (j = 0; j < nptrs; j++)
        printf("%s\n", strings[j]);

    free(strings);
}
using namespace std;
#include <execinfo.h>
string get_last_sub_string(string str,char t)
{
    unsigned int pos;
    for(pos=0;pos<str.size();pos++){
        if(str[str.size()-pos-1]==t)
            break;
    }
    string dst= str.substr(str.size()-pos,pos);
    return dst;
}
string get_last_sub_string(string str,char t_start,char t_end)
{
    unsigned int pos;
    for(pos=0;pos<str.size();pos++){
        if(str[str.size()-pos-1]==t_start)
            break;
    }
    unsigned int pos_end;
    for(pos_end=0;pos_end<str.size();pos_end++){
        if(str[str.size()-pos_end-1]==t_end)
            break;
    }
    string dst= str.substr(str.size()-pos,pos-pos_end-1);
    return dst;
}


//#ifdef HAVE_CXA_DEMANGLE
#if 1
char* demangle(const char* name)
{
    char buf[1024];
    unsigned int size=1024;
    int status;
    char* res = abi::__cxa_demangle (name,
                                     buf,
                                     &size,
                                     &status);
    return res;
}
#else
const char* demangle(const char* name)
{
    return name;
}
#endif
#include <string.h>
using namespace std;
void print_backstrace(void)
{
    int j, nptrs;
    void *buffer[BT_BUF_SIZE];
    char **strings;

    nptrs = backtrace(buffer, BT_BUF_SIZE);
    printf("@@@@@@@@@@@@@backtrace start(%d functions) \n", nptrs);
    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
        perror("backtrace_symbols");
        exit(EXIT_FAILURE);
    }
    string str;
    char   *realname;
    for (j = 0; j < nptrs; j++)
    {
        str=string(strings[j]);
        string sub=get_last_sub_string(str,'(','+');
        realname=demangle(sub.data());
        if(realname)
            cout<<realname<<endl;
    }


    free(strings);
    cout<<"@@@@@@@@@@@@@backtrace end "<<endl;
}


void test11()
{
    print_backstrace();
}
void test2()
{
    test11();
}
void test3()
{
    test2();
}
void test4()
{
    test3();
}
class SSS{
public:
    SSS()
    {

    }
    void fun()
    {
        test4();

    }
};

int main()
{
  //  test4();
SSS sss;
sss.fun();
    //  test1();
    //    print_backstrace();
    //printf("11\n");
    return 0;
}
