#include <iostream>
#include <conio.h>
#include <string.h>
#include <list>
using namespace std;


class IOInterface {
public:
    virtual istream& citire(istream& in) = 0;
    virtual ostream& afisare(ostream& out) const = 0;
};


//Volum
class Volum:public IOInterface {
protected:
    string numeVolum;
    string autor;
    float pret;                //pretul volumului
    bool InStoc;           // daca este sau nu disponibila
    int idVolum;
    int nrExemplare;
public:
//constructori
    Volum();
    Volum(string numeVolum, string autor, float pret, bool InStoc, int idVolum, int nrExemplare);
//constructor de copiere
    Volum( const Volum &v);
//Supraincarcarea operatorului egal pentru obiecte de tip Volum
    Volum& operator =(const Volum& v);

//metode virtuale
    virtual ostream& afisare(ostream& out)const;
    virtual istream& citire(istream& in);

//suprascrierea operatorului <<
    friend ostream & operator<<(ostream & out, const Volum &v);
//suprascrierea operatorului >>
    friend istream & operator>>(istream &in, Volum &v);
//supraincarcarea operatorului pre-incrementare
    const Volum operator--();
//supraincarcarea operatorului post-incrementare
    const Volum operator--(int);

//supraincarcarea operatorului + pentru float
    Volum operator+(int f);//Volum+float
    friend Volum operator+(int f, Volum v);//float+Volum
    // supraincarcare ==
    bool operator==(const Volum& v);
//cast la float
    explicit operator float() {
        return (float)this->pret;
    }
//seters
    void setInStoc(bool InStoc);
    void setNumeVolum( string numeVolum);
    void setAutor( string autor);
    void setPret(float pret);
    void setIdVolum(int idVolum);
    void setNrExemplare(int nrExemplare);
//geters
    bool getInStoc();
    string getNumeVolum();
    string getAutor();
    float getPret();
    int getId();
    int getNrExemplare() ;
//
    virtual double pretCuTransport();
    virtual~Volum();




};
//constructrs
Volum::Volum() {
    //cout<<"Volum\n";
    this->numeVolum="nu se cunoaste";
    this->autor="Anonim";
    this->pret=0;
    this->InStoc=false;
    this->idVolum=-1;
    this->nrExemplare=0;
}

Volum::Volum(string numeVolum, string autor, float pret, bool InStoc, int idVolum, int nrExemplare) {
    //cout<<"V\n";
    this->numeVolum=numeVolum;
    this->autor=autor;
    this->pret=pret;
    this->InStoc=InStoc;
    this->idVolum=idVolum;
    this->nrExemplare=nrExemplare;
}
//constructor de copiere
Volum::Volum(const Volum &v) {
    //cout<<"V\n";
    this->numeVolum=v.numeVolum;
    this->autor=v.autor;
    this->pret=v.pret;
    this->InStoc=v.InStoc;
    this->idVolum=v.idVolum;
    this->nrExemplare=v.nrExemplare;
}
//supraincarcarea operatorului = pt clasa Volum
Volum& Volum::operator =(const Volum& v) {
    //cout<<"V\n";
    if(this != &v) {
        this->numeVolum=v.numeVolum;
        this->autor=v.autor;
        this->pret=v.pret;
        this->InStoc=v.InStoc;
        this->idVolum=v.idVolum;
        this->nrExemplare=v.nrExemplare;
    }

    return* this;
}
//metoda virtuala de citire
istream& Volum::citire(istream& in) {

    char s[1000];
    cout<<"Introduceti numele volumului:";
    in.get(s,1000);
    in.get();
    this->numeVolum=s;

    cout<<"Introduceti numele autorului:";
    in.get(s,1000);
    in.get();
    this->autor=s;

    cout<<"Introduceti pretul:";
    in>>this->pret;

    cout<<"Este in stoc?(intorduceti 1 pt da 0 altfel)";
    in>>this->InStoc;
    cout<<"Nr exemplare:";
    in>>this->nrExemplare;
    return in;

}
//supraincarcarea operatorului>>
istream & operator>>(istream &in, Volum &v) {
    return v.citire(in);
}
//metoda virtuala de afisare
ostream & Volum::afisare(ostream & out ) const {
    out<<"Numele volumului este: "<<this->numeVolum<<endl;
    out<<"Numele autorului este: "<<this->autor<<endl;
    out<<"Status volum : "<<(!this->InStoc?"nu este in stoc":"este in stoc")<<endl;
    out<<"Id-ul volumului este:"<<this->idVolum<<endl;
    out<<"Pretul este: "<<this->pret<<endl;
    out<<"Nr exemplare disponibile: "<<this->nrExemplare;
    return out;
}
//supraincarcarea operatorului<<
ostream & operator<<(ostream & out, const Volum &v) {
    return v.afisare(out);
}
//supraincarcarea operatorului pre-incrementare
const Volum Volum::operator--() {
    this->nrExemplare--;
    return *this;
}
//supraincarcarea operatorului post-incrementare
const Volum Volum::operator--(int) {
    Volum aux(*this);
    this->nrExemplare--;
    return aux;
}
//supraincarcare ==;
bool Volum::operator==(const Volum& v) {
    if(v.numeVolum==this->numeVolum && this->autor==v.autor)
        return true;
    return false;
}
//supraincarcarea operatorului + pentru float
Volum Volum::operator+(int f) { //Volum+float
    Volum aux(*this);
    aux.nrExemplare=aux.nrExemplare+f;
    return aux;
}
Volum operator+(int f, Volum v) { //float+Volum
    Volum aux(v);
    aux.nrExemplare=aux.nrExemplare+f;
    return aux;
}
//seters
void Volum::setInStoc(bool InStoc) {
    this->InStoc=InStoc;
}
void Volum::setNumeVolum( string numeVolum) {
    this->numeVolum=numeVolum;
}
void Volum::setAutor( string autor) {
    this->autor=autor;
}
void Volum::setPret(float pret) {
    this->pret=pret;
}
void Volum::setIdVolum(int idVolum) {
    this->idVolum=idVolum;
}
void Volum::setNrExemplare(int nrExemplare) {
    this->nrExemplare = nrExemplare;
}
int Volum::getNrExemplare() {
    return nrExemplare;
}

