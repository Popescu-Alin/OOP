#include <iostream>
#include <conio.h>
#include <string.h>
#include <time.h>
using namespace std;

///Carte--------------------------------------------------------------------------------------------------
///-------------------------------------------------------------------------------------------------------
class Carte {
private:
    char* numeCarte;
    char* autor;
    float pret;                //pretul cartii
    bool imprumutat;           // daca este sau nu disponibila
    int idCarte;
    char *dataImprumut;         // data la care a fost imprumutata cartea;
    //o carte este imprumutata maxim 14 zile
public:
//constructori
    Carte();
    Carte(char* numeCarte, char* autor);
    Carte(char* numeCarte, char* autor, float pret, bool imprumutat, int idCarte, char* dataImprumut);
//constructor de copiere
    Carte(Carte &c);
//Supraincarcarea operatorului egal pentru obiecte de tip Carte
    Carte& operator =(const Carte& carte);
//suprascrierea operatorului <<
    friend ostream & operator<<(ostream & out, const Carte &c);
//suprascrierea operatorului >>
    friend istream & operator>>(istream &in, Carte &c);
//supraincarcarea operatorului pre-incrementare
    const Carte operator++();
//supraincarcarea operatorului post-incrementare
    const Carte operator++(int);
//supraincarcare ==
    bool operator==(const Carte& c);
//supraincarcare <=
    bool operator<=(const Carte& c);
//supraincarcarea operatorului + pentru float
    Carte operator+(float f);//Carte+float
    friend Carte operator+(float f, Carte c);//float+Carte
//supraincarcarea operatorului * pentru float
    Carte operator*(float f);//Carte*float
    friend Carte operator*(float f, Carte c);//float*Carte
//supraincarcarea operatorului + pentru Carte
    Carte operator + (Carte c);
//supraincarcarea operatorului []
    char operator[](int index);
//cast la float
    explicit operator float() {
        return (float)this->pret;
    }
//seters
    void setImprumutat(bool imprumutat);
    void setNumeCarte( char *numeCarte);
    void setAutor( char *autor);
    void setPret(float pret);
    void setIdCarte(int idCarte);
    void setDataImprumut(char *dataImprumut);
//geters
    bool getImprumutat();
    char* getNumeCarte();
    char* getAutor();
    float getPret();
    int getId();
    char* getDataImprumut();
//alte metode
    void update(char *s,int p);
    //functia returneaza prin s,
    //data calendaristica in care ne aflam dupap zile de la imprumutul cartii
    //p<=31
//destructor
    ~Carte();
};
//constructrs
Carte::Carte() {
    this->numeCarte=new char[strlen("Nu se cunoaste")+1];
    strcpy(this->numeCarte,"Nu se cunoaste");
    this->autor=new char[strlen("Anonim")+1];
    strcpy(this->autor,"Anonim");
    this->pret=0;
    this->imprumutat=false;
    this->idCarte=-1;
    this->dataImprumut=new char[11];
    strcpy(this->dataImprumut,"00/00/0000");
}
Carte::Carte(char* numeCarte, char* autor) {
    this->numeCarte=new char[strlen(numeCarte)+1];
    strcpy(this->numeCarte,numeCarte);
    this->autor=new char[strlen(autor)+1];
    strcpy(this->autor,autor);
    this->pret=0;
    this->imprumutat=false;
    this->idCarte=-1;
    this->dataImprumut=new char[11];
    strcpy(this->dataImprumut,"00/00/0000");
}
Carte::Carte(char* numeCarte, char* autor, float pret, bool imprumutat, int idCarte, char * dataImprumut) {
    this->numeCarte=new char[strlen(numeCarte)+1];
    strcpy(this->numeCarte,numeCarte);
    this->autor=new char[strlen(autor)+1];
    strcpy(this->autor,autor);
    this->pret=pret;
    this->imprumutat=imprumutat;
    this->idCarte=idCarte;
    this->dataImprumut=new char[11];
    strcpy(this->dataImprumut,dataImprumut);
}
//constructor de copiere
Carte::Carte(Carte &c) {
    this->numeCarte=new char[strlen(c.numeCarte)+1];
    strcpy(this->numeCarte,c.numeCarte);
    this->autor=new char[strlen(c.autor)+1];
    strcpy(this->autor,c.autor);
    this->pret=c.pret;
    this->imprumutat=c.imprumutat;
    this->idCarte=c.idCarte;
    this->dataImprumut=new char[11];
    strcpy(this->dataImprumut,c.dataImprumut);
}
//supraincarcarea operatorului = pt clasa carte
Carte& Carte::operator =(const Carte& c) {
    if(this != &c) {
        if(this->numeCarte != NULL)
            delete [] this->numeCarte;

        if(this->autor != NULL)
            delete [] this->autor;

        if(this->dataImprumut)
            delete [] this->dataImprumut;

        this->numeCarte=new char[strlen(c.numeCarte)+1];
        strcpy(this->numeCarte,c.numeCarte);
        this->autor=new char[strlen(c.autor)+1];
        strcpy(this->autor,c.autor);
        this->pret=c.pret;
        this->imprumutat=c.imprumutat;
        this->idCarte=c.idCarte;
        this->dataImprumut=new char[11];
        strcpy(this->dataImprumut,c.dataImprumut);
    }

    return* this;
}
//supraincarcarea operatorului>>
istream & operator>>(istream &in, Carte &c) {
    char s[100];
    if(c.numeCarte)
        delete[] c.numeCarte;
    if(c.autor)
        delete[] c.autor;
    if(c.dataImprumut)
        delete[] c.dataImprumut;

    cout<<"Introduceti numele cartii:";
    in.get(s,100);
    c.numeCarte=new char[strlen(s)+1];
    strcpy(c.numeCarte,s);
    in.get();
    cout<<"Introduceti Autorul :";
    in.get(s,100);
    c.autor=new char[strlen(s)+1];
    strcpy(c.autor,s);
    in.get();
    cout<<"Introduceti amenda instrainare carte :";
    in>>c.pret;
    cout<<"Introduceti status [disponibila(1)/indisponibila(0):";
    in>>c.imprumutat;
    c.imprumutat=!c.imprumutat;
    if(c.imprumutat) {
        in.get();
        cout<<"Introduceti data imprumutarii :";
        in.get(s,100);
        c.dataImprumut=new char[strlen(s)+1];
        strcpy(c.dataImprumut,s);
        in.get();
    }
    c.idCarte=-2;
    in.get();
    return in;
}
//supraincarcarea operatorului<<
ostream & operator<<(ostream & out, const Carte &c) {
    out<<"Numele cartii este: "<<c.numeCarte<<endl;
    out<<"Numele autorului este: "<<c.autor<<endl;
    out<<"Status carte : "<<(c.imprumutat?"indisponibila momentan":"disponibila")<<endl;
    if(c.imprumutat)
        out<<"Data imprumutarii: "<<c.dataImprumut<<endl;
    out<<"Id-ul cartii este:"<<c.idCarte<<endl;
    out<<"Amenda instrainare carte este: "<<c.pret<<endl;
    return out;
}
//supraincarcarea operatorului pre-incrementare
const Carte Carte::operator++() {
    this->pret++;
    return *this;
}
//supraincarcarea operatorului post-incrementare
const Carte Carte::operator++(int) {
    Carte aux(*this);
    this->pret++;
    return aux;
}
//supraincarcare ==;
bool Carte::operator==(const Carte& c) {
    if(strcmp(this->numeCarte,c.numeCarte)==0 && strcmp(this->autor,c.autor)==0)
        return true;
    return false;
}
//supraincarcare <=;
bool Carte::operator<=(const Carte& c) {
    if(strcmp(this->autor,c.autor)<0)
        return true;
    else if(strcmp(this->autor,c.autor)==0 && strcmp(this->numeCarte,c.numeCarte)<=0)
        return true;
    return false;
}
//supraincarcarea operatorului + pentru float
Carte Carte::operator+(float f) { //Carte+float
    Carte aux(*this);
    aux.pret=aux.pret+f;
    return aux;
}
Carte operator+(float f, Carte c) { //float+Carte
    Carte aux(c);
    aux.pret=aux.pret+f;
    return aux;
}
//supraincarcarea operatorului * pentru float
Carte Carte::operator*(float f) { //Carte*float
    Carte aux(*this);
    aux.pret=aux.pret*f;
    return aux;
}
Carte operator*(float f, Carte c) { //float*Carte
    Carte aux(c);
    aux.pret=aux.pret*f;
    return aux;
}
////supraincarcarea operatorului + pentru Carte
Carte Carte::operator+(Carte c) {
    Carte aux;
    char *s=new char[strlen(this->numeCarte)+strlen(c.numeCarte)+10];
    strcpy(s,this->numeCarte);
    strcat(s," & ");
    strcat(s,c.numeCarte);
    aux.setNumeCarte(s);
    delete s;
    s=new char[strlen(this->autor)+strlen(c.autor)+10];
    strcpy(s,this->autor);
    strcat(s," & ");
    strcat(s,c.autor);
    aux.setAutor(s);
    delete s;
    aux.setPret((float)*this + (float)c );
    return aux;
}
//supraincarcarea operatorului []
char Carte::operator[](int index) { // metoda returneaza caracterul de pe pozitia index din numele autorului cartii
    index=index%(strlen(this->autor));
    return this->autor[index];
}
//seters
void Carte::setImprumutat(bool imprumutat) {
    this->imprumutat=imprumutat;
}
void Carte::setNumeCarte( char *numeCarte) {
    if(this->numeCarte)
        delete[] this->numeCarte;
    this->numeCarte= new char[strlen(numeCarte)+1];
    strcpy(this->numeCarte,numeCarte);
}
void Carte::setAutor( char *autor) {
    if(this->autor)
        delete[] this->autor;
    this->autor= new char[strlen(autor)+1];
    strcpy(this->autor,autor);
}
void Carte::setPret(float pret) {
    this->pret=pret;
}
void Carte::setIdCarte(int idCarte) {
    this->idCarte=idCarte;
}
void Carte::setDataImprumut(char *dataImprumut) {
    if(this->dataImprumut)
        delete[] this->dataImprumut;
    this->dataImprumut= new char[strlen(dataImprumut)+1];
    strcpy(this->dataImprumut,dataImprumut);
}
//geters
bool Carte::getImprumutat() {
    return this->imprumutat;
}
char* Carte::getNumeCarte() {
    return this->numeCarte;
}
char* Carte::getAutor() {
    return this->autor;
}
float Carte::getPret() {
    return this->pret;
}
int Carte::getId() {
    return this->idCarte;
}
char* Carte::getDataImprumut() {
    return this->dataImprumut;
}
//destructor
Carte::~Carte() {

    if(this->numeCarte != NULL)
        delete [] this->numeCarte;

    if(this->autor != NULL)
        delete [] this->autor;

    if(this->dataImprumut)
        delete [] this->dataImprumut;
    this->idCarte=0;
    this->imprumutat=false;
    this->pret=0;
}
//alte metode
void Carte::update(char s[],int p ) {//functia primeste un string si un nr si returneaza prin s noua data calendaristica
    int z=atoi(this->dataImprumut),l=atoi(this->dataImprumut+3),a=atoi(this->dataImprumut+6);//transfor din string in int-uri;
    int t=31;  //cate zile sunt in luna
    if(l==1 || l==3 || l==5  || l==7  || l==8  || l==10  || l==12)
        t=32;
    if(l==2)
        if(a%4==0)
            t=30;
        else
            t=29;

    l=l+(z+p)/t;
    z=(z+p)%t;
    a=a+l/12;
    l=l%12;

    s[0]=z/10+'0';
    s[1]=z%10+'0';
    s[2]='/';
    s[3]=l/10+'0';
    s[4]=l%10+'0';
    s[5]='/';
    itoa(a,(s+6),10);
}

