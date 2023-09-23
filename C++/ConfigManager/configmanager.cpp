#include <iostream>
#include <fstream>
#include <assert.h>
#include <string.h>
using namespace std;
struct ServerInfo{ 
    char _ip[32];
    int _port;
};

class ConfigManager
{
public:
    ConfigManager(const char* configfile = "bitserver.config") : _configfile(configfile)
    {}
public:
    void ReadText(ServerInfo& info)
    {
        ifstream ifile;
        ifile.open(_configfile.c_str(), ios::in);
        assert(ifile);
        ifile >> info._ip;
        ifile >> info._port;
        ifile.close();
    }
    void WriteText(ServerInfo& info)
    {
        ofstream ofile;
        ofile.open(_configfile, ios::out);
        assert(ofile);
        ofile << info._ip << endl;
        ofile << info._port << endl;
        ofile.close();
    }
    void WriteBin(ServerInfo& info)
    {
        ofstream ofile;
        ofile.open(_configfile, ios::out | ios::binary);
        assert(ofile);
        ofile.write((const char*)&info, sizeof(info));
        ofile.close(); 
    }
    void ReadBin(ServerInfo& info)
    {
        ifstream ifile;
        ifile.open(_configfile, ios::in | ios::binary);
        assert(ifile);
        ifile.read((char*)&info, sizeof(info));
        ifile.close();
        cout << info._ip << endl;
        cout << info._port << endl;
    }

private:
    string _configfile;
};

int main()
{
    ConfigManager cfg("bite88.config");
    ServerInfo sinfo;
    cfg.ReadText(sinfo);
    strcpy(sinfo._ip, "10.168.122.89");
    sinfo._port = 9090;
    cfg.WriteText(sinfo);
    cfg.WriteBin(sinfo);
    cfg.ReadBin(sinfo);
    
}