//geters
bool Volum::getInStoc() {
    return this->InStoc;
}
string Volum::getNumeVolum() {
    return this->numeVolum;
}
string Volum::getAutor() {
    return this->autor;
}
float Volum::getPret() {
    return this->pret;
}
int Volum::getId() {
    return this->idVolum;
}

//alte metode
double Volum:: pretCuTransport() {
    return 1.01*(this->pret);
}

//destructor
Volum::~Volum() {

    this->numeVolum="";
    this->autor="";
    this->idVolum=0;
    this->InStoc=false;
    this->pret=0;
}


///-------------------------------------------------------------------------------------------------------------------------------
///volum proza

class VolumProza:public virtual Volum {
protected:
    int nrOpere;
    string tipOpere;
    void Copiere( const VolumProza& v);

public:
    VolumProza();
    VolumProza( string numeVolum,  string autor, float pret, bool inStoc, int idVolum, int nrExemplare, int nrOpere, string tipOpere);
//constructor de copiere
    VolumProza( const VolumProza &v);
//Supraincarcarea operatorului egal pentru obiecte de tip VolumProza
    VolumProza& operator =(const VolumProza& v);
//metode virtuale
    virtual ostream& afisare(ostream& out)const;
    virtual istream& citire(istream& in);
    istream& citireVproza(istream& in);
    ostream& afisareVProza(ostream& out)const;
//suprascrierea operatorului <<
    friend ostream & operator<<(ostream & out, const VolumProza &v);
//suprascrierea operatorului >>
    friend istream & operator>>(istream &in, VolumProza &v);

//supraincarcarea operatorului + pentru float
    VolumProza operator+(int f);//Volum+float
    friend VolumProza operator+(int f, VolumProza v);//float+Volum

    //supraincarcarea operatorului pre-incrementare
    const VolumProza operator--();
//supraincarcarea operatorului post-incrementare
    const VolumProza operator--(int);
//
    double pretCuTransport();
    virtual~VolumProza();
};

VolumProza::VolumProza():Volum() {
    //cout<<"VolumProza\n";
    this->nrOpere=0;
    this->tipOpere="nu se cunoaste";
}