///Biblioteca---------------------------------------------------------------------------------------------
///-------------------------------------------------------------------------------------------------------
class Biblioteca {
private:
    string numeBiblioteca;
    Carte *carti;//vector de carti
    int nrCarti;
    int nrMaxCarti;//nr maxim de carti ;
    double mediePreturiCarti;
public:
//constructori
    Biblioteca();
    Biblioteca(string numeBiblioteca, Carte *carti,int nrCarti);
    Biblioteca(string numeBiblioteca,Carte *carti,int nrCarti,int nrMaxCarti,double mediePreturiCarti);
// constructor de copiere
    Biblioteca(Biblioteca &b);
// Supraincarcarea operatorului = pentru obiecte de tip Biblioteca
    Biblioteca& operator =(const Biblioteca& b);

//suprascrierea operatorului <<
    friend ostream & operator<<(ostream & out, const Biblioteca &c);
//suprascrierea operatorului >>
    friend istream & operator>>(istream &in, Biblioteca &c);
//supraincarcarea operatorului pre-incrementare
    const Biblioteca operator++();
//supraincarcarea operatorului post-incrementare
    const Biblioteca operator++(int);
//supraincarcare ==
    bool operator==(const Biblioteca& b);
//supraincarcare <=
    bool operator<=(const Biblioteca& b);
//supraincarcarea operatorului + pentru float
    Biblioteca operator+(float f);//Biblioteca+float
    friend Biblioteca operator+(float f, Biblioteca b);//float+Biblioteca
//supraincarcarea operatorului * pentru float
    Biblioteca operator*(float f);//Biblioteca*float
    friend Biblioteca operator*(float f, Biblioteca b);//float*Biblioteca
//supraincarcarea operatorului + pentru Carte
    Biblioteca operator+(Carte c);//Biblioteca+Carte
    friend Biblioteca operator+(Carte c, Biblioteca b);//Carte+Biblioteca
//supraincarcarea operatorului + pentru Carte
    Biblioteca operator+(Biblioteca b);
//supraincarcarea operatorului []
    Carte operator[](int index);
//cast la double
    explicit operator double() {
        return (double)this->mediePreturiCarti;
    }

//geters
    double getMedie();
    int getNrCarti();
    Carte getCarte(char *autor, char* nume);
    Carte& getCarte(int id);
    string GetNume();
//seters
    void setMedie(double medie);
    void setNume(string nume);
//alte metode
    void sort();
    void adaugaCarte(Carte c);
    void recalculareMedie();
    void updateCarte(Carte toUpdate, Carte updateWith ); // inlocuiesc o carte cu alta carte
    void stergereCarte(Carte c); // sterge cartea c din biblioteca.
    void stergereCarte(int id);
    void afisareCartiDisponibile( char* autor);
    bool existaId(int id);
    int generareId();
//destructor
    ~Biblioteca();
};
//constructors
Biblioteca::Biblioteca() {
    this->numeBiblioteca ="Anonim";
    this->carti=new Carte[10];
    this->nrCarti=0;
    this->nrMaxCarti=10;
    this->mediePreturiCarti=0;
}
Biblioteca::Biblioteca(string numeBiblioteca,Carte *carti,int nrCarti) {
    this->numeBiblioteca =numeBiblioteca;
    this->nrCarti=nrCarti;
    this->nrMaxCarti=nrCarti;
    this->carti=new Carte[this->nrMaxCarti];
    for(int i=0; i<this->nrCarti; i++)
        this->carti[i]=carti[i];
    this->recalculareMedie();
}
Biblioteca::Biblioteca(string numeBiblioteca,Carte *carti,int nrCarti,int nrMaxCarti,double mediePreturiCarti) {
    this->numeBiblioteca=numeBiblioteca;
    this->nrCarti=nrCarti;
    this->nrMaxCarti=nrMaxCarti;
    this->mediePreturiCarti=mediePreturiCarti;
    this->carti=new Carte[this->nrMaxCarti];
    for(int i=0; i<this->nrCarti; i++)
        this->carti[i]=carti[i];
}
// constructor de copiere
Biblioteca::Biblioteca(Biblioteca &b) {
    this->numeBiblioteca=b.numeBiblioteca;
    this->nrCarti=b.nrCarti;
    this->nrMaxCarti=b.nrMaxCarti;
    this->mediePreturiCarti=b.mediePreturiCarti;
    this->carti=new Carte[this->nrMaxCarti];
    for(int i=0; i<this->nrCarti; i++)
        this->carti[i]=b.carti[i];
}
// Supraincarcarea operatorului egal pentru obiecte de tip Biblioteca
Biblioteca& Biblioteca:: operator =(const Biblioteca& b) {
    if(this != &b) {
        if(this->carti)
            delete[] this->carti;
        this->numeBiblioteca=b.numeBiblioteca;
        this->nrCarti=b.nrCarti;
        this->nrMaxCarti=b.nrMaxCarti;
        this->mediePreturiCarti=b.mediePreturiCarti;
        this->carti=new Carte[this->nrMaxCarti];
        for(int i=0; i<this->nrCarti; i++)
            this->carti[i]=b.carti[i];

    }
    return *this;
}
//supraincarcarea operatorului>>
istream & operator>>(istream &in, Biblioteca &b) {
    if(b.carti)
        delete[] b.carti;
    cout<<"Introduceti numele bibliotecii:";
    char s[100];
    in.get(s,100);
    b.numeBiblioteca=s;
    in.get();
    do {
        cout<<"Introduceti numarul de cartii din biblioteca:";
        in>>b.nrCarti;
        if(b.nrCarti<0) {
            cout<<"Nu este permisa introducerea unui nr negativ in acest contex."<<endl;
            cout<<"Va rugam introduceti o valoare pozitiva."<<endl;
        }
    } while(b.nrCarti<0);
    b.nrMaxCarti=b.nrCarti;
    b.carti=new Carte[b.nrCarti];
    in.get();
    for(int i=0; i<b.nrCarti; i++) {
        cout<<"introduceti cartea "<<i+1<<endl;
        in>>b.carti[i];
        cout<<endl;
        in.get();
    }
    in.get();
    return in;
}
//supraincarcarea operatorului<<
ostream & operator<<(ostream & out, const Biblioteca &b) {
    out<<"Numele bibliotecii este: "<<b.numeBiblioteca<<endl;
    out<<"Cele "<<b.nrCarti<<" carti din biblioteca sunt:"<<endl;
    for (int i=0; i<b.nrCarti; i++) {
        out<<"Cartea "<<i+1<<" este:"<<endl<<b.carti[i];
        out<<endl;
    }

    return out;
}
//supraincarcarea operatorului pre-incrementare
const Biblioteca Biblioteca::operator++() {
    for(int i=0; i<this->nrCarti; i++)
        this->carti[i]++;
    this->recalculareMedie();
    return *this;
}
//supraincarcarea operatorului post-incrementare
const Biblioteca Biblioteca::operator++(int) {
    Biblioteca aux(*this);
    for(int i=0; i<this->nrCarti; i++)
        this->carti[i]++;
    this->recalculareMedie();
    return aux;
}
//supraincarcare ==;
bool Biblioteca::operator==(const Biblioteca& b) {
    if( this->nrCarti != b.nrCarti)
        return false;
    for(int i=0; i<this->nrCarti; i++)
        if(!(this->carti[i]==b.carti[i]))
            return false;
    return true;
}
//supraincarcare <=;
bool Biblioteca::operator<=(const Biblioteca& b) {
    if( this->nrCarti > b.nrCarti)
        return false;
    return true;
}
//supraincarcarea operatorului + pentru float
Biblioteca Biblioteca::operator+(float f) { //Biblioteca+float
    Biblioteca aux(*this);
    for (int i=0; i<aux.nrCarti; i++)
        aux.carti[i]=aux.carti[i]+f;
    aux.recalculareMedie();
    return aux;
}
Biblioteca operator+(float f, Biblioteca b) { //float+Biblioteca
    Biblioteca aux(b);
    for (int i=0; i<aux.nrCarti; i++)
        aux.carti[i]=aux.carti[i]+f;
    aux.recalculareMedie();
    return aux;
}
//supraincarcarea operatorului * pentru float
Biblioteca Biblioteca::operator*(float f) { //Biblioteca*float
    Biblioteca aux(*this);
    for (int i=0; i<aux.nrCarti; i++)
        aux.carti[i]=aux.carti[i]*f;
    aux.recalculareMedie();
    return aux;
}
Biblioteca operator*(float f, Biblioteca b) { //float*Biblioteca
    Biblioteca aux(b);
    for (int i=0; i<aux.nrCarti; i++)
        aux.carti[i]=aux.carti[i]*f;
    aux.recalculareMedie();
    return aux;
}
//supraincarcarea operatorului + pentru Carte
Biblioteca Biblioteca::operator+(Carte c) { //Biblioteca+Carte
    Biblioteca aux(*this);
    aux.adaugaCarte(c);
    return aux;
}
Biblioteca operator+(Carte c, Biblioteca b) { //Carte+Biblioteca
    Biblioteca aux(b);
    aux.adaugaCarte(c);
    return aux;
}
//supraincarcarea operatorului + pentru Carte
Biblioteca Biblioteca::operator+(Biblioteca b) {
    Biblioteca aux(*this);
    for(int i =0; i<b.nrCarti; i++) {
        Carte c=b.carti[i];
        c.setImprumutat(false);
        aux=aux + c;
    };
    return aux;
}
//supraincarcarea operatorului []
Carte Biblioteca::operator[](int index) { // metoda returneaza cartea de pe pozitia index din biblioteca
    index=index%(this->nrCarti);
    return this->carti[index];
}
//setres
void Biblioteca::setMedie( double x) {
    this->mediePreturiCarti=x;
}
void Biblioteca::setNume(string nume) {
    this->numeBiblioteca=nume;
}
//geters
double Biblioteca::getMedie() {
    return this->mediePreturiCarti;
}
string Biblioteca::GetNume() {
    return this->numeBiblioteca;
}
int Biblioteca::getNrCarti() {
    return this->nrCarti;
}
Carte Biblioteca::getCarte(char* autor,char *nume) { // returneaza cartea care are numele si autorul specificat
    for(int i=0; i<this->nrCarti; i++)
        if(strcmp(this->carti[i].getNumeCarte(),nume)==0 && strcmp(this->carti[i].getAutor(),autor)==0)
            return this->carti[i];

    Carte c;
    return c;
}
Carte& Biblioteca::getCarte(int id) {// returneaza o carte care are id ul id
    for(int i=0; i<this->nrCarti; i++)
        if(this->carti[i].getId()==id)
            return this->carti[i];
}
//alte metode
void Biblioteca::sort() {   // sorteaza carile din biblioteca dupa autor si nume
    int sem;
    do {
        sem=1;
        for(int i=0; i<this->nrCarti-1; i++)
            if(!(this->carti[i]<=this->carti[i+1])) {
                sem=0;
                Carte c=this->carti[i];
                this->carti[i]=this->carti[i+1];
                this->carti[i+1]=c;
            }
    } while(sem==0);
}
void Biblioteca::adaugaCarte(Carte c) {
    c.setIdCarte(this->generareId());
    if(this->nrCarti<this->nrMaxCarti)
        this->carti[nrCarti++]=c;
    else {
        this->nrMaxCarti+=10;// cresc dimensiunea maxima a vectorului
        Carte *Vt=new Carte[this->nrMaxCarti]; // fac un vector temporal;

        for (int i=0; i<this->nrCarti; i++) //copiez in vectorul temporla vectorul de carti
            Vt[i]=this->carti[i];

        delete[] this->carti;     // sterg vectorul de carti;

        this->carti=new Carte[this->nrMaxCarti]; //maresc dimensiunea vectorului

        for (int i=0; i<this->nrCarti; i++) //copiez din vt in carti
            this->carti[i]=Vt[i];

        this->carti[nrCarti++]=c; // adaug cartea;
        delete[] Vt;
    }
    this->recalculareMedie();

}
void Biblioteca::recalculareMedie() {// recalculeaza media amenzilor
    float s=0;
    for(int i=0; i<this->nrCarti; i++)
        s=s+this->carti[i].getPret();
    if(this->nrCarti>0)
        this->mediePreturiCarti=s/this->nrCarti;
    else
        this->mediePreturiCarti=0;
}
void Biblioteca::updateCarte(Carte toUpdate, Carte updateWith ) { //inlocuieste o carte cu alta care
    for(int i=0; i<this->nrCarti; i++)
        if(this->carti[i]==toUpdate) {
            this->carti[i]=updateWith;
            break;
        }
}
void Biblioteca::stergereCarte(Carte c) {//sterge o carte
    for(int i=0; i<this->nrCarti; i++)
        if(this->carti[i]==c) {
            for(int j=i+1; j<nrCarti; j++)
                this->carti[j-1]=this->carti[j];
            this->nrCarti--;
            break;
        }
}
void Biblioteca::stergereCarte(int id) {// sterge o caite dupa id
    for(int i=0; i<this->nrCarti; i++)
        if(this->carti[i].getId()==id) {
            for(int j=i+1; j<nrCarti; j++)
                this->carti[j-1]=this->carti[j];
            this->nrCarti--;
            break;
        }
}
void Biblioteca::afisareCartiDisponibile(char *autor="") { // metoda afiseza toate cartile disponibile (optional care au un anumit autor).
    for(int i=0; i<this->nrCarti; i++)
        if(this->carti[i].getImprumutat()==false && (strcmp(autor,"")==0 || strcmp(this->carti[i].getAutor(),autor)==0))
            cout<<this->carti[i]<<endl;
}
bool Biblioteca::existaId(int id) {
    for (int i=0; i<=this->nrCarti; i++)
        if(this->carti[i].getId()==id)
            return true;
    return false;
}
int Biblioteca::generareId() { //functia genereaza un id nou, care nu a mai fost atribuit unei alte carti.
    int id;
    do {
        id=abs(rand())+10;       //id ul trebuie sa aiba cel putin 2 cifre
    } while(this->existaId(id));
    return id;
}
//destructor
Biblioteca::~Biblioteca() {
    if(this->carti)
        delete [] this->carti;
    this->numeBiblioteca="";
    this->nrCarti=0;
    this->nrMaxCarti=0;
    this->mediePreturiCarti=0;
}

