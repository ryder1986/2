#ifndef JSONPACKET_H
#define JSONPACKET_H

#include <cstring>
#include <json/json.h>
#include <json/value.h>
#include <tool.h>
using namespace std;
using  namespace Json ;

class JsonPacket
{
    typedef  Value JsonValue;
public:
    JsonPacket(string str)
    {
        JsonValue v;
        Reader r;
        bool rst=r.parse(str,v);
        if(!rst){
            prt(info,"parse err");
        }else
            val=v;
    }

    JsonPacket()
    {
    }

    JsonPacket(vector<JsonPacket> ar)
    {
        JsonValue v;
        int sz=ar.size();
        for(int i=0;i<sz;i++){
            v[i]=ar[i].val;
        }
        val=v;
    }
public:
    JsonPacket(JsonValue v)
    {
        val=v;
    }
public:
    string data()
    {
        FastWriter  w;
        return  w.write(val);
    }

    template <typename T>
    void set(string name,T value)
    {
        if(!name_exist(name,"set")){
            prt(info,"setting key: %s fail",name.data());
        }
        else
            val[name]=value;
#if 0
        check_type(val[name]);
#endif
    }
    void set(string name,JsonPacket p)
    {
        if(!name_exist(name,"set")){
            prt(info,"setting name: %s fail",name.data());
        }
        else
            val[name]=p.val;
    }

    void set(string name,vector<JsonPacket> pkts)
    {
        if(!name_exist(name,"set")){
            prt(info,"setting name: %s fail",name.data());
        }
        else
        {
            for(JsonPacket p:pkts)
                val[name].append(p.value());
        }
    }
    void add(string name,vector<JsonPacket> pkts)
    {
        if(!name_exist(name,"add")){

            for(JsonPacket p:pkts)
                val[name].append(p.value());
        }
        else
        {
            prt(info,"setting name: %s fail",name.data());
        }
    }
    template <typename T>
    void add(string name,T value)
    {
        if(!name_exist(name,"add"))
            val[name]=value;
        else{
            prt(info,"adding key: %s fail,already exist",name.data());
        }


#if 0
        check_type(val[name]);
#endif
    }
    void add(string name,JsonPacket p)
    {
        if(!name_exist(name,"add"))
            val[name]=p.val;
        else{
            prt(info,"adding key: %s fail,already exist",name.data());
        }
    }

    JsonPacket get(string name)
    {
        if(name_exist(name,"get"))
            return JsonPacket(val[name]);
        else
            return JsonPacket();
    }
    int to_int()
    {
        if(val.empty()){
            prt(info,"to int error :no content");
            return 0;
        }
        if(!val.isInt()){
            prt(info,"get error type:not Int");
            return 0;
        }
        return val.asInt();
    }
    double to_double()
    {
        if(val.empty()){
            prt(info,"to  double :no content");
            return 0;
        }
        if(!val.isDouble()){
            prt(info,"get error type:not Double");
            return 0;
        }
        return val.asDouble();
    }

    bool to_bool()
    {
        if(val.empty()){
            prt(info,"to  bool :no content");
            return false;
        }
        if(!val.isBool()){
            prt(info,"get error type:not Bool");
            return false;
        }
        return val.asBool();
    }

    string to_string()
    {
        if(val.empty()){
            prt(info,"to  string :no content");
            return string();
        }
        if(!val.isString()){
            prt(info,"get error type:not String");
            return string();
        }
        return val.asString();
    }

    vector<JsonPacket> to_array()
    {
        vector<JsonPacket>  ar;
        if(val.empty()){
            prt(info,"to  string :no content");

            return ar;
        }
        if(!val.isArray()){
            prt(info,"get error type:not String");
            return ar;
        }
        JsonValue v=val;

        int sz=v.size();
        for(int i=0;i<sz;i++){
            ar.push_back( v[i]);
        }
        return ar;
    }
    JsonValue value()
    {


        return val;
    }

private:
    bool name_exist(string name,string str)
    {
        bool rst=true;
        JsonValue v=val;
        rst=v[name].isNull();
        if(rst&&(str=="get"||str=="set")){
            prt(info," key (%s) not exist",name.data());

        }
        return !rst;
    }
    void check_type(JsonValue v)
    {
        if(v.isArray())   prt(info,"isArray");
        if(v.isBool())   prt(info,"isBool");
        if(v.isDouble())   prt(info,"isDouble");
        if(v.isInt())   prt(info,"isInt");
        if(v.isInt64())   prt(info,"isInt64");
        if(v.isIntegral())   prt(info,"isIntegral");
        if(v.isNull())   prt(info,"isNull");
        if(v.isNumeric())   prt(info,"isNumeric");
        if(v.isObject())   prt(info,"isObject");
        if(v.isString())   prt(info,"isString");
        if(v.isUInt())   prt(info,"isUInt");
        if(v.isUInt64())   prt(info,"isUInt64");

    }

private:
    JsonValue val;

};
class JsonData{
protected:
    JsonPacket config;
public:
    JsonData(JsonPacket pkt)
    {
        config=pkt;
    }
    JsonData()
    {

    }
    virtual void encode()=0;
    virtual void decode()=0;
    JsonPacket data()
    {
        return config;
    }

};
#define DECODE_INT_MEM(mem) {this->mem=config.get(#mem).to_int();}
#define DECODE_STRING_MEM(mem) {this->mem=config.get(#mem).to_string();}
#define DECODE_DOUBLE_MEM(mem) {this->mem=config.get(#mem).to_double();}
#define DECODE_BOOL_MEM(mem) {this->mem=config.get(#mem).to_bool();}
#define DECODE_OBJ_MEM(mem) {this->mem=config.get(#mem);}
#define DECODE_OBJ_ARRAY_MEM(mem)  {auto tmp=config.get(#mem).to_array();this->mem.assign(tmp.begin(),tmp.end());}

#define ENCODE_MEM(mem) {config.add(#mem,this->mem);}
#define ENCODE_INT_MEM(mem) {ENCODE_MEM(mem);}
#define ENCODE_STRING_MEM(mem) {ENCODE_MEM(mem);}
#define ENCODE_DOUBLE_MEM(mem) {ENCODE_MEM(mem);}
#define ENCODE_BOOL_MEM(mem) {ENCODE_MEM(mem);}
#define ENCODE_OBJ_MEM(mem) {config.add(#mem,this->mem.data());}
#define ENCODE_OBJ_ARRAY_MEM(mem) { vector<JsonPacket> pkts;\
    for(auto tmp1:this->mem){pkts.push_back(tmp1.data());}\
    config.add(#mem,pkts);}
#endif // JSONPACKET_H