VolumProza::VolumProza( string numeVolum,  string autor, float pret, bool inStoc, int idVolum, int nrExemplare, int nrOpere, string tipOpere) : Volum(numeVolum, autor, pret, inStoc, idVolum, nrExemplare) {
    //cout<<"VPr\n";
    this->nrOpere=nrOpere;
    this->tipOpere=tipOpere;
}
//copy const
VolumProza::VolumProza( const VolumProza &v):Volum(v) {
    //cout<<"VPr\n";
    this->tipOpere=v.tipOpere;
    this->nrOpere=v.nrOpere;
}

//Supraincarcarea operatorului egal pentru obiecte de tip VolumProza
void VolumProza::Copiere(const VolumProza& v){
    this->nrOpere=v.nrOpere;
    this->tipOpere=v.tipOpere;
}
VolumProza& VolumProza::operator =(const VolumProza& v) {
    if(this!=&v) {
        Volum::operator=(v);
        this->Copiere(v);
    }
    return *this;
}

ostream& VolumProza::afisareVProza(ostream& out)const{
    out<<"\nnr de opere este:"<<this->nrOpere;
    out<<"\nTipul de opere :"<<this->tipOpere;
    return out;
}
ostream& VolumProza::afisare(ostream& out)const {
    this->Volum::afisare(out);
    this->afisareVProza(out);
    return out;
}

//suprascrierea operatorului <<
ostream & operator<<(ostream & out, const VolumProza &v) {
    v.afisare(out);
    return out;
}
istream& VolumProza::citireVproza(istream& in){
    in.get();
    char s[1000];
    cout<<"Introduceti tipul operelor:";
    in.get(s,1000);
    in.get();
    this->tipOpere=s;
    cout<<"Introduceti nr de opere:";
    in>>this->nrOpere;
    return in;
}
istream& VolumProza::citire(istream& in) {
    this->Volum::citire(in);
    this->citireVproza(in);
    return in;
}
//suprascrierea operatorului >>
istream & operator>>(istream &in, VolumProza &v) {
    v.citire(in);
    return in;
}

//supraincarcarea operatorului pre-incrementare
const VolumProza VolumProza::operator--() {
    this->Volum::operator--();
    return *this;
}
//supraincarcarea operatorului post-incrementare
const VolumProza VolumProza::operator--(int) {
    VolumProza aux(*this);
    this->Volum::operator--();
    return aux;
}

VolumProza VolumProza::operator+(int f) {
    VolumProza aux(*this);
    aux.nrExemplare+=f;
    return aux;
}
VolumProza operator+(int f, VolumProza v) {
    VolumProza aux(v);
    aux.nrExemplare+=f;
    return aux;
}
//alte metode
double VolumProza::pretCuTransport() {
    return 1.02*(this->pret);
}


VolumProza::~VolumProza() {
    this->tipOpere="";
    this->nrOpere=0;
}



///-----------------------------------------------------------------------------------------------------------------------
// volum poezie

class VolumPoezie:public virtual Volum {
protected:
    int nrPoezi;
    string tipPoezi;
    void Copiere(const VolumPoezie& v);
public:
    VolumPoezie();
    VolumPoezie( string numeVolum,  string autor, float pret, bool inStoc, int idVolum, int nrExemplare, int nrPoezi, string tipPoezi);
//constructor de copiere
    VolumPoezie( const VolumPoezie &v);
//Supraincarcarea operatorului egal pentru obiecte de tip VolumPoezie
    VolumPoezie& operator =(const VolumPoezie& v);
//metode virtuale
    virtual ostream& afisare(ostream& out)const;
    virtual istream& citire(istream& in);
    istream& citireVPoezie(istream& in);
    ostream& afisareVPoezie(ostream& out)const;
//suprascrierea operatorului <<
    friend ostream & operator<<(ostream & out, const VolumPoezie &v);
//suprascrierea operatorului >>
    friend istream & operator>>(istream &in, VolumPoezie &v);

//supraincarcarea operatorului pre-incrementare
    const VolumPoezie operator--();
//supraincarcarea operatorului post-incrementare
    const VolumPoezie operator--(int);

//supraincarcarea operatorului + pentru int
    VolumPoezie operator+(int f);
    friend VolumPoezie operator+(int f, VolumPoezie v);

    double pretCuTransport();

    virtual~VolumPoezie();

};

VolumPoezie::VolumPoezie():Volum() {
    //cout<<"VolumPoezie\n";
    this->nrPoezi=0;
    this->tipPoezi="nu se cunoaste";
}