///Abonament----------------------------------------------------------------------------------------------
///-------------------------------------------------------------------------------------------------------

class Abonament {
private:
    char* nume;
    string prenume;
    char initialaTata;
    int nrLuni;
    int nrCartiPierdute;
    int *nrCartiPerLuna;
    Carte *c; //un client poate imprumuta o carte la un momendat, daca nu a returnato nu poate imprumuta alta.
    const int idAbonament;          // fiecare abonamnet va avea un id propriu.
    static int total;               // nr total de abonamnete create.
public:
//constructori
    Abonament();
    Abonament(char* nume, string prenume, char initialaTata);
    Abonament(char* nume, string prenume, char initialaTata, int nrLuni, int *nrCartiPerLuna,int nrCartiPierdute,Carte c );
//copy-const
    Abonament(const Abonament& a);
// supraincarcare operatori >>
    friend istream & operator>>(istream &in, Abonament &a);
// supraincarcare operatori <<
    friend ostream & operator<<(ostream & out, const Abonament &a);
// supraincarcare operator =
    Abonament& operator = (const Abonament& a);
//supraincarcarea operatorului pre-incrementare
    const Abonament operator++();
//supraincarcarea operatorului post-incrementare
    const Abonament operator++(int);
//supraincarcare ==
    bool operator==(const Abonament& a);
//supraincarcare <=
    bool operator<=(const Abonament& a);
//supraincarcarea operatorului + pentru int
    Abonament operator+(int f);//Abonament+int
    friend Abonament operator+(int f, Abonament c);//int+Abonament
//supraincarcarea operatorului * pentru int
    Abonament operator*(int f);//Abonament*int
    friend Abonament operator*(int f, Abonament a);//int*Abonament
//supraincarcarea operatorului []
    int operator[](int index);
//cast la double
    explicit operator int() {
        return (int)this->nrCartiPierdute;
    }
//seters
    static void setTotal(int i);
    void setNume( char *nume);
    void setPrenume( string prenume);
    void setInitialaTata(char c);
    void setNrCartiPerLuna( int* nrCartiPerLuna);
    void setCarte(Carte c);
    void setNrCartiPierdute(int i);

//geters
    Carte& getCarte();
    int getidAbonament();
    char* getNume();
    string getPrenume();
    char getInitialaTata();
    int* getNrCariPerLuna();
    int getNrLuni();
    int getNrCariPierdute();
    static int getTotal();
//Alte metode
    void addLuna(int x);
    double calculeazaAmenda();
    void upDateLuna(int index, int valoare);
//Destructor
    ~Abonament();
};
//constructor
Abonament::Abonament():idAbonament(++total) {
    this->nume=new char[strlen("Anonim")+1];
    strcpy(this->nume,"Anonim");
    this->prenume="Anonim";
    this->initialaTata='?';
    this->nrLuni=1;
    this->nrCartiPerLuna=new int[this->nrLuni];
    this->nrCartiPerLuna[0]=0;
    this->nrCartiPierdute=0;
    this->c=new Carte;


}
Abonament::Abonament(char* nume, string prenume, char initialaTata):idAbonament(++total) {
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->prenume=prenume;
    this->initialaTata=initialaTata;
    this->nrLuni=1;
    this->nrCartiPerLuna=new int[this->nrLuni];
    this->nrCartiPerLuna[0]=0;
    this->nrCartiPierdute=0;
    this->c=new Carte;

}
Abonament::Abonament(char* nume, string prenume, char initialaTata, int nrLuni,
                     int *nrCartiPerLuna, int nrCartiPierdute, Carte c):idAbonament(++total) {
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->prenume=prenume;
    this->initialaTata=initialaTata;
    this->nrLuni=nrLuni;
    this->nrCartiPerLuna=new int[this->nrLuni];
    for (int i=0; i<nrLuni; i++)
        this->nrCartiPerLuna[i]=nrCartiPerLuna[i];
    this->nrCartiPierdute=nrCartiPierdute;
    this->c=new Carte;
    *this->c=c;
}
//copy const
Abonament::Abonament(const Abonament& a):idAbonament(a.idAbonament) {
    this->nume=new char[strlen(a.nume)+1];
    strcpy(this->nume,a.nume);
    this->prenume=a.prenume;
    this->initialaTata=a.initialaTata;
    this->nrLuni=a.nrLuni;
    this->nrCartiPerLuna=new int[this->nrLuni];
    for (int i=0; i<nrLuni; i++)
        this->nrCartiPerLuna[i]=a.nrCartiPerLuna[i];
    this->nrCartiPierdute=a.nrCartiPierdute;
    this->c=new Carte;
    this->c=a.c;
}
//suprainrcarea operator =
Abonament& Abonament::operator =(const Abonament& a) {
    if(this != &a) {
        if(this->nume!= NULL)
            delete [] this->nume;
        if(this->nrCartiPerLuna !=NULL)
            delete [] this->nrCartiPerLuna;
        this->nume=new char[strlen(a.nume)+1];
        strcpy(this->nume,a.nume);
        this->prenume=a.prenume;
        this->initialaTata=a.initialaTata;
        this->nrLuni=a.nrLuni;
        this->nrCartiPerLuna=new int[this->nrLuni];
        for (int i=0; i<nrLuni; i++)
            this->nrCartiPerLuna[i]=a.nrCartiPerLuna[i];
        this->nrCartiPierdute=a.nrCartiPierdute;
        this->c[0]=a.c[0];
    }

    return* this;
}
//supraincarcarea lui >>
istream & operator>>(istream &in, Abonament &a) {
    char s[100];
    if(a.nume)
        delete[] a.nume;
    if(a.nrCartiPerLuna)
        delete[] a.nrCartiPerLuna;

    cout<<"Introduceti numele :";
    in.get(s,100);
    a.nume=new char[strlen(s)+1];
    strcpy(a.nume,s);
    in.get();

    cout<<"Introduceti prenumele :";
    in>>a.prenume;
    in.get();
    cout<<"Introduceti initiala tatalui :";
    in>>a.initialaTata;
    a.nrLuni=1;
    a.nrCartiPerLuna=new int[a.nrLuni];
    for (int i=0; i<a.nrLuni; i++)
        a.nrCartiPerLuna[i]=0;
    a.nrCartiPierdute=0;
    Carte ct;
    *a.c=ct;
    in.get();
    return in;
}
//supraincarcarea lui <<
ostream & operator<<(ostream & out, const Abonament &a) {
    out<<"Id-ul abonamentului este:"<<a.idAbonament<<endl;
    out<<"Numele este: "<<a.nume<<endl;
    out<<"Prenumele este: "<<a.prenume<<endl;
    out<<"Initiala Tatalui este: "<<a.initialaTata<<endl;
    out<<"Numarul de carti imprumutate in fiecare luna este:"<<endl;
    for(int i=0; i<a.nrLuni; i++)
        out<<"  In luna "<<i+1<<" a imprumutat "<<a.nrCartiPerLuna[i]<<" carti"<<endl;
    out<<"Nr de carti pierdute este: "<<a.nrCartiPierdute<<endl;

    if(!(-1==a.c[0].getId()))
        out<<"Ultima carte nereturnata este:"<<endl<<a.c[0];
    return out;
}
//supraincarcarea operatorului pre-incrementare
const Abonament Abonament::operator++() {
    this->nrCartiPierdute++;
    return *this;
}
//supraincarcarea operatorului post-incrementare
const Abonament Abonament::operator++(int) {
    Abonament aux(*this);
    this->nrCartiPierdute++;
    return aux;
}
//supraincarcare ==;
bool Abonament::operator==(const Abonament& a) {
    return (strcmp(this->nume,a.nume)==0 && this->prenume==a.prenume && this->initialaTata==a.initialaTata);
}
//supraincarcare <=;
bool Abonament::operator<=(const Abonament& a) {
    if(strcmp(this->nume,a.nume)<0)
        return true;
    else if(strcmp(this->nume,a.nume)==0 && this->prenume<a.prenume)
        return true;
    else if(strcmp(this->nume,a.nume)==0 && this->prenume==a.prenume && this->initialaTata<=a.initialaTata)
        return true;

    return false;
}
//supraincarcarea operatorului + pentru int
Abonament Abonament::operator+(int f) {//Abonament+int
    Abonament aux(*this);
    Carte c=aux.getCarte();
    aux.nrCartiPierdute=aux.nrCartiPierdute+f;
    aux.setCarte(c);
    return aux;
}
Abonament operator+(int f,const Abonament a) { //int+Carte
    Abonament aux=a;
    Carte c=aux.getCarte();
    aux.nrCartiPierdute=aux.nrCartiPierdute+f;
    aux.setCarte(c);
    return aux;
}
//supraincarcarea operatorului * pentru int
Abonament Abonament::operator*(int f) { //Abonament*int
    Abonament aux(*this);
    Carte c=aux.getCarte();
    aux.nrCartiPierdute=aux.nrCartiPierdute*f;
    aux.setCarte(c);
    return aux;
}
Abonament operator*(int f, Abonament a) { //int*Abonament , mareste nr de carti pierdute de f ori
    Abonament aux=a;
    Carte c=aux.getCarte();
    aux.nrCartiPierdute=aux.nrCartiPierdute*f;
    aux.setCarte(c);
    return aux;
}
//supraincarcarea operatorului []
int Abonament::operator[](int index) { // metoda returneaza nr de carti din luna index
    index=index%(this->nrLuni);
    return this->nrCartiPerLuna[index];
}
//seters
void Abonament::setCarte(Carte c) {
    *this->c=c;
}
void Abonament::setTotal(int i) {
    Abonament::total=i;
}
void Abonament::setNume( char *nume) {
    if (this->nume!=NULL)
        delete[] this->nume;
    this->nume= new char[strlen(nume)+1];
    strcpy(this->nume,nume);
}
void Abonament::setPrenume( string prenume) {
    this->prenume= prenume;
}
void Abonament::setInitialaTata(char c) {
    this->initialaTata=c;
}
void Abonament::setNrCartiPerLuna(int *nrCartiPerLuna) { //metoda modifica primele min(nrLuni,lungime vector dat) valori din vector;
    int t=sizeof(nrCartiPerLuna)/sizeof(*nrCartiPerLuna);
    if(t>(this->nrLuni));
    t=this->nrLuni;
    for (int i=0; i<t; i++)
        this->nrCartiPerLuna[i]=nrCartiPerLuna[i];
}
void Abonament::setNrCartiPierdute(int i) {
    this->nrCartiPierdute=i;
}
//geteres
Carte& Abonament::getCarte() {
    return this->c[0];
}
int Abonament::getidAbonament() {
    return idAbonament;
}
string Abonament::getPrenume() {
    return this->prenume;
}
char* Abonament::getNume() {
    return this->nume;
}
char Abonament::getInitialaTata() {
    return this->initialaTata;
}
int* Abonament::getNrCariPerLuna() {
    return this->nrCartiPerLuna;
}
int Abonament::getNrLuni() {
    return nrLuni;
}
int Abonament::getTotal() {
    return Abonament::total;
}
int Abonament::getNrCariPierdute() {
    return this->nrCartiPierdute;
}
//alte metode
void Abonament::addLuna(int x) { // metoda creste dimensiunea vectorului de luni si adauga la final valoare x
    int *vt=new int[this->nrLuni];
    for(int i=0; i<this->nrLuni; i++)
        vt[i]=this->nrCartiPerLuna[i];
    delete [] this->nrCartiPerLuna;
    this->nrCartiPerLuna= new int[this->nrLuni+1];
    for(int i=0; i<this->nrLuni; i++)
        this->nrCartiPerLuna[i]=vt[i];
    this->nrCartiPerLuna[this->nrLuni++]=x;


}
double Abonament::calculeazaAmenda() {// calculeaza amenda in caz de pierdere a unei carti,in functie de nr de carti pe care le a pierdut.
    if(this->nrCartiPierdute>=3)
        return this->c->getPret();
    else
        return (this->c->getPret()) * (7+nrCartiPierdute)/10;;
}
void Abonament::upDateLuna(int index, int valoare) {// inlocuieste o valoare din vector cu alta valoare
    if(index>=1 && index<=this->nrLuni)
        this->nrCartiPerLuna[index-1]=valoare;
}
//destructo
Abonament::~Abonament() {
    if(this->nume)
        delete [] this->nume;
    if(this->nrCartiPerLuna)
        delete [] this->nrCartiPerLuna;
    this->initialaTata=0;
    this->nrLuni=0;
    this->prenume="";
}

