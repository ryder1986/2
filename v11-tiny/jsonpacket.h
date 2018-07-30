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
//    JsonPacket(const JsonPacket &v)
//    {
//        val=v.value();
//    }
public:
    string data()
    {
#if 1
   //     FastWriter  w;
        FastWriter  w;
             //     StyledWriter  w;
        return  w.write(val);
#else
        return val.asString();
#endif
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

public:
    JsonPacket config;
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
template<typename TP>
class VdData{
protected:
    TP private_data;
public:
    VdData(TP d):private_data(d)
    {
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

template <typename T>
class RequestData:public JsonData
{
public:
    int op;
    int index;
    T data;

    RequestData(int op,int index , T data):op(op),index(index),data(data)
    {

    }
    RequestData()
    {

    }

    void encode()
    {

    }
    void decode()
    {

    }

};

class VdEvent:public JsonData
{
public:
    int op;
    int index;
    JsonPacket arg;
    JsonPacket ret;

    VdEvent(int op,int index , JsonPacket data,JsonPacket rt=JsonPacket()):op(op),index(index),arg(data),ret(rt)
    {
        encode();
    }
    VdEvent(JsonPacket p):JsonData(p)
    {
        decode();
    }
//    VdEvent(JsonPacket &&p):JsonData(p)
//    {
//        decode();
//    }
//    VdEvent(VdEvent &&e):JsonData(e.data)
//    {
//        decode();
//    }
//    VdEvent(VdEvent &e):JsonData(e.data)
//    {
//        decode();
//    }
//    void operator =(const VdEvent &e)
//    {
//          decode();
//    }
    void encode()
    {
        ENCODE_INT_MEM(index);
        ENCODE_INT_MEM(op);
        config.add("arg",arg);
        config.add("ret",ret);

    }
    void decode()
    {
        DECODE_INT_MEM(op);
        DECODE_INT_MEM(index);
        arg=config.get("arg");
        ret=config.get("ret");
    }

};

//template <typename T>
//class RequestData:public JsonData
//{
//public:
//    int op;
//    int index;
//    T data;

//    RequestData()
//    {

//    }

//    RequestData(JsonPacket pkt)
//    {
//        decode();
//    }
//    RequestData(int o,int i,int d):op(o),index(i),data(d)
//    {
//        encode();
//    }
//private:
//    void decode()
//    {
//        DECODE_STRING_MEM(op);
//        DECODE_STRING_MEM(index);
//        DECODE_OBJ_MEM(data);
//    }
//    void encode()
//    {
//        ENCODE_STRING_MEM(op);
//        ENCODE_STRING_MEM(index);
//        ENCODE_OBJ_MEM(data);
//    }
//};
//class VdEvent{
//public:
//    RequestData e;
//    virtual void process_event(JsonPacket data)
//    {
//         e=data;
//    }


//};



#endif // JSONPACKET_H