VolumPoezie::VolumPoezie( string numeVolum,  string autor, float pret, bool inStoc, int idVolum, int nrExemplare, int nrPoezi, string tipPoezi) : Volum(numeVolum, autor, pret, inStoc, idVolum, nrExemplare) {
    //cout<<"VPo\n";
    this->nrPoezi=nrPoezi;
    this->tipPoezi=tipPoezi;
}
//copy const
VolumPoezie::VolumPoezie( const VolumPoezie &v):Volum(v) {
    //cout<<"VPo\n";
    this->tipPoezi=v.tipPoezi;
    this->nrPoezi=v.nrPoezi;
}

//Supraincarcarea operatorului egal pentru obiecte de tip VolumPoezie
void VolumPoezie::Copiere(const VolumPoezie& v){
    this->tipPoezi=v.tipPoezi;
    this->nrPoezi=v.nrPoezi;
}
VolumPoezie& VolumPoezie::operator =(const VolumPoezie& v) {
    if(this!=&v) {
        Volum::operator=(v);
       this->Copiere(v);
    }
    return *this;
}


ostream& VolumPoezie::afisare(ostream& out)const {
    this->Volum::afisare(out);
    this->afisareVPoezie(out);
    return out;
}
ostream& VolumPoezie::afisareVPoezie(ostream& out)const{
    out<<"\nnr de poezi este:"<<this->nrPoezi;
    out<<"\nTipul de poezi :"<<this->tipPoezi;
    return out;
}
//suprascrierea operatorului <<
ostream & operator<<(ostream & out, const VolumPoezie &v) {
    v.afisare(out);
    return out;
}
istream& VolumPoezie::citireVPoezie(istream& in){
    in.get();
    char s[1000];
    cout<<"Introduceti tipul poezi:";
    in.get(s,1000);
    in.get();
    this->tipPoezi=s;
    cout<<"Introduceti nr de poezi:";
    in>>this->nrPoezi;
    return in;
}
istream& VolumPoezie::citire(istream& in) {
    this->Volum::citire(in);
    this->citireVPoezie(in);
    return in;
}
//suprascrierea operatorului >>
istream & operator>>(istream &in, VolumPoezie &v) {
    v.citire(in);
    return in;
}

const VolumPoezie VolumPoezie::operator--() {
    this->Volum::operator--();
    return *this;
}
//supraincarcarea operatorului post-incrementare
const VolumPoezie VolumPoezie::operator--(int) {
    VolumPoezie aux(*this);
    this->Volum::operator--();
    return aux;
}

VolumPoezie VolumPoezie::operator+(int f) {
    VolumPoezie aux(*this);
    aux.nrExemplare+=f;
    return aux;
}
VolumPoezie operator+(int f, VolumPoezie v) {
    VolumPoezie aux(v);
    aux.nrExemplare+=f;
    return aux;
}


double VolumPoezie::pretCuTransport() {
    return (this->pret)*1.02;
}


VolumPoezie::~VolumPoezie() {
    this->tipPoezi="";
    this->nrPoezi=0;
}




///------------------------------------------------------------------------------------------------------------
class VolumMixt:public  VolumPoezie,
                public  VolumProza {
private:
    float procentReducere;
public:
    VolumMixt();
    VolumMixt( string numeVolum,  string autor, float pret, bool inStoc, int idVolum, int nrExemplare, int nrPoezi, string tipPoezi, int nrOpere, string tipOpere, float procentReducere);
//constructor de copiere
    VolumMixt( const VolumMixt &v);
//Supraincarcarea operatorului egal pentru obiecte de tip VolumPoezie
    VolumMixt& operator =(const VolumMixt& v);
//metode virtuale
    virtual ostream& afisare(ostream& out)const;
    virtual istream& citire(istream& in);
//suprascrierea operatorului <<
    friend ostream & operator<<(ostream & out, const VolumMixt &v);
//suprascrierea operatorului >>
    friend istream & operator>>(istream &in, VolumMixt &v);

//supraincarcarea operatorului pre-incrementare
    const VolumMixt operator--();
//supraincarcarea operatorului post-incrementare
    const VolumMixt operator--(int);

//supraincarcarea operatorului + pentru float
    VolumMixt operator+(int f);//Volum+float
    friend VolumMixt operator+(int f, VolumMixt v);//float+Volum
//alte metode
    double pretCuTransport();
    virtual ~VolumMixt();
};