///Plangere----------------------------------------------------------------------------------------------
///-------------------------------------------------------------------------------------------------------

class Plangere {
private:
    string numePrenume;
    int problema;
    int idCarte;
    int nrZile;// nr de zile care au trecut de la depunerea plangerii=)
    bool evaluat;
public:
    //constructori
    Plangere();
    Plangere(string numePrenume, int idCarte, int problema);
    Plangere(string numePrenume, int idCarte, int problema,int nrZile, bool evaluat);
// constructor de copiere
    Plangere(Plangere &b);
// Supraincarcarea operatorului = pentru obiecte de tip Plangere
    Plangere& operator =(const Plangere& r);

//suprascrierea operatorului <<
    friend ostream & operator<<(ostream & out, const Plangere& r);
//suprascrierea operatorului >>
    friend istream & operator>>(istream &in, Plangere& r);
//supraincarcarea operatorului pre-incrementare
    const Plangere operator++();
//supraincarcarea operatorului post-incrementare
    const Plangere operator++(int);
//supraincarcare ==
    bool operator==(const Plangere& r);
//supraincarcare <=
    bool operator<=(const Plangere& r);
//supraincarcarea operatorului + pentru int
    Plangere operator+(int f);//Plangere+int
    friend Plangere operator+(int f, Plangere c);//int+Plangere
//supraincarcarea operatorului * pentru int
    Plangere operator*(int f);//Plangere*int
    friend Plangere operator*(int f, Plangere c);//int*Plangere
//supraincarcarea operatorului []
    char operator[](int index);
//cast la int
    explicit operator int() {
        return (int)this->nrZile;
    }
//geters
    string getNumePrenume();
    bool getEvaluat();
    int getProblema();
    int getIdCarte();
//setres
    void setEvaluat(bool evaluat);
//alte metode
    double calculProcentScadereAmenda();
//destructor
    ~Plangere();
};
//constructors:
//fara parametri
Plangere::Plangere() {
    this->numePrenume ="Anonim";
    this->idCarte=-1;
    this->problema=-1;
    this->evaluat=false;
    this->nrZile=0;
}
//cu 3 parametrii
Plangere::Plangere(string numePrenume, int idCarte, int problema) {
    this->numePrenume =numePrenume;
    this->idCarte=idCarte;
    this->problema=problema;
    this->nrZile=0;
    this->evaluat=false;
}
//cu toti parametrii
Plangere::Plangere(string numePrenume, int idCarte, int problema, int nrZile,bool evaluat) {
    this->numePrenume =numePrenume;
    this->idCarte=idCarte;
    this->problema=problema;
    this->nrZile=nrZile;
    this->evaluat=evaluat;
}
// constructor de copiere
Plangere::Plangere(Plangere &p) {
    this->numePrenume =p.numePrenume;
    this->idCarte=p.idCarte;
    this->problema=p.problema;
    this->nrZile=p.nrZile;
    this->evaluat=p.evaluat;
}

