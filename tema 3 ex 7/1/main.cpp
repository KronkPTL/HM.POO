#include <iostream>
#include <vector>
#include <string>

using namespace std;

///clasa de baza FILM
class film
{
protected:
    string nume_film, tip_film, nume_regizor;
    double salariu_regizor, rating, incasari;
    int durata;

public:
    ///constructori
    film(string _nume = "", string _tip_film = "", string _nume_regizor = "", int _durata = 0, double _rating = 0.0, double _incasari = 0.0)
    {
        nume_regizor = _nume_regizor;
        nume_film = _nume;
        tip_film = _tip_film;
        durata = _durata;
        rating = _rating;
        incasari = _incasari;
    }
    film(film &x)
    {
        nume_regizor = x.nume_regizor;
        nume_film = x.nume_film;
        tip_film = x.tip_film;
        durata = x.durata;
        rating = x.rating;
        incasari = x.incasari;
    }

    ///destructor
    virtual ~film(){}

    ///get si set
    void setNume_film(string x){ nume_film = x;}
    string getNume_film(){ return nume_film; }

    void setNume_regizor(string x){ nume_regizor = x;}
    string getNume_regizor(){ return nume_regizor; }

    void setTip_film(string x) { tip_film = x;}
    string getTip_film(){ return tip_film; }

    void setDurata(int x) { durata = x; }
    int getDurata(){ return durata; }

    void setRating(double x){ rating = x;}
    double getRating() { return rating;}

    void setIncasari(double x){ incasari = x;}
    double getIncasari(){return incasari;}

    virtual void setSalariu(double x){ salariu_regizor = x; }
    virtual double getSalariu() { return salariu_regizor; }

    ///functii
    //afisare
    virtual void afis() = 0;

    //citire
    friend istream & operator >>(istream &, film &);

    film & operator = (const film &);
};

istream & operator >> (istream &in, film &p)
{
    string _nume_film, _tip_film, _nume_regizor;
    double _salariu_regizor, _rating, _incasari;
    int _durata;
    cout << "\n-------------------------------\nAcum cititi UN FILM\n";

    cout << "\nNumele filmului: ";
    in >> _nume_film;
    p.setNume_film(_nume_film);

    cout << "\nDurata filmului(in ore): ";
    in >> _durata;
    p.setDurata(_durata);

    cout << "\nTipul filmului: ";
    in >> _tip_film;
    p.setTip_film(_tip_film);

    cout << "\nIncasari: ";
    in >> _incasari;
    p.setIncasari(_incasari);

    cout << "\nRating: ";
    in >> _rating;
    p.setRating(_rating);

    cout << "\nNumele regizorului filmului: ";
    in >> _nume_regizor;
    p.setNume_regizor(_nume_regizor);

    cout << "\nSalariul fix al regizorului: ";
    in >> _salariu_regizor;
    p.setSalariu(_salariu_regizor);

    return in;
}

film & film :: operator = (const film &p)
{
    if(this == &p)
        return (*this);
    this -> nume_regizor = p.nume_regizor;
    this -> salariu_regizor = p.salariu_regizor;
    this -> nume_film = p.nume_film;
    this -> tip_film = p.tip_film;
    this -> durata = p.durata;
    this -> rating = p.rating;
    this -> incasari = p.incasari;
    return (*this);
}




///clasa PERSONAL
class personal : public film
{
//private:
    //int nrPersonal;

protected:
    string CNP, nume; ///nume film e cheia primara
    double salariu;

public:
    ///constructori
    personal(string _CNP = "", string _nume = "", string _nume_film = "", double _salariu = 0.0)
    {
        CNP = _CNP;
        nume = _nume;
        nume_film = _nume_film;
        salariu = _salariu;
    }
    personal(personal &x)
    {
        CNP = x.CNP;
        nume = x.nume;
        nume_film = x.nume_film;
        salariu = x.salariu;
    }
    ///destructor
    ~personal() {}

