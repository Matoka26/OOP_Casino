#include <iostream>
#include <fstream>
#include <strings.h>
#include <windows.h>
#include <algorithm>
#include <typeinfo>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <bitset>
#include <stack>
#include <set>
#include <unordered_map>
///79->rosu cu text alb
///7->negru cu text alb
///175->verde cu text alb

///3->inima rosie
///4->romb
///5->trefla
///6->inima neagra
using namespace std;

class Player{


};

class JocCarti{
protected:
    vector<pair<string,string>> pachet;
public:
    JocCarti();
    JocCarti(vector<pair<string,string>> pachet){this->pachet = pachet;}
    JocCarti(const JocCarti& obj){this->pachet = obj.pachet;}
    JocCarti& operator=(const JocCarti& obj);
    friend ostream& operator<<(ostream& out , const JocCarti& obj);
    friend istream& operator>>(istream& in , JocCarti& obj);

    vector<pair<string,string>> getPachet()const{return pachet;}
    int size(){return pachet.size();};
    pair<string,string> &operator[](int index){return pachet[index];}
    virtual pair<string,string> trageCarte();
    ~JocCarti(){};

};
class BlackJack:public virtual JocCarti{
protected:
    unordered_map<string,int>valoriCarti;
public:
    BlackJack();
    BlackJack(vector<pair<string,string>> pachet,unordered_map<string,int> valoriCarti);
    BlackJack(const BlackJack& obj);
    BlackJack& operator=(const BlackJack& obj);
    friend ostream& operator<<(ostream& out,const BlackJack& obj);
    friend istream& operator>>(istream& in , BlackJack& obj);
    ~BlackJack(){};
};

class Pacanea{
private:
    vector<char> slot;
    float multi;
public:
    Pacanea();
    Pacanea(vector<char>slot,float multi){this->slot = slot;this->multi = multi;}
    Pacanea(const Pacanea& obj){this->slot = obj.slot; this->multi = obj.multi;}
    Pacanea& operator=(const Pacanea& obj);
    char &operator[](int index){return slot[index];}
    int size(){return slot.size();}
    friend istream& operator>>(istream& in,Pacanea& obj);
    friend ostream& operator<<(ostream& out,const Pacanea& obj);

    ~Pacanea(){}

};