// Supraincarcarea operatorului egal pentru obiecte de tip Biblioteca
Plangere& Plangere:: operator =(const Plangere& p) {
    if(this != &p) {
        this->numePrenume =p.numePrenume;
        this->idCarte=p.idCarte;
        this->problema=p.problema;
        this->evaluat=p.evaluat;
        this->nrZile=p.nrZile;
    }
    return *this;
}
//supraincarcarea operatorului>>
istream & operator>>(istream &in, Plangere &r) {
    cout<<"Introduceti numele : ";
    char s[100];
    in.get(s,100);
    in.get();
    r.numePrenume=s;
    cout<<"Introduceti id-ul cartii: ";
    in>>r.idCarte;
    cout<<"Introduceti id-ul problemei:";
    in>>r.problema;
    in.get();
    r.nrZile=0;
    r.evaluat=false;
    return in;
}
//supraincarcarea operatorului<<
ostream & operator<<(ostream & out, const Plangere &p) {
    out<<"Numele persoanei este: "<<p.numePrenume<<endl;
    out<<"Id-ul cartii este: "<<p.idCarte<<endl;
    out<<"Id-ul problemei: "<<p.problema<<endl;
    out<<"Statusul plangerii : "<<(p.evaluat?"evaluat":"neevaluat")<<endl;
    if(!p.evaluat)
        out<<"Numar de zile de la depunerea plangerii :"<<p.nrZile<<endl;

    return out;
}
//supraincarcarea operatorului pre-incrementare
const Plangere Plangere::operator++() {
    this->nrZile++;
    return *this;
}
//supraincarcarea operatorului post-incrementare
const Plangere Plangere::operator++(int) {
    Plangere aux(*this);
    this->nrZile++;
    return aux;
}
//supraincarcare ==;
bool Plangere::operator==(const Plangere& p) {
    if( this->idCarte == p.idCarte && this->problema==p.problema)
        return true;
    return false;
}
//supraincarcare <=;
bool Plangere::operator<=(const Plangere& p) {
    if( this->problema<=p.problema)
        return true;
    return false;
}
//supraincarcarea operatorului + pentru int
Plangere Plangere::operator+(int f) { //Plangere+int adauga un nr intreg f la nr de zile
    Plangere aux(*this);
    aux.nrZile+=f;
    return aux;
}
Plangere operator+(int f, Plangere p) { //int+Plangere
    Plangere aux(p);
    aux.nrZile=aux.nrZile +f;
    return aux;
}
//supraincarcarea operatorului * pentru int
Plangere Plangere::operator*(int f) { //Plangere*int
    Plangere aux(*this);
    aux.nrZile*=f;
    return aux;
}
Plangere operator*(int f, Plangere p) { //int*Plangere
    Plangere aux(p);
    aux.nrZile*=f;
    return aux;
}
//supraincarcarea operatorului []
char Plangere::operator[](int index) { // metoda returneaza caracterul de pe poz c din numePrenume
    index=index%(this->numePrenume.size());
    return this->numePrenume[index];
}
//seters
void Plangere::setEvaluat(bool evaluat) {
    this->evaluat=evaluat;
}
//getres
bool Plangere::getEvaluat() {
    return this->evaluat;
}
string Plangere::getNumePrenume() {
    return this->numePrenume;
}
int Plangere::getProblema() {
    return this->problema;
}
int Plangere::getIdCarte(){
    return this->idCarte;
}
//alte metode
double Plangere::calculProcentScadereAmenda() {// in fuctie de problema , metoda returneaza procentul care ar trebui scazut din amenda  asociata cartii.
    switch (this->problema) {
    case 1:
        return 0.15;
        break;
    case 2:
        return 0.35;
        break;
    case 3:
        return 0.45;
        break;
    case 4:
        return 0.10;
        break;
    default:
        return 0;
        break;

    }
}
//destructor
Plangere::~Plangere() {
    this->numePrenume ="";
    this->idCarte=-1;
    this->problema=0;
    this->nrZile=0;
    this->evaluat=false;
}