//constructori
VolumMixt::VolumMixt():Volum(),VolumPoezie(),VolumProza() {
    // cout<<"VolumMixt\n";
    this->procentReducere=0;
}

VolumMixt::VolumMixt( string numeVolum,  string autor, float pret, bool inStoc, int idVolum, int nrExemplare, int nrPoezi, string tipPoezi, int nrOpere, string tipOpere,float procentReducere): VolumProza(numeVolum,autor,pret,InStoc,idVolum,nrExemplare,nrOpere,tipOpere),
                                                                                                                                                                                                 VolumPoezie(numeVolum,autor,pret,InStoc,idVolum,nrExemplare,nrPoezi,tipPoezi),
                                                                                                                                                                                                 Volum(numeVolum,autor,pret,InStoc,idVolum,nrExemplare) {
    //cout<<"VM\n";
    this->procentReducere=procentReducere;
}
//copy const
VolumMixt::VolumMixt( const VolumMixt &v):Volum(v),VolumPoezie(v),VolumProza(v) {
    //cout<<"VM\n";
    this->procentReducere=v.procentReducere;
}

//Supraincarcarea operatorului egal pentru obiecte de tip VolumPoezie
VolumMixt& VolumMixt:: operator =(const VolumMixt& v) {
    if(this!=&v) {
        Volum::operator=(v);
        this->VolumProza::Copiere(v);
        this->VolumPoezie::Copiere(v);
        this->procentReducere=v.procentReducere;
    }
    return *this;
}

//fuctii virtuale de citire si afisare
ostream& VolumMixt::afisare(ostream& out)const {
    this->Volum::afisare(out);
    this->VolumPoezie::afisareVPoezie(out);
    this->VolumProza::afisareVProza(out);
    out<<"\nBani economisiti:"<<this->pret*this->procentReducere;
    return out;
}
istream& VolumMixt::citire(istream& in) {
    this->Volum::citire(in);
    this->VolumPoezie::citireVPoezie(in);
    this->VolumProza::citireVproza(in);
    cout<<"Introduceti reducerea in procente(ex 0.1): ";
    in>>this->procentReducere;
    return in;
}

//suprascrierea operatorului <<
ostream & operator<<(ostream & out, const VolumMixt &v) {
    return v.afisare(out);
}
//suprascrierea operatorului >>
istream & operator>>(istream &in, VolumMixt &v) {
    return v.citire(in);
}

const VolumMixt VolumMixt::operator--() {
    this->Volum::operator--();
    return *this;
}
//supraincarcarea operatorului post-incrementare
const VolumMixt VolumMixt::operator--(int) {
    VolumMixt aux(*this);
    this->Volum::operator--();
    return aux;
}

VolumMixt VolumMixt::operator+(int f) {
    VolumMixt aux(*this);
    aux.nrExemplare+=f;
    return aux;
}
VolumMixt operator+(int f, VolumMixt v) {
    VolumMixt aux(v);
    aux.nrExemplare+=f;
    return aux;
}

//alte metode
double VolumMixt::pretCuTransport() {
    return this->pret *1.03;
}
//destructor
VolumMixt::~VolumMixt() {
    this->procentReducere=0;
}


///Magazin..................

class Magazin {
private:
    string numeMagazin;
    list<Volum*> V;//vector de carti

public:
//constructori
    Magazin();
    Magazin(string numeMagazin, list<Volum*> V);
// constructor de copiere
    Magazin(Magazin &m);
// Supraincarcarea operatorului = pentru obiecte de tip Magazin
    Magazin& operator =(const Magazin& m);

//suprascrierea operatorului <<
    friend ostream & operator<<(ostream & out, const Magazin &m);
//suprascrierea operatorului >>
    friend istream & operator>>(istream &in, Magazin &m);

//supraincarcarea operatorului + pentru Volum
    Magazin operator+(Volum *c);//Magazin+Volum
    friend Magazin operator+(Volum *c, Magazin b);//Volum+Magazin
//supraincarcarea operatorului []
    Volum* operator[](int index);
//geters
    int getNrCarti();
    Volum getVolum(char *autor, char* nume);
//afisare
    ostream & afisare( ostream & out) const ;
//set
    void setNume(string nume);
//alte metode
    void stergereVolum(Volum *c); // sterge Voluma c din Magazin.
    bool existaId(int id);
    int generareId();
    int size();
//destructor
    ~Magazin();
};
//constructors
Magazin::Magazin() {
    this->numeMagazin="anonim";
    this->V.clear();

}