    ///get,set pt cnp
    void setCnp(string x){ CNP = x; }
    string getCnp() { return CNP; }

    ///get,set pt nume
    void setNume(string x){ nume = x;}
    string getNume(){ return nume; }

    ///get,set pt nume film

    ///get,set pt salariu;
    void setSalariu(double x){ salariu = x; }
    double getSalariu() { return salariu; }

    ///functii
    personal & operator = (const personal &);
    friend istream & operator >>(istream &, personal &);
    void afis(){cout << "in ast anu itnra";}
};

istream & operator >>(istream &in, personal &p)
{
    string _CNP, _nume;
    double _salariu;
    cout << "\n-------------------------------\nAcum cititi UN PERSONAL din filmul curent\n";

    cout << "\nCNP: ";
    in >> _CNP;
    p.setCnp(_CNP);

    cout << "\nNume: ";
    in >> _nume;
    p.setNume(_nume);
    in.get();

    cout << "\nSalariu: ";
    in >> _salariu;
    p.setSalariu(_salariu);

    return in;
}

personal & personal :: operator = (const personal &p)
{
    if(this == &p)
        return (*this);
    this -> nume = p.nume;
    this -> CNP = p.CNP;
    this -> salariu = p.salariu;
    return (*this);
}





///clasa ACTOR
class actor : public personal
{
private:
    bool principal;
    static int nrActori;
public:
    ///constructori
    actor(string _nume = "", string _CNP = "", string _nume_film = "", double _salariu = 0.0, bool _principal = 0)
        : personal(_CNP, _nume, _nume_film, _salariu), principal(_principal) { }

    actor(actor &x)
        : personal(x.CNP, x.nume, x.nume_film, x.salariu), principal(x.principal) {}

    ///destructor
    ~actor(){}

    ///functii
    ///set si get
    void setPrincipal(bool x){ principal = x;}
    bool getPrincipal(){ return principal;}

    void setSalariu(double x) ///setarea salariului pentru actor principal
    {
        if(principal == 1)
            salariu = x + 0.1 * x; //marirea de 10%
        else salariu = x;
    }

    ///functie de citire
    friend istream & operator >> (istream &, actor &);

    ///functie de afisare
    void afis()
    {
        cout << "Actorul cu numele: ";
        cout << this -> getNume();
        cout << " are CNP-ul: " ;
        cout << this -> getCnp();
        cout << ", salariul: ";
        cout << this -> getSalariu();
        cout << " si apare in filmul: ";
        cout << this -> getNume_film();
        if(this -> principal == 1)
            cout << " si este personaj principal";
        cout <<"\n";
    }
    actor & operator = (const actor &);

};

istream & operator >> (istream &in, actor &p)
{

    cout << "\n-------------------------------\nAcum cititi UN ACTOR din filmul curent\n";

    in >> (personal &)p;

    cout << "\nEste actor principal? (0 sau 1): ";

    try
    {
        in >> p.principal;
        if(p.principal != 0 && p.principal != 1)
            throw 0;
        if(p.principal == 1)
            p.salariu = p.salariu + 0.1 * p.salariu; //marirea de 10%
        else p.salariu = p.salariu;
    }
    catch(int x)
    {
        cout << "\nNu ati introdus 0 sau 1!";
        return in;
    }

    return in;
}

actor & actor :: operator = (const actor &p)
{
    if(this == &p)
        return (*this);

    static_cast<personal &>(*this) = (personal &)p; ///pt ca stiu ca se duce in clasa "de sus"

    this -> principal = p.principal;
    return (*this);
}






///clasa PERSONAL_TEHNIC
class personal_tehnic : public personal
{
private:
    string departament;
public:
    ///constructori
    personal_tehnic(string _nume = "", string _CNP = "", string _nume_film = "", double _salariu = 0.0, string _departament = "")
        : personal(_CNP, _nume, _nume_film, _salariu), departament(_departament) {}