int Abonament::total=1;

int Apartine(Abonament *V,int nrAbon, Abonament& a) { //verific daca exista abonamentu a in V
    for(int i=0; i<nrAbon; i++)
        if(V[i]==a)
            return i;
    return -1;
}
bool Apartine(Plangere *P,int n, Plangere p) {// verific daca exista plangerea p in P
    for(int i=0; i<n; i++)
        if(P[i]==p)
            return 1;
    return 0;
}
void Stergete(Abonament *&V,int &nrAbon, int p) {// sterg un abonament a, daca exista.
    for(int i=p+1; i<nrAbon; i++)
        V[i-1]=V[i];
    nrAbon--;
}
void AfisarePlangeri(Plangere *P, int n) {
    for(int i=0; i<n; i++)
        cout<<P[i]<<endl;
}
void AfisisareAbonamente(Abonament *V,int n) {
    for(int i=0; i<n; i++)
        cout<<V[i]<<endl;
}
void Optiunea0(Abonament *&V, int &nrAbonamente, int &nrMaxAbonamente, int &curent) {
    Abonament a;
    cout<<"Pentru a va crea abonamnetu va rugam introduceti toate datele cerute mai jos."<<endl;
    cin.get();
    cin>>a;
    cout<<endl;
    if(Apartine(V,nrAbonamente,a)!=-1) {
        cout<<"Acest abonamnet exista deja."<<endl;
        curent=-1;
    } else {
        if(nrAbonamente<nrMaxAbonamente)
            V[nrAbonamente++]=a;
        else {
            nrMaxAbonamente+=100;// cresc dimensiunea maxima a vectorului
            Abonament *Vt=new Abonament[nrAbonamente]; // fac un vector temporal;

            for (int i=0; i<nrAbonamente; i++) //copiez in vectorul temporla vectorul de carti
                Vt[i]=V[i];

            delete[] V;     // sterg vectorul de carti;

            V=new Abonament[nrMaxAbonamente]; //maresc dimensiunea vectorului

            for (int i=0; i<nrAbonamente; i++)//copiez din vt in carti
                V[i]=Vt[i];

            V[nrAbonamente++]=a; // adaug cartea;
            delete[] Vt;
        }
        curent=nrAbonamente-1;
        cout<<"Va multumimi ca ati ales biblioteca noastra."<<endl;
    }
}
void Optiunea1(Abonament V[], int &nrAbonamente, int &curent) {
    Abonament a;

    cout<<"Va rugam introduceti toate datele cerute mai jos pentru a va putea conecta."<<endl;
    cin.get();
    cin>>a;
    cout<<endl;
    int i=Apartine(V,nrAbonamente,a);
    if(i!=-1) {
        curent=i;
        cout<<"Bine ai revenit "<<V[curent].getPrenume()<<"!"<<endl;

    } else {
        cout<<"Ne pare rau, acest abonamnet nu exista."<<endl;
        curent=-1;
    }
}
void Optiunea2(Abonament V[], int &nrAbonamente, int &curent) {
    if(curent!=-1 ) {
        if(V[curent].getCarte().getId()==-1) {
            cout<<"Sunteti sigur ca coriti sa stergeti abonamentu?"<<endl
                <<"Apasati tasta 1 penru a il sterge sau 0 pentru a anula stergerea abonamentului!"<<endl;
            char c;
            cin>>c;
            if(c=='1') {
                cout<<"Contul a fost sters.  :( "<<endl;
                Stergete(V,nrAbonamente,curent);
                curent=-1;
            } else
                cout<<"Cererea de stergere de cont a fost anulata."<<endl;
        } else
            cout<<"Nu puteti sterge contul pana nu returnati toate cartile."<<endl;
    } else
        cout<<"Nu s a putut efectua stergerea. Nu sunteti conectat cu niciun cont."<<endl;

}
void Optiunea3(Biblioteca &b, Abonament &a ) {
    //------------------------------------------------------------------------------------------|
    time_t theTime = time(NULL);                                                 //             |
    struct tm *aTime = localtime(&theTime);                                      //             |
    int z = aTime->tm_mday;       //                                                            | preluat de pe https://stackoverflow.com/questions/8343676/how-to-get-current-date-and-time
    int l = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept          |
    int an = aTime->tm_year + 1900; // Year is # years since 1900                               |
    //------------------------------------------------------------------------------------------|
    char t[11];
    t[0]=z/10+'0';
    t[1]=z%10+'0';
    t[2]='/';
    t[3]=l/10+'0';
    t[4]=l%10+'0';
    t[5]='/';
    itoa(an,(t+6),10);// data curenta intr un string.

    if(a.getCarte().getId()!=-1) {
        cout<<"Nu puteti imprumuta o alta carte pana nu returnati ultima carte imprumutata.\n";
        return;
    }
    cout<<"Introduceti id-ul cartii\n";
    cout<<"Daca nu stiti id-ul cartii introduceti 1 (Aceasta actiune va permite sa recautati cartea) altfel introduceti un id \n";
    int id;
    cin>>id;
    cin.get();
    if(id==1) {
        char s[100];
        cout<<"Va rugam introduceti numele autorului cartii:"<<endl;
        cin.get(s,100);
        cin.get();
        system("cls");
        cout<<"Cartile cerute sunt :"<<endl;
        b.afisareCartiDisponibile(s);
        cout<<"Daca doriti sa imprumutati o carte introduceti id-ul carii, altfel  apsati 1. \n";
        cin>>id;
        if(id==1) {
            cout<<"Ne pare rau ca nu ati gasit cartea pe care o doreati :(\n";
            return;
        }
    }

    int sem=1;
    while(sem) {
        if(b.existaId(id)) {
            if(b.getCarte(id).getImprumutat()==false) {
                Carte &c=b.getCarte(id);
                c.setDataImprumut(t);
                c.setImprumutat(true);
                a.setCarte(c);
                int *v=a.getNrCariPerLuna();
                int size=a.getNrLuni();
                v[size-1]++;

                cout<<"Carte a fost imprumutata cu succes!\n";
                break;
            } else {
                cout<<"Acesta carte nu este disponibila momentan.\n";
                char s[20];
                b.getCarte(id).update(s,15);
                cout<<"Ea va fi disponibila incepand cu data de "<<s<<endl;
            }
        } else
            cout<<"Nu exista nicio carte cu aste id.\n";
        cout<<"Daca doriti sa introduceti alt id apasati 1, altfel 0.\n";
        cin>>sem;
        if(sem) {
            cout<<"Introduceti id-ul cartii\n";
            cin>>id;
        }
    }
}
void Optiunea4(Biblioteca &b, Abonament &a) {
    if(a.getCarte().getId()!=-1) {
        cout<<"Daca doriti sa returnati cartea apasati tasta 1.\n";
        cout<<"Daca ati pierdut cartea va rugam apasati 0.\n";
        int x;
        cin>>x;
        if(x==1) {
            cout<<"Cartea a fost returnata cu succes. Va multumim!\n";
            if(b.existaId(a.getCarte().getId())) {
                Carte &c=b.getCarte(a.getCarte().getId());
                c.setImprumutat(false);
            }
            a.getCarte().setIdCarte(-1);
        } else {
            cout<<"Ne pare rau, sunteti nevoit sa platiti o amenda in valoare de "<<a.calculeazaAmenda()<<" lei\n";
            b.stergereCarte(a.getCarte().getId());
            a.getCarte().setIdCarte(-1);
            a++;
        }
    } else
        cout<<"Nu puteti restitui carte deoarece nu ati imprumutat nicio carte momentan.\n";
}
void Optiunea5(Biblioteca B) {
    cout<<"Cartile care sunt disponibile astazi sunt urmatoarele : "<<endl;
    B.afisareCartiDisponibile();
    cout<<endl;
    cout<<"Pentru o cautare avansata apasti tasta 1, altfel apasati 0:"<<endl;
    bool ok;
    cin>>ok;
    cin.get();
    if(ok) {
        cout<<"Pentru a cauta carile dispoibile ale unui anumit autor, apasati 1"<<endl;
        cout<<"Pentru a cauta carile dispoibile la o anumita data, apasati 2"<<endl;
        int op;
        cin>>op;
        if(op==1) {
            char s[100];
            cout<<"Intorduceti numele autorului"<<endl;
            cin.get();
            cin.get(s,100);
            cin.get();
            system("cls");
            cout<<"Cartile cerute sunt :"<<endl;
            B.afisareCartiDisponibile(s);
        }
        if(op==2) {
            char s[100];
            cout<<"Intorduceti data( de forma dd/mm/yyyy)."<<endl;
            cin.get();
            cin.get(s,100);
            cin.get();
            system("cls");
            cout<<"Cartile cerute sunt :"<<endl;
            for(int i=0; i<B.getNrCarti(); i++) {
                char t[12];
                B[i].update(t,15);
                if(!B[i].getImprumutat() || strcmp(s,t)>=0)
                    cout<<B[i];
                cout<<endl;
            }
        }
    }
}
void Optiuneat7(Plangere *&P, int &nrPlangeri,int &nrMaxPlangeri, Abonament a) {// deoarece fac modificari si la nivel de pointer trimit referinta pointerului.
    cout<<"+-----SubMeniu---------------------------------------------------------+\n";
    cout<<"|Raporteaza o poblema in legatura cu cartea pe care ati imprumutat-o   |\n"
        <<"|Daca cartea este murdara apasati 1.                                   |\n"
        <<"|Daca cartea este deteriorata apasati 2.                               |\n"
        <<"|Daca cartea are pagini lipsa apsati 3.                                |\n"
        <<"|Daca exista o alta problema apasati 4.                                |\n"
        <<"+----------------------------------------------------------------------+\n";
    int c;
    cin>>c;
    while(c<1 || c>4) {
        cout<<"Va rugam sa introduceti una din cele 4 posibilitati.\n Va multumim!\n";
        cin>>c;
    }
    char s[1000];
    strcpy(s,a.getNume());
    strcat(s," ");
    string ss=s + a.getPrenume();
    Plangere p(ss,a.getCarte().getId(),c,0,false);
    if(!Apartine(P,nrPlangeri,p)){
        if(nrPlangeri<nrMaxPlangeri)
            P[nrPlangeri++]=p;
        else {
            nrMaxPlangeri+=100;// cresc dimensiunea maxima a vectorului
            Plangere *Vt=new Plangere[nrPlangeri]; // fac un vector temporal;

            for (int i=0; i<nrPlangeri; i++) //copiez in vectorul temporla vectorul de carti
                Vt[i]=P[i];

            delete[] P;     // sterg vectorul de carti;

            P=new Plangere[nrMaxPlangeri]; //maresc dimensiunea vectorului

            for (int i=0; i<nrPlangeri; i++)//copiez din vt in carti
                P[i]=Vt[i];

            P[nrPlangeri++]=p; // adaug cartea;
            delete[] Vt;

        }
    }else
        cout<<"Aceasta problema a fost deja raportata si urmeaza a fi adresata."<<endl;
}
void Optiunea8(int curent,Abonament *A,int n) {
    cout<<endl;
    cout<<"+----------------SubMeniu--------------------------------------------------------+"<<endl;
    cout<<"|Pentru a parasi acest meniu apasati 0.                                          |"<<endl;
    cout<<"|Pentru a modifica numele apasati 1.                                             |"<<endl;
    cout<<"|Pentru a modifica prenumele apasati 2.                                          |"<<endl;
    cout<<"|Pentru a modifica initiala tatalui apasati 3.                                   |"<<endl;
    cout<<"|Pentru a sterge evidenta cartiilor dumneavostra apasati 4.                      |"<<endl;
    cout<<"+--------------------------------------------------------------------------------+"<<endl;
    char chr;
    cin >> chr;
    while ((chr < '0' || chr > '4')) {
        cout << "Nu ati introdus o optiune valida." << endl
             << "Va rog sa introduceti o optiune valida." << endl;
        cin >> chr;
    }
    cin.get();
    char s[100];
    Abonament aux(A[curent]);
    switch (chr) {
    case '0':
        return;
        break;
    case '1':
        cout<<"Introduceti noul nume: ";
        cin.get(s,100);
        cin.get();
        aux.setNume(s);
        break;
    case '2':
        cout<<"Introduceti noul prenume: ";
        cin.get(s,100);
        cin.get();
        aux.setPrenume(s);
        break;
    case '3':
        char x;
        cin>>x;
        if(aux.getInitialaTata()!=x)
            aux.setInitialaTata(x);
        break;
    case '4':
        int *v=new int[A[curent].getNrLuni()];
        for(int i=0; i<A[curent].getNrLuni(); i++)
            v[i]=0;
        A[curent].setNrCartiPerLuna(v);
        delete[] v;
        break;
    }
    if(Apartine(A,n,aux)!=-1 && chr!='4')
        cout<<"Nu s-a putut efectu operatia, doarece abonamentu in urma modificarii exista deja in baza noastra de date. :<\n";
    else {
        if(chr!='4')
            A[curent]=aux;
        cout<<"Modificarea s a efectuat cu succes.\n";
    }
}
void Meniu() {
    cout<<endl;
    cout<<"+---------------Meniu------------------------------------------------------------+"<<endl;
    cout<<"|Pentru a crea un abonament apasati 0.                                           |"<<endl;
    cout<<"|Pentru a accesa alt abonament pe care sa se efectueaza operatiile apasati 1.    |"<<endl;
    cout<<"|Pentru a sterge un abonament curent apasati 2.                                  |"<<endl;
    cout<<"|Pentru a imprumuta o carte apasati 3.                                           |"<<endl;
    cout<<"|Pentru a returna o carte  apasati 4.                                            |"<<endl;
    cout<<"|Pentru a afisa toate cartile neimprumutate apasati 5.                           |"<<endl;
    cout<<"|Pentru a vede informati  despre abonamentu dumneavostra apasati 6.              |"<<endl;
    cout<<"|Pentru a raporta o problema in legatura cu cartea dumneavostra apasati 7.       |"<<endl;
    cout<<"|Pentru a modifica o un abonament apasati 8.                                     |"<<endl;
    cout<<"|Pentru a inchide programul apasati tasta  9.                                    |"<<endl;
    cout<<"+--------------------------------------------------------------------------------+"<<endl;
}
void Meniu2() {
    cout<<endl;
    cout<<"+---------------Meniu adimistartor-----------------------------------------------+"<<endl;
    cout<<"|Pentru a va deloga apasati 0                                                    |"<<endl;
    cout<<"|Pentru a adauga o carte apasati 1.                                              |"<<endl;
    cout<<"|Pentru a vizualiza toate cartile din biblioteca apsatin 2.                      |"<<endl;
    cout<<"|Pentru a modifica amenzile apasati 3.                                           |"<<endl;
    cout<<"|Pentru a vizualiza toate plangerile apasati 4.                                  |"<<endl;
    cout<<"|Pentru a creste numarul de zile de la depunerea plangerilor apasati 5.          |"<<endl;
    cout<<"|Pentru a semnala trecerea intr-o noua luna apsati 6.                            |"<<endl;
    cout<<"|Pentru a sorta cartile din biblioteca apasati 7.                                |"<<endl;
    cout<<"|Pentru a afisa media amenzilor cartilor din biblioteca apasati 8.               |"<<endl;
    cout<<"|Pentru a modifica numele bibliotecii  9.                                        |"<<endl;
    cout<<"|Pentru a vizualiza plangerile apasati a.                                        |"<<endl;
    cout<<"|Pentru a inchide programul apasati tasta b.                                     |"<<endl;
    cout<<"+--------------------------------------------------------------------------------+"<<endl;

}
void Optiunea1A(Biblioteca &b) {
    cout<<"Introdueti toate datele cerute mai jos:\n";
    Carte c;
    cin.get();
    cin>>c;
    b=b+c;
}
void Optiunea3A(Biblioteca &b) {
    cout<<"Daca doriti a face modificari pentru intreaga biblioteca apasati 1.\n"
        <<"Daca doriti sa face modificari pentru o carte apasati 2.\n";
    int o;
    cin>>o;
    while(o!=1 && o!=2) {
        cout<<"Va rugam introduceti o optiune valida.\n";
        cin>>o;
    }
    if(o==1) {
        cout<<"Daca doriti a face modificari cu un o anumita suma apasati 1.\n"
            <<"Daca doriti a face modificari cu un  anumit procent apasati 2.\n";
        cin>>o;
        while(o!=1 && o!=2) {
            cout<<"Va rugam introduceti o optiune valida.\n";
            cin>>o;
        }
        if(o==1) {
            float x;
            cout<<"Intorduceti suma: ";
            cin>>x;
            b=b+x;
        } else {
            float x;
            cout<<"Intorduceti procentajul ( exemplu : pt o modificare cu 20% se va introduce 20) :";
            cin>>x;
            b=b*(1+(x/100));

        }
    } else {
        cout<<"Introduceti id-ul cartii:";
        cin>>o;
        if(b.existaId(o)) {
            Carte &c=b.getCarte(o);
            cout<<"Daca doriti a face modificari cu un o anumita suma apasati 1.\n"
                <<"Daca doriti a face modificari cu un  anumit procent apasati 2.\n";
            cin>>o;
            while(o!=1 && o!=2) {
                cout<<"Va rugam introduceti o optiune valida.\n";
                cin>>o;
            }
            if(o==1) {
                float x;
                cout<<"Intorduceti suma: ";
                cin>>x;
                c=c+x;
            } else {
                float x;
                cout<<"Intorduceti procentajul ( exemplu : pt o modificare cu 20% se va introduce 20) :";
                cin>>x;
                c=c*(1+(x/100));

            }
        } else
            cout<<"Acest id nu are asociat nicio carte.\n";
    }
}
void Optiunea5A(Plangere *P, int n) {
    cout<<"Introduceti nr de zile : ";
    int x;
    cin>>x;
    for(int i=0; i<n; i++)
        if(x==1)
            P[i]++;
        else
            P[i]=P[i]+x;
}
void Optiunea6A(Abonament *V,int n) {
    for(int i=0; i<n; i++)
        V[i].addLuna(0);
    cout<<"Cererea a fost executata cu succes.\n";
}
void Optiunea9A(Biblioteca &b) {
    char nume[200];
    cout<<"Introduceti un nou nume: ";
    cin.get();
    cin.get(nume,200);
    cin.get();
    string st;
    st=st+nume;
    b.setNume(st);
}
void OptiuneaA(Biblioteca &b, Plangere *p, int n){
    cout<<"Plangerile sunt:\n";
    for(int i=0; i<n; i++){
        cout<<"Plangerea "<<i+1<<" este:\n"
            <<"Numele persoanei care a depus plangerea este: "<<p[i].getNumePrenume()
            <<"\nId-ul problemei este:"<<p[i].getProblema()
            <<"\nPlangerea este : "<<(p[i].getEvaluat()?"evaluata":"neevaluata")
            <<"\nCartea la care s a sesizat o plangere este:\n";
            cout<<b.getCarte(p[i].getIdCarte())<<endl;
    }
    cout<<"Daca doriti sa evaluati o plangere apasati 1, altfel 0.\n";
    int op;
    cin>>op;
    if(op==0)
        return;
    cout<<"Introduceti indicele plangerii( a p-a plangere):";
    do{
    cin>>op;
    }while(op<0 || op>n);

    if(p[op-1].getEvaluat()==true)
        cout<<"Aceasta plangere a fost deja evaluata!\n";
    else{
        cout<<"Doriti sa aplicati reducerea amenzii?\nApasati 1 pt da sau 0 pt nu.\n";
        op--;
        Carte &c=b.getCarte(p[op].getIdCarte()); // aici copiez referinta cartii pentru , orice modificare facuta se va reflecta in bilioteca
        int o;
        cin>>o;
        if(o){
            c.setPret((float)c*(1-p[op].calculProcentScadereAmenda()));
            p[op].setEvaluat(true);
        }
        cout<<"Actiunea s a finalizat cu succes\n";
        b.recalculareMedie();
    }

}
int main() {
    Abonament *V= new Abonament[100], administrator("admin", "parola", 'A'), a("Ana", "Banana", 'I'), b("Popa", "Ilie", 'I'), c("Popa","Ion",'I'), d("1", "1", '1');
    int nrAbonamente = 5,nrMaxAbonemente=100, curent = -1;// vectorii sunt alocati dinamic, curent reprezinta pozitia din vector a abonamentului, daca curent este -1 inseamna ca niciun abonament nu este conectat.
    Plangere *P=new Plangere[100];
    int nrPlangeri=1,nrMaxPlangeri=100;
    Biblioteca B;
    Plangere p("ana are",6344,1);
    P[0]=p;
    V[0] = administrator;
    V[1] = a;
    V[2] = b;
    V[3] = c;
    V[4] = d;
    V[4].addLuna(11);
    Carte cc("Ana", "Popa", 100, 1, 10, "11/11/2021"),c1("An", "Popa", 100, 0, 11, "0/00/0000"),c2("Ana", "Popi", 100, 0, 11, "0/00/0000"),c3("Ana", "Coca", 100, 0, 11, "0/00/0000");
    V[4].setCarte(cc);
    Carte c4,c5;
    c4=c1+c2;
    c5=c3+c1;
    B=B+cc+c1+c2+c3+c4+c5;
    B=B+B;
    char chr;
    while (1) {
        if (curent) {
            Meniu();
            cin >> chr;
            while ((chr < '0' || chr > '9')) {
                cout << "Nu ati introdus o optiune valida." << endl
                     << "Va rog sa introduceti o optiune valida." << endl;
                cin >> chr;
            }
            switch (chr) {
            case '9':
                cout << "O zi frumoasa in continuare!" << endl;
                exit(0);
                break;
            case '0':
                Optiunea0(V, nrAbonamente,nrMaxAbonemente, curent);
                break;
            case '1':
                Optiunea1(V, nrAbonamente, curent);
                break;
            case '2':
                Optiunea2(V, nrAbonamente, curent);
                break;
            case '3':
                if (curent != -1)
                    Optiunea3(B, V[curent]);
                else
                    cout << "Nu puteti imprumuta o carte deoarece nu sunteti conectat.\n";
                break;
            case '4':
                if (curent != -1)
                    Optiunea4(B, V[curent]);
                else
                    cout << "Nu puteti returna o carte deoarece nu sunteti conectat.\n";
                break;
            case '5':
                Optiunea5(B);
                break;
            case '6':
                if (curent != -1)
                    cout << V[curent] << endl;
                else
                    cout << "Nu puteti raporta o problema deoarece nu sunteti conectat.\n";
                break;
            case '7':
                if (curent != -1)
                    if (V[curent].getCarte().getId() != -1)
                        Optiuneat7(P, nrPlangeri,nrMaxPlangeri, V[curent]);
                    else
                        cout
                                << "Nu puteti raporta o poblema deoarece nu ati imprumutat in momentul actual nicio carte.\n";
                else
                    cout << "Nu puteti raporta o problema deoarece nu sunteti conectat.\n";
                break;
            case '8':
                if(curent!=-1)
                    Optiunea8(curent,V,nrAbonamente);
                else
                    cout<<"Nu se poate efectua operatia deoarece nu sunteti conectat.\n";

            }
            cout << "Pentru a continua apasati o tasta." << endl;
            cin >> chr;
            system("cls");

        } else {
            Meniu2();
            cin >> chr;
            while ((chr < '0' || chr > '9') && chr!='a' && chr!='b' ) {
                cout << "Nu ati introdus o optiune valida." << endl
                     << "Va rog sa introduceti o optiune valida." << endl;
                cin >> chr;
            }
            switch (chr) {
            case 'b':
                cout << "O zi frumoasa in continuare!" << endl;
                exit(0);
                break;
            case '0':
                curent = -1;
                break;
            case '1':
                cout<<"Introdueti toate datele cerute mai jos:\n";
                cin.get();
                cin>>cc;
                B=B+cc;
                break;
            case '2':
                cout<<B<<endl;
                break;
            case '3':
                Optiunea3A(B);
                break;
            case '4':
                if(nrPlangeri==0)
                    cout<<"Nu exista plangeri!\n";
                else {
                    cout<<"Plangerile sunt: \n";
                    AfisarePlangeri(P,nrPlangeri);
                }
                break;
            case '5':
                Optiunea5A(P,nrPlangeri);
                break;
            case '6':
                Optiunea6A(V,nrAbonamente);
                break;
            case '7':
                B.sort();
                cout<<"Cartile au fost sortate cu succes.\n";
                break;
            case '8':
                cout<<"Media carilor din biblioteca este: "<<B.getMedie()<<endl;
                break;
            case '9':
                Optiunea9A(B);
                break;
            case 'a':
                OptiuneaA(B,P,nrPlangeri);
                break;

            }

            cout << "Pentru a continua apasati o tasta." << endl;
            cin >> chr;
            system("cls");
        }
    }
    return 0;
}