Magazin::Magazin(string numeMagazin, list<Volum*> V) {
    this->numeMagazin=numeMagazin;
    this->V=V;
}
// constructor de copiere
Magazin::Magazin(Magazin &m) {
    this->numeMagazin=m.numeMagazin;
    this->V=m.V;

}
// Supraincarcarea operatorului egal pentru obiecte de tip Magazin
Magazin& Magazin:: operator =(const Magazin& m) {
    if(this != &m) {
        this->numeMagazin=m.numeMagazin;
        this->V=m.V;
    }
    return *this;
}
//supraincarcarea operatorului>>
istream & operator>>(istream &in, Magazin &m) {
    char s[1000];
    cout<<"Intorduceti numele magazinului:";
    in.get(s,1000);
    m.numeMagazin=s;
    in.get();

    cout<<"Introduceti numarul de carti:";
    int n;
    in>>n;
    for(int i=1; i<=n; i++) {
        cout<<"Daca este un volum de proza apasati 1\n"
            <<"Daca este un volum de poezii apasati 2\n"
            <<"Daca este un volum mixt pasati 3\n";
        int x;
        in>>x;
        Volum *v;
        if(x==1)
            v=new VolumProza;
        if(x==2)
            v=new VolumPoezie;
        if(x==3)
            v=new VolumMixt;
        if(x>=1 && x<=3) {
            in.get();
            in>>*v;
            m=m+v;
        }
    }
    return in;
}
//supraincarcarea operatorului<<
ostream & Magazin::afisare (ostream &out) const {
    out<<"Numele magazinului este: "<<this->numeMagazin<<endl<<endl;
    out<<"Cele "<<this->V.size()<<" volume din Magazin sunt:"<<endl;
    list<Volum*>::const_iterator it;// const pt ca ii trimit un obiect constant asa ca V.begin o sa fie const_iterator
    int i=0;
    for (it = this->V.begin(); it != this->V.end(); it++) {
        out<<"Voluma "<<++i<<" este:"<<endl<<*(*it);//*it sa afiseze valoarea din iterator(un pointer) iar *(*it) sa ajiseze volumul:) (altfel afiseaza o adresa de memorie)
        out<<endl<<endl;;
    }
    return out;
}
ostream & operator<<(ostream & out,  const Magazin &m) {
    return m.afisare(out);
}

//supraincarcarea operatorului + pentru Volum
Magazin Magazin::operator+(Volum *v) { //Magazin+Volum
    Magazin aux(*this);
    (*v).setIdVolum(aux.generareId());
    aux.V.push_back(v);
    return aux;
}
Magazin operator+(Volum *v, Magazin m) { //Volum+Magazin
    Magazin aux(m);
    (*v).setIdVolum(aux.generareId());
    aux.V.push_back(v);
    return aux;
}
//supraincarcarea operatorului []
Volum* Magazin::operator[](int index) { // metoda returneaza Voluma de pe pozitia index din Magazin
    index=index%(this->V.size());
    list<Volum*>::const_iterator it= this->V.begin();// const pt ca ii trimit un obiect constant asa ca V.begin o sa fie const_iterator
    for (int i=0; i<index; it++,i++)
        ;
    return *it;
}
//setres
void Magazin::setNume(string numeMagazin) {
    this->numeMagazin=numeMagazin;
}
//alte metode
int Magazin::getNrCarti() {
    int total=0;
    list<Volum*>::const_iterator it;// const pt ca ii trimit un obiect constant asa ca V.begin o sa fie const_iterator
    for (it = this->V.begin(); it != this->V.end(); it++)
        total+=(*it)->getNrExemplare();

    return total;
}

void Magazin::stergereVolum(Volum *v) {
    V.remove(v);
    //delete v;
}