    personal_tehnic(personal_tehnic &x)
        : personal(x.CNP, x.nume, x.nume_film, x.salariu), departament(x.departament) {}
    ///destructor
    ~personal_tehnic() {}

    ///get si set
    void setDepartament(string x) { departament = x; }
    string getDepartament() { return departament; }
    ///functii
    ///functie de citire
    friend istream & operator >> (istream &, personal_tehnic &);

    ///functie de afisare
    void afis()
        {
            cout << "Persoana cu numele: " << this -> getNume();
            cout << ", lucreaza pe departamentul: " << this -> getDepartament();
            cout << " si are salariul: " << this -> getSalariu();
            cout << "\n";
        }

    personal_tehnic & operator = (const personal_tehnic &);
};

istream & operator >> (istream &in, personal_tehnic &p)
{
    string _departament;
    //cout << "\n-------------------------------\nAcum cititi UN PERSONAL TEHNIC din filmul curent\n";

    in >> (personal &)p;

    cout << "\nPe ce departament lucreaza?: ";
    try
    {
        in >> p.departament;
        if(p.departament.size() == 0)
            throw 0;
    }
    catch(int x)
    {
        cout << "\nNu ati introdus departamentul!";
        return in;
    }

    return in;
}

personal_tehnic & personal_tehnic :: operator = (const personal_tehnic &p)
{
    if(this == &p)
        return (*this);

    static_cast<personal &>(*this) = (personal &)p;

    this -> departament = p.departament;
    return (*this);
}

template <class T> ///T pentru film si W pentru persoane
class FirmaDistributie
{
private:
    //vector <W> persoane;
    //vector <T*> filme_total;
    vector <T*> persoane;
    static unsigned persoane_total;
    static unsigned actori_total;
public:
    ///constructori
    FirmaDistributie(){}
    FirmaDistributie(FirmaDistributie<T> &p)
    {
        //filme_total = p.filme_total;
        persoane = p.persoane;
        persoane_total = p.persoane_total;
        actori_total = p.actori_total;
    }

    ///destructor
    ~FirmaDistributie()
    {
        persoane_total = 0;
        actori_total = 0;
    }

    ///functii
    FirmaDistributie<T> & operator +=(T &p) ///pentru adaugare
    {
        persoane.push_back(&p);

        persoane_total++;
        //actor *P = dynamic_cast<actor *>(filme_total[filme_total.size() - 1]);
        //if(P && P -> principal == 1)
            //actori_total++;
        return *this;

    }

    /*FirmaDistributie<T, W> & operator +=(W &p) ///pentru adaugare
    {
        persoane.push_back(&p);

        actor *P = dynamic_cast<actor *>(filme_total[filme_total.size() - 1]);
        if(P)
            actori_total++;
        return *this;

    }*/

    ///get
    static unsigned getPersoane_total() { return persoane_total; }
    static unsigned getactori_total(){ return actori_total; }

    void afis()
    {
        int i, j;
        //for(i = 0; i < filme_total.size(); i++)
            for(j = 0; j < persoane.size(); j++)
            {

                actor *P = dynamic_cast<actor *>(persoane[j]);
                if(P)
                    P->afis();
                personal_tehnic *Q = dynamic_cast<personal_tehnic *>(persoane[j]);
                if(Q)
                    Q->afis();
            }
    }
};

template<class T>
unsigned FirmaDistributie<T> :: persoane_total = 0;

template<class T>
unsigned FirmaDistributie<T> :: actori_total = 0;



int main()
{
    FirmaDistributie<film> p;
    int i, x;
    do
    {
        cout << "Doriti sa introduceti un actor sau un personal tehnic(1 sau 2): ";
        cin >>x;
        if(x == 1)
            {
                actor un_actor;
                cin >> un_actor;
                p += un_actor;
            }

        else if(x == 2)
            {
                personal_tehnic tehnic;
                cin >> tehnic;
                p += tehnic;
            }
        cout << "\n";
    }while(x != 0);

    cout << p.getPersoane_total();
    cout << "\n";
    p.afis();

    return 0;
}