JocCarti::JocCarti(){
    for(int i = 2 ; i <= 10 ; i++){
        this->pachet.push_back({to_string(i),"rosie"});
        this->pachet.push_back({to_string(i),"neagra"});
        this->pachet.push_back({to_string(i),"romb"});
        this->pachet.push_back({to_string(i),"trefla"});
    }
    this->pachet.push_back({"A","rosie"});
    this->pachet.push_back({"A","neagra"});
    this->pachet.push_back({"A","romb"});
    this->pachet.push_back({"A","trefla"});

    this->pachet.push_back({"J","rosie"});
    this->pachet.push_back({"J","neagra"});
    this->pachet.push_back({"J","romb"});
    this->pachet.push_back({"J","trefla"});

    this->pachet.push_back({"Q","rosie"});
    this->pachet.push_back({"Q","neagra"});
    this->pachet.push_back({"Q","romb"});
    this->pachet.push_back({"Q","trefla"});

    this->pachet.push_back({"K","rosie"});
    this->pachet.push_back({"K","neagra"});
    this->pachet.push_back({"K","romb"});
    this->pachet.push_back({"K","trefla"});

    this->pachet.push_back({"Joker","rosie"});
    this->pachet.push_back({"Joker","neagra"});

}
JocCarti& JocCarti::operator=(const JocCarti& obj){
    if( this != &obj){
        this->pachet = obj.pachet;
    }
    return *this;
}
ostream& operator<<(ostream& out , const JocCarti& obj){
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    out<<"CARTILE DIN PACHET\n"<<char(196)<<char(196)<<char(196)<<char(196)<<char(196)<<char(196)<<char(196)<<"\n";
    for(auto it = obj.pachet.begin() ; it != obj.pachet.end() ; it++){
            if(it->second == "rosie"){
                SetConsoleTextAttribute(h,79);
                out<<it->first<<char(3)<<" ";
            }
            if(it->second == "romb"){
                SetConsoleTextAttribute(h,79);
                out<<it->first<<char(4)<<" ";
            }
            if(it->second == "neagra"){

                SetConsoleTextAttribute(h,7);
                out<<it->first<<char(6)<<" ";
            }
            if(it->second == "trefla"){
                SetConsoleTextAttribute(h,7);
                out<<it->first<<char(5)<<" ";
            }
        }
        SetConsoleTextAttribute(h,7);
        out<<'\n';
        return out;
}
istream& operator>>(istream& in , JocCarti& obj){
    cout<<"Cate carti are pachetul?\n";
    int n;
    in>>n;
    string aux;
    obj.pachet.clear();
    for(int i = 0 ; i < n ; i++){
        cout<<"cartea "<<i<<":";
        in>>aux;
        obj.pachet.push_back({aux,"rosie"});
        obj.pachet.push_back({aux,"neagra"});
        obj.pachet.push_back({aux,"romb"});
        obj.pachet.push_back({aux,"trefla"});
    }

    return in;
}
pair<string,string> JocCarti::trageCarte(){
    pair<string,string> carte = this->pachet[0];
    this->pachet.erase(this->pachet.begin()+1);
    return carte;
}
BlackJack::BlackJack():JocCarti(){
    for(auto it = pachet.begin() ; it != pachet.end() ; it++)
    if(it->first == "Joker"){
        pachet.erase(it);
        it--;
        }

    for(int i = 2 ; i <= 10 ; i++)
        valoriCarti[to_string(i)] = i;
    valoriCarti["A"] = 11;
    valoriCarti["Q"] = 10;
    valoriCarti["K"] = 10;
    valoriCarti["J"] = 10;
}
BlackJack::BlackJack(vector<pair<string,string>> pachet,unordered_map<string,int> valoriCarti):JocCarti(pachet){
    this->valoriCarti = valoriCarti;
}
BlackJack::BlackJack(const BlackJack& obj){
        this->pachet = obj.pachet;
        this->valoriCarti = obj.valoriCarti;
}
BlackJack& BlackJack::operator=(const BlackJack& obj){
    if(this != &obj){
        JocCarti::operator=(obj);
        this->valoriCarti = obj.valoriCarti;
    }
    return *this;
}
ostream& operator<<(ostream& out,const BlackJack& obj){
    out<<(JocCarti&)obj;
    out<<"\nValorile Cartilor:\n"<<char(196)<<char(196)<<char(196)<<char(196)<<char(196)<<char(196)<<char(196)<<'\n';
    for(auto it = obj.valoriCarti.begin() ; it != obj.valoriCarti.end() ; it++)
        out<<it->first<<": "<<it->second<<'\n';
    return out;
}
istream& operator>>(istream& in , BlackJack& obj){
    in>>(JocCarti&)obj;
    int aux;
    obj.valoriCarti.clear();
    cout<<"Alegeti valori pt carti\n";
    for(auto it = obj.pachet.begin() ; it != obj.pachet.end() ; it += 4){
        cout<<"Cartile cu "<<it->first<<':';
        in>>aux;
        obj.valoriCarti[it->first] = aux;
    }

    return in;
}
Pacanea::Pacanea(){
    for(int i = 0 ; i < 3 ; i++){
        this->slot.push_back('J');
        this->slot.push_back('Q');
        this->slot.push_back('K');
    }
    this->multi = 0.2;
}
Pacanea& Pacanea::operator=(const Pacanea& obj){
    if(this != &obj){
        this->slot = obj.slot;
        this->multi = obj.multi;
    }
    return *this;
}
ostream& operator<<(ostream& out,const Pacanea& obj){
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    out<<setw(57)<<"PACANEA\n"<<setw(48)<<char(196)<<char(196)<<char(196)<<char(196)<<char(196)<<char(196)<<char(196)<<char(196)<<char(196)<<char(196)<<char(196)<<"\n";
    out<<setw(50);
    for(int i = 0 ; i < 9 ; i++){
        if( (i >= 3 && i <= 5)&&((obj.slot[3] == obj.slot[4] && obj.slot[4] == obj.slot[5]) || obj.slot[3] == obj.slot[4]))
            SetConsoleTextAttribute(h,10);
        if( obj.slot[4] != obj.slot[5] && i == 5  ) SetConsoleTextAttribute(h,7);
        out<<obj.slot[i]<<"  ";
        SetConsoleTextAttribute(h,7);
        if(!(i%3 -2)){
            out<<'\n';
            out<<setw(50);
        }
    }
    out<<"\nMultiplicator: "<<obj.multi<<'\n';
    return out;
}
istream& operator>>(istream& in, Pacanea& obj){
    obj.slot.clear();
    cout<<"Cate simboluri ai?\n";
    int n;
    char aux;
    in>>n;
    for(int i = 0 ; i < n ; i++){
        cout<<"Caracterul "<<i<<": ";
        in>>aux;
        obj.slot.push_back(aux);
    }
    if(n < 9){
        for(int i = 9 - n ; i > 0 ; i--)
            obj.slot.push_back('-');
    }
    return in;
}