bool Magazin::existaId(int id) {
    list<Volum*>::const_iterator it;// const pt ca ii trimit un obiect constant asa ca V.begin o sa fie const_iterator
    for (it = this->V.begin(); it != this->V.end(); it++) {
        if((*(*it)).getId()==id)//*it sa afiseze valoarea din iterator(un pointer) iar *(*it) sa ajiseze volumul:) (altfel afiseaza o adresa de memorie)
            return true;
    }
    return false;
}
int Magazin::generareId() { //functia genereaza un id nou, care nu a mai fost atribuit unei alte carti.
    int id;
    do {
        id=abs(rand())+1;
    } while(this->existaId(id));
    return id;
}
int Magazin::size(){
    return this->V.size();
}
//destructor
Magazin::~Magazin() {
    this->numeMagazin="anonim";
    this->V.clear();
}

///Meniu

void Meniu() {
    cout<<endl;
    cout<<"+---------------Meniu--------------------------------+"<<endl;
    cout<<"|Pentru a inchide programul apasati tasta 0.         |"<<endl;
    cout<<"|Pentru a accesa meniul administratorului apsati 1   |"<<endl;
    cout<<"|Pentru a vizualiza produsele din magazin apasati 2  |"<<endl;
    cout<<"|Pentru a adauga un produs in cos apasati 3.         |"<<endl;
    cout<<"|Pentru a vizualiza cosul apasati 4                  |"<<endl;
    cout<<"|Pentru a elimina un produs din cos apasati 5        |"<<endl;
    cout<<"|Pentru a achita apasati 6                           |"<<endl;
    cout<<"+----------------------------------------------------+"<<endl;
    cout<<endl;
}
void MeniuAdmin() {
    cout<<endl;
    cout<<"+---------------Meniu-Admin--------------------------+"<<endl;
    cout<<"|Pentru a inchide programul apasati tasta 0.         |"<<endl;
    cout<<"|Pentru a parasi meniul de administrator apasati 1   |"<<endl;
    cout<<"|Pentru a vizualiza produsele din magazin apasati 2  |"<<endl;
    cout<<"|Pentru a adauga o carte apasati 3                   |"<<endl;
    cout<<"|Pentru a elimina  o carte apasati 4                 |"<<endl;
    cout<<"|Pentru a modifica o carte apasati 5                 |"<<endl;
    cout<<"+----------------------------------------------------+"<<endl;
    cout<<endl;
}

void Optiunea2(Magazin M){
    for(int i=0;i<M.size();i++)
        if(M[i]->getInStoc())
            cout<<*M[i]<<endl;
}

void Optiunea3(Magazin M, list<Volum*> & Cos) {
    cout<<"introduceti id ul produsului:";
    int id;
    cin>>id;
    if(M.existaId(id)){
        Volum *v;
        for (int i=0;i<M.size();i++)
            if(M[i]->getId()==id)
                v=M[i];
        Cos.push_back(v);
    }
    else
        cout<<"Nu ati introdus un id valid\n";

}

void Optiunea5(list<Volum*> & Cos){
    int id,sem=0;
    cout<<"Introduceti id ul produsului: ";
    cin>>id;
    list<Volum*>::iterator it;
    for(it=Cos.begin();it!=Cos.end();it++)
        if((*it)->getId()==id){
            Cos.remove(*it);
            break;
            sem=1;
        }
    if(sem=1)
        cout<<"Volumul a fost eliminat"<<endl;
    else
        cout<<"Nu exista un produs cu acest id\n";
}

void Optiunea4(list<Volum*> & Cos){
    list<Volum*>::iterator it;
    for(it=Cos.begin();it!=Cos.end();it++)
        cout<<**it<<endl;
    if(Cos.size()==0)
        cout<<"cosul este gol\n";
}

void Optiunea6(list<Volum*> & Cos){
    if(Cos.size()==0)
        cout<<"cosul este gol\n";
    else{
        cout<<"Daca doriti livrare la domiciliu apasati 1, altfel apasati 0\n";
        int x;
        cin>>x;
        if(x){
            float suma=0;
            list<Volum*>::iterator it;
            for(it=Cos.begin();it!=Cos.end();it++){
                suma+=(*it)->pretCuTransport();
                (**it)--;
            }
            cout<<"suma de platit este:"<<suma<<endl;
        }
        else
        {
            float suma=0;
            list<Volum*>::iterator it;
            for(it=Cos.begin();it!=Cos.end();it++){
                suma+=(float)(**it);
                (**it)--;
            }
            cout<<"suma de platit este:"<<suma<<endl;
        }
        Cos.clear();
    }
}

