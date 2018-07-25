
    g++ ../../tool.cpp   ../../cppjson/json_value.cpp  ../../cppjson/json_writer.cpp  ../../cppjson/json_reader.cpp   --shared -o /root/libjsonlib.so --std=c++11 -I../../cppjson/include

    g++ main.cpp -L/root/ -ljsonlib -o /root/testjson -I../../ -I../../cppjson/include --std=c++11
