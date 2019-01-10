#include"finalhashtable.h"
#include<bits/stdc++.h>
using namespace std;


template<typename K, typename V>
class OpcodeTable : public HashTable<K,V> , public HTWrapper<K,V> {
    public:
     string serialize(OpcodeTable<K,V> h)
    {
        string s = "";
        for (int i=0; i<10; i++)
        {
            HashNode<K,V>* ptr=h.record[i];
            while (ptr !=  NULL)
            {
                int ln = (ptr->key).length();
                s.push_back('0' + ln);
                s = s + "~" + ptr->key ;
                int w;
                string ww;
                w = get<0>((ptr->object)[0]);
                stringstream s1;
                s1<<w;
                ww=s1.str();
                ln = ww.length();
                s.push_back('0' + ln);
                s = s + "~" + ww;

                w = get<1>((ptr->object)[0]);
                stringstream s2;
                s2<<w;
                 ww=s2.str();
                ln = ww.length();
                s.push_back('0' + ln);
                s = s + "~" + ww;

                w = get<2>((ptr->object)[0]);
                stringstream s3;
                s3<<w;
                ww=s3.str();
                ln = ww.length();
                s.push_back('0' + ln);
                s = s + "~" + ww;
                ptr=ptr->next;
            }
        }
    return s;
    }

     void saveToFile(OpcodeTable<K,V> h)
    {   string filename;
        cout<<"Enter filenames: ";
        cin>>filename;
        ofstream out(filename.c_str());
        cout<<"Record is saved in file: "<<filename<<endl;
        out<<h.serialize(h);
        out.close();
    }

};

template<typename K, typename V>
class Regiter : public HashTable<K,V> , public HTWrapper<K,V>
{

};
class Assembler
{
    public:
    bool saveToFile(string fname,string ptr)
    {
        ofstream out(fname.c_str());
        cout<<"Record is saved in file: "<<fname<<endl;
        out<<ptr;
        out.close();
        return 1;
    }
    template<typename K, typename V>
    string loadFromFile(string fname,OpcodeTable<K,V> h)
    {
        string ff,m,jk;
        ifstream in(fname.c_str());
        while(getline(in,ff)){
         m+=ff+' ';
         jk+=ff;
         validateCode(jk,h);
         jk="";
        }
        in.close();
        return m;
    }
    template<typename K, typename V>
    void validateCode(string m,OpcodeTable<K,V> h)
    {
        string d;
        for(int i=0;i<m.size();i++){
            if(m[i]==' ') break;
            else d+=m[i];
        }
    }
};
int main(){
    OpcodeTable <string,vector<tuple<int,int,int> > > opcodeTable;
   vector<tuple<int,int,int> > v;
   v.push_back(make_tuple(44,2,4));
   opcodeTable.addRecord("MOV",v);
   v.pop_back();
   v.push_back(make_tuple(47,2,4));
   opcodeTable.addRecord("ADD",v);
   v.pop_back();
   v.push_back(make_tuple(67,1,2));
   opcodeTable.addRecord("JUMP",v);
   v.pop_back();
   v.push_back(make_tuple(23,2,4));
   opcodeTable.addRecord("CMP",v);
   v.pop_back();
  // opcodeTable.saveToFile(opcodeTable);
  // opcodeTable.loadFromFile();
  Regiter<string,string> regiter;
  regiter.addRecord("A","000");
  regiter.addRecord("B","001");
  regiter.addRecord("C","010");
  regiter.addRecord("D","011");
 // regiter.saveToFile(regiter);
 // regiter.loadFromFile();
 Assembler as;
 string fn="sam.txt";
// int gg=as.saveToFile(fn,ss);
 cout<<as.loadFromFile(fn,opcodeTable);
}