void Optiunea3A(Magazin &M) {
    cout<<"Daca este un volum de proza apasati 1\n"
        <<"Daca este un volum de poezii apasati 2\n"
        <<"Daca este un volum mixt pasati 3\n";
    int x;
    cin>>x;
    Volum *v;
    if(x==1)
        v=new VolumProza;
    if(x==2)
        v=new VolumPoezie;
    if(x==3)
        v=new VolumMixt;
    if(x>=1 && x<=3) {
        cin.get();
        cin>>*v;
        M=M+v;
    } else
        cout<<"Nu ati introdus o obtiune valida\n";

}

void Optiunea4A(Magazin &M) {
    cout<<"introduceti id-ul cartii.";
    int id;
    cin>>id;
    for (int i=0;i<M.size();i++)
        if(M[i]->getId()==id)
            M.stergereVolum(M[i]);
    cout<<"Volumul cu id-ul "<<id<<" a fost eliminat din magazin\n";
}


void Optiunea5A(Magazin &M) {
    cout<<"introduceti id-ul cartii.";
    int id;
    cin>>id;
    if(M.existaId(id)){
        Volum *v;
        for (int i=0;i<M.size();i++)
            if(M[i]->getId()==id)
                v=M[i];
        cout<<"Pt a adauga un nr de exemplare apasati 1\n"
            <<"Pt a modifica statusul volumului apasati 2\n";
        int x;
        cin>>x;
        if(x==1){
            cout<<"introduceti numarul de exemlare: ";
            cin>>x;
            *v= (*v)+x;
        }else
        if(x==2){
            cout<<"introduceti statusu (1 pt disponibil/0 altfel): ";
            cin>>x;
            v->setInStoc((x?true:false));
        }

        //cout<<*v;

        cout<<"Volumul cu id-ul "<<id<<" a fost modificat cu succes \n";
    }else
        cout<<"nu esxista niciun produs cu acest id.\n";
}

int main() {
    Volum *v=new VolumProza("1","1",10,1,0,10,10,"nebunie");
    VolumMixt v2("1","1",10,1,0,10,10,"nebunie",10,"nebunie2",0.1);

    Magazin M;
    M=M+v;
    M.setNume("Ana");
    list<Volum*> Cos;
    int admin=0;
    char chr;
    while(true) {
        if(!admin) {
            Meniu();
            cin >> chr;
            while ((chr < '0' || chr > '6')) {
                cout << "Nu ati introdus o optiune valida." << endl
                     << "Va rog sa introduceti o optiune valida." << endl;
                cin >> chr;
            }
            string parola;
            switch (chr) {
                case '0':
                    cout << "O zi frumoasa in continuare!" << endl;
                    exit(0);
                    break;
                case '1':
                    cout<<"Introduceti parola : ";
                    cin>>parola;
                    if(parola=="parola")
                        admin=1;
                    else
                        cout<<"Parola gresita.\n";
                    break;
                case '2':
                    Optiunea2(M);
                    break;
                case '3':
                    Optiunea3(M,Cos);
                    break;
                case '4':
                    Optiunea4(Cos);
                    break;
                case '5':
                    Optiunea5(Cos);
                    break;
                case '6':
                    Optiunea6(Cos);

                    break;
            }
            cout << "Pentru a continua apasati o tasta." << endl;
            cin >> chr;
            system("cls");
        } else {
            MeniuAdmin();
            cin >> chr;
            while ((chr < '0' || chr >= '6')) {
                cout << "Nu ati introdus o optiune valida." << endl
                     << "Va rog sa introduceti o optiune valida." << endl;
                cin >> chr;
            }
            string parola;
            switch (chr) {
                case '0':
                    cout << "O zi frumoasa in continuare!" << endl;
                    exit(0);
                    break;
                case '1':
                    cout << "O zi frumoasa in continuare!" << endl;
                    admin=0;
                    break;
                case '2':
                    cout<<M<<endl;
                    cout<<"Nr total produse este : "<<M.getNrCarti()<<endl;
                    break;
                case '3':
                    Optiunea3A(M);
                    break;
                case '4':
                    Optiunea4A(M);
                    break;
                case '5':
                    Optiunea5A(M);
                    break;
            }
            cout << "Pentru a continua apasati o tasta." << endl;
            cin >> chr;
            system("cls");
        }
    }

    return 0;
}
