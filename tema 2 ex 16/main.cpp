#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;


///clasa Angajat

class Angajat
{
protected:
    string nume;
    double salariu;
    int sectie_lucru;

private:
    int nrAngajati;

public:

    ///constructori

    Angajat()
    {
        nume = ""; // NULL
        salariu = 0.0;
        sectie_lucru = -2;
    }

    Angajat(string _nume, int _sectie_lucru, double _salariu)
    {
        nume.assign(_nume);
        sectie_lucru = _sectie_lucru;
        salariu = _salariu;
    }

    Angajat(const Angajat &x) // supraincarcarea de copiere
    {
        nume.assign(x.nume);
        sectie_lucru = x.sectie_lucru;
        salariu = x.salariu;
    }

    ///destructor

    ~Angajat()
    {
        nume.erase();
        salariu = 0.0;
        sectie_lucru = -2;
    }

    //set, get pentru nume
    string getNume() { return nume; }
    void setNume(string _nume) { nume.assign(_nume); }

    //set, get pentru salariu
    virtual double getSalariu() { return salariu; }
    void setSalariu(double _salariu){ salariu = _salariu; }

    //set, get pentru sectie
    int getSectie() { return sectie_lucru;}
    void setSectie(int _sectie_lucru) { sectie_lucru = _sectie_lucru;}

    //set, get pentru nrAngajati
    virtual int getAngajati() { return nrAngajati; }
    void setAngajati(int x) { nrAngajati = x; }


    //functii suprascriere
    friend ostream & operator << (ostream &, Angajat );
    friend istream & operator >> (istream &, Angajat );
    Angajat & operator = (const Angajat &);

};


///operatori de afisare si citire pentru clasa Angajat
///operator afisare Angajat
ostream & operator << (ostream &out_s, Angajat x[])
{
    int i;
    out_s << "\n";
    int n = x[1].getAngajati();
    for(i = 1; i <= n; i++)
        out_s <<"Angajatul: "<< x[i].getNume() << " are salariul: " << x[i].getSalariu() << ", lucreaza in sectia: " << x[i].getSectie() << "\n";
    return out_s;
}

///operator citire Angajat
istream & operator >> (istream &in_s, Angajat x[])
{
    int i, n;
    cout << "n = ";
    in_s >> n;
    x[1].setAngajati(n);
    for(i = 1; i <= n; i++)
    {
        string nume;
        double salariu;
        int sectie;
        cout << "\nSalariu: ";
        in_s >> salariu;
        x[i].setSalariu(salariu);

        cout << "Nume: ";
        in_s.get();
        in_s >> nume;
        x[i].setNume(nume);

        cout << "Sectie: ";
        in_s >> sectie;
        x[i].setSectie(sectie);

    }
    return in_s;
}

/// supraincarcarea atribuirii pt angajat, =
Angajat & Angajat :: operator = (const Angajat &p)
{
    this->nume = p.nume;
    this->sectie_lucru = p.sectie_lucru;
    this->nrAngajati = p.nrAngajati;
    this->salariu = p.salariu;
    return (*this);

}

///clasa Administrator

class Administrator : public Angajat
{
private:
    int sectie_sef;
    bool admin;
    int nrAdmin;

public:
    ///constructor
    Administrator() : Angajat()
    {
        admin = 1;
    }
    Administrator(string nume, double salariu, int _sectie_sef, int n) //sectie_sef e cheia comuna
            : Angajat(nume, _sectie_sef, salariu), sectie_sef(_sectie_sef), admin(1), nrAdmin(n) //apeleaza constructorul din Angajat
    {
    }

    Administrator(Administrator &x) : Angajat(x.nume, x.sectie_sef, x.salariu)
    {
        admin = 1;
        sectie_sef = x.sectie_sef;
    }

    ///destructor
    ~Administrator(){};

    //set, get pentru cati administratori sunt
    int getAngajati() { return nrAdmin; }
    void setAdmin(int x) { nrAdmin = x; }

    //get admin
    int getAdminT() { return admin; }

    //get salariu + bonus
    double getSalariu() { return  salariu + salariu * 0.2; } //ceva in plus pentru ca e administrator

    //functii suprascriere
    friend ostream & operator << (ostream &, Administrator );
    friend istream & operator >> (istream &, Administrator );
    Administrator & operator = (const Administrator &);
};


///operatori de afisare si citire pentru clasa Administrator
///operator afisare Administrator
ostream & operator << (ostream &out_s, Administrator x[])
{
    int i;
    out_s << "\n";
    int n = x[1].getAngajati();
    for(i = 1; i <= n; i++)
        {
            out_s <<"Angajatul: "<< x[i].getNume() << " are salariul: " << x[i].getSalariu() << ", lucreaza in sectia: " << x[i].getSectie() << " si ";
            if(x[i].getAdminT() == 1)
                cout<<"este administrator\n";
        }
    return out_s;
}

///operator citire Administrator
istream & operator >> (istream &in_s, Administrator x[])
{
    int i, n;
    cout << "n = ";
    in_s >> n;
    x[1].setAdmin(n);
    for(i = 1; i <= n; i++)
    {

        string nume;
        double salariu;
        int sectie;
        cout << "\nSalariu: ";
        in_s >> salariu;
        x[i].setSalariu(salariu);

        cout << "Nume: ";
        in_s.get();
        in_s >> nume;
        x[i].setNume(nume);

        cout << "Sectie: ";
        in_s >> sectie;
        x[i].setSectie(sectie);
    }
    return in_s;
}

/// supraincarcarea atribuirii pentru administrator, =
Administrator & Administrator :: operator = (const Administrator &p)
{
    this->nume = p.nume;
    this->sectie_lucru = p.sectie_lucru;
    this->sectie_sef = p.sectie_sef;
    this->admin = p.admin;
    this->nrAdmin = p.nrAdmin;
    this->salariu = p.salariu;
    return (*this);

}
int main()
{
    Angajat v[100];
    Administrator w[100];
    int n;
    cout << "Citire Angajati:\n";
    cin >> v;
    cout << v;

    cout << "\nCitire Administratori:\n";
    cin >> w;
    cout << w;

    return 0;
}
