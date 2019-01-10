#include<bits/stdc++.h>
#define endl "\n"

using namespace std;

template<typename K, typename V>
class HashNode
{
    public:
    K key;
	V object;
	HashNode* next;
    HashNode(K key, V object)
    {
        this->key = key;
	    this->object = object;
	    this->next = NULL;
    }
};

template<typename K, typename V>
class HashTable
{
    public:
        HashNode<K,V>** record;
        HashTable()
        {
            record = new HashNode<K,V>*[10];
            for (int i=0; i<10 ; i++)
                record[i] = NULL;
        }
        
        int computeHash(string key)
        {
            int len=key.length();
            int sum=0;
            for(int i=0;i<len;i++)
                sum+=key[i];
            return sum%10;
        }
        
        int computeHash(int key)
        {
            return key%10;
        }

        bool hasKey(K key)
        {
            int	index=computeHash(key);
            HashNode<K,V>* entry = record[index];
            while (entry !=  NULL)
            {
                if (entry->key == key)
                {
                    return true;
                }
            }
            return false;
        }

        void addRecord(K key,V object)
        {   
            int i;
            if(hasKey(key))
            {
                cout<<"Duplicate key entries not allowed"<<endl;
            }
            else
            {
                i=computeHash(key);
                HashNode<K,V>* entry = record[i];
                if (entry==NULL)
                {
                    entry = new HashNode<K,V>( key, object);
                    record[i] = entry;
                }
                else 
                    handleCollision(i,key,object);
            }
        }

        void getRecord(K key)
        {
            if(hasKey(key))
            {
                int i=computeHash(key);
                HashNode<K,V>* entry = record[i];
                while (entry !=  NULL)
                {
                    if (entry->key == key)
                    {
                        cout<<entry->object<<" ";
                    }
                    entry = entry->next;
                }
            }
            
            else 
                cout<<"Key does not exist."<<endl;
        }

        void replaceRecord(K key,V object)
        {
            if(hasKey(key))
            {
                int i=computeHash(key);
                bool flag = false;
                HashNode<K,V>* entry = record[i];
                while (entry !=  NULL)
                {
                    if (entry->key == key)
                    {
                        entry->object=object;
                        break;
                    }
                }
            }
            else 
                cout<<"Key does not exist."<<endl;
        }

        void handleCollision(int index,K key,V object)
        { 
            HashNode<K,V>* prev = NULL;
            HashNode<K,V>* entry = record[index];
            {
                while (entry != NULL)
                {
                    prev = entry;
                    entry = entry->next;
                }
                entry = new HashNode<K,V>(key, object);
                prev->next = entry;
            }
        }
        
        void printHashtable()
        {
            for(int i=0; i<10 ; i++)
        {

            HashNode<K,V>* ptr=record[i];
            while (ptr !=  NULL)
            {
                cout<<"Index "<<i<<' '; cout<<"Key: "<< ptr->key <<"  Object: "<<ptr->object<<"\n";
                ptr=ptr->next;
            }
        }
    }
};

template<typename K, typename V>
class HTWrapper
{
    public:
    string serialize(HashTable<K,V> h)
    {
        string s = "";
        for (int i=0; i<10; i++)
        {
            HashNode<K,V>* ptr=h.record[i];
            while (ptr !=  NULL)
            {
                int ln = (ptr->key).length();
                s.push_back('0' + ln);
                s = s + "~" + ptr->key;
                /*int a=ptr->object;
                stringstream ss;
                ss<<a;
                string str=ss.str();*/
                ln = (ptr->object).length();
                s.push_back('0' + ln);
                s = s + "~" + ptr->object ;
                ptr=ptr->next;
            }
        }
    return s;
    }
    
    void deserializer(string str, string deserialize[] )
    {
        int len, pos=0;
        string temp = "";
        int i = 0;
        while(pos>-1)
        {
            pos = str.find("~", pos+1);
            if(pos>0)
            {
                len = str[pos-1] - 48;
                temp.append(str, pos+1, len);
                deserialize[i++] = temp;
                temp = "";
            }
        }
    }
    
    void saveToFile(HashTable<K,V> h)
    {   
        string filename;
        cout<<"Enter filename: ";
        cin>>filename;
        ofstream out(filename.c_str());
        cout<<"Record is saved in file: "<<filename<<endl;
        out<<serialize(h);
        out.close();
    }
    
    void loadFromFile()
    {
        string filename;
        string deserialize[100]={};
        cout<<"Enter filename: ";
        cin>>filename;
        string ff;
        int count=1;
        ifstream in(filename.c_str());
        in>>ff;
        
        deserializer(ff,deserialize);
        
        for(int i=0;i<100;i++)
        {
            cout<<deserialize[i]<<' ';
        }
        cout<<endl;
        in.close();
    }
};