template<typename T> ///sa supraincarci size pt toate si []
void amesteca(T& joc){
    srand(time(nullptr));
    T aux = joc;
    vector<bool> v(joc.size());
    for(int i = 0 ; i < joc.size() ; i++){
        int idk = rand() % joc.size();
        while(v[idk])
            idk = (idk+1)%joc.size();

        joc[idk] = aux[i];
        v[idk] = 1;
        }
}

/*
template<class T>
class MasaJoc{
private:
    T joc;
    int playeri = 0;
public:
};
*/

class Casino{
public:
    int fonduri;
public:
    Casino();
    ~Casino();
};

Casino::Casino(){
    /*
    ifstream fisBani("bani.in",ios::binary | ios::in); ///flaguri pt binara si input
    if(fisBani){
        fisBani.seekg(0,fisBani.end);
        int lung = fisBani.tellg();
        fisBani.seekg(0,fisBani.beg);

        char* aux = new char[lung];
        char* maOmor = new char[lung-208];
        fisBani.read(aux,lung);

        int k = 0;
        for(int i = 208 ; i < lung ; i++)
            maOmor[k++] = aux[i];

        if(fisBani){
            string s = "";
            for(int i = 0 ; i < lung-208 ; i++){
                if(maOmor[i] == '0')
                    s.append("0");
                else
                    s.append("1");
            }
            ///mai ai sa faci tot stringu ala de 1010101110110 in ceva numere
            for(int i = 0 ; i < s.size()/8 ; i++){
                for(int j = 0 ; j < 8 ; j++){

                }
            }

           // fonduri = stoi(s,0,2);
        }else
            fonduri = 0;

        delete[] aux;
        delete[] maOmor;
        fisBani.close();
    }
    */
}

Casino::~Casino(){
    /*
    ofstream fisBani("bani.in", ios::binary | ios::out); ///flaguri pt binara si output
    string s="Ultimul check al contului:";
    string msgFinal;
    if(fonduri < 0)
        msgFinal = "faliment";
    else{
        msgFinal = to_string(fonduri);
    }
    s.append(msgFinal);
    char* aux = new char[s.size()*8+1];
    int k = 0;
    for(int i = 0 ; i < s.length() ; i++){
        for(int j = 7 ; j >= 0; j--){
            if(bitset<8>(s[i])[j] == false) aux[k++] = '0';
            else aux[k++] = '1';
        }
    }
    fisBani.write(aux,s.size()*8);
    if(aux != NULL)
        delete[] aux;
    fisBani.close();
    */
}

int main()
{
    JocCarti basic;
    Pacanea paca;
    Casino c;
    BlackJack b,r;

}
