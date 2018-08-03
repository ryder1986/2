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
const char* demangle(const char* name)
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
void print_backstrace(void)
{
    int j, nptrs;
    void *buffer[BT_BUF_SIZE];
    char **strings;

    nptrs = backtrace(buffer, BT_BUF_SIZE);
    printf("backtrace() functions: %d\n", nptrs);

    /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
would produce similar output to the following: */

    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
        perror("backtrace_symbols");
        exit(EXIT_FAILURE);
    }
    string str;
    const   char   *realname;
    for (j = 0; j < nptrs; j++)
    {

        str=string(strings[j]);
        cout<<endl;
        string sub=get_last_sub_string(str,'(',')');
        realname=demangle(str.data());
        if(realname)
        {
            string str(realname);
         cout<<str.size()<<endl;
        }
        //if(strlen(realname)>3)
          //  cout<<"realname:"<<realname<<endl;
    }
    //    int     status;
    // const   char   *realname;
    //    for (j = 0; j < nptrs; j++)
    //    {
    //        //   printf("%s\n", strings[j]);
    //        str=string(strings[j]);
    //    //    cout<<"\n";
    //      cout<<str;
    //        cout<<"\n";
    //        //cout<<get_last_sub_string(str,'/');
    //       cout<<get_last_sub_string(str,'(',')');

    //  const std::type_info  &ti = typeid(strings);
    //  string s1=get_last_sub_string(str,'(','+');
    //    cout<<"\n";
    //   cout<<"s1:"<<s1;
    //     cout<<"\n";
    //  //   if(s1!="main"&&s1!="__libc_start_main"){
    //         if(1){
    //        //realname = abi::__cxa_demangle(s1.data(), 0, 0, &status);
    //    realname=    demangle(s1.data());
    //   cout<<"real:::";
    //      // cout<<realname;
    //        //   free(realname);
    //               }
    //       cout<<"\n";
    //       fflush(NULL);
    //    }

    free(strings);
}
int main()
{

    //  test1();
    print_backstrace();
    //printf("11\n");
    return 0;
}
