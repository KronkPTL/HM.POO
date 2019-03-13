#include <iostream>
#include <fstream>

using namespace std;

class Nod
{
private:
    char info;
    Nod *next, *prev;

public:

    Nod(){next = prev = NULL;}; //constructor
    ~Nod(){}; //destructor

    //functii de accesare
    char getInfo()
    {
        return info;
    }

    Nod * getNext()
    {
        return next;
    }

    Nod * getPrev()
    {
        return prev;
    }

    void setInfo(char x)
    {
        info = x;
    }

    void setNext(Nod *x)
    {
        next = x;
    }

    void setPrev(Nod *x)
    {
        prev = x;
    }

    //functia friend pentru lista
    friend class List;
};


class List
{
private:
    Nod *prim, *ultim;

public:
    // Constructor
    List();
    List(const List &);

    //Destructor
    ~List();

    // inserarea la final
    void adaugare_final(char);

    // stergerea ultimei valori din lista
    void sterge_final();

    // functii friend
    friend ostream &operator << (ostream &, const List &);
    friend istream &operator >> (istream &, List &);

    //supraincarcari
    List operator + (const List &); //supraincarcarea +
    List & operator = (const List &); //supraincarcarea =


};

List::List() //constructor lista
{
    prim = ultim = NULL;
}

List::~List() //destructor
{
    delete []prim;
}


void List::adaugare_final(char a) //adaugarea unei valori la final
{

    Nod *q = new Nod;
    q -> setInfo(a);
    q -> setNext(NULL);
    if(!prim)
    {
        prim = q;
        ultim = prim;
        prim -> setPrev(NULL);
    }
    else
    {
        ultim -> setNext(q);
        q -> setPrev(ultim);
        ultim = q;
    }
}

List::List(const List &x)
{
    prim = x.prim;
    ultim = x.ultim;
    Nod *q;
    for(q = x.prim; q != NULL; q = q -> getNext())
        this -> adaugare_final(q -> getInfo());

}

void List::sterge_final() //stergerea unei valori de la final
{
    if(prim != NULL && ultim != NULL)
    {
        Nod *q = ultim; // salvez adresa nodului pe care il sterg
        if (prim == ultim)
        {
            prim = NULL;
            ultim = NULL;
            delete q;
        }

        ultim = ultim -> getPrev();
        ultim -> setNext(NULL);
        delete q;
    }
}

ostream & operator << (ostream &out_s, const List &l) //afisare
{
    Nod *q;
    if(l.prim == NULL)
        return out_s;
    cout << "\nAfisare de la stanga la dreapta:   ";
    for (q = l.prim; q != NULL; q = q -> getNext())
        out_s << q -> getInfo() << " ";

    cout << "\n\nAfisare de la dreapta la stanga:   ";
    for(q = l.ultim; q != NULL; q = q -> getPrev())
        out_s << q -> getInfo() << " ";

    cout<<"\n";
    return out_s;
}

istream & operator >> (istream &in_s, List &l) //citire
{
    char a;
    int n, i;
    //cout << "n = ";
    in_s >> n;
    if(n != 0)
    {
        //cout << "\n\nValori: ";
        for(i = 1; i <= n; i++)
        {
            in_s >> a;
            l.adaugare_final(a);
        }
    }
    else cout << "Nu am ce valori sa citesc.";
    return in_s;
}

List List::operator + (const List &l) //supraincarcarea operatorului + pentru concatenare
{
    List p;
    Nod *q;
    for(q = this -> prim; q != NULL; q = q -> getNext())
        p.adaugare_final(q -> getInfo());

    for(q = l.prim; q != NULL; q = q -> getNext())
        p.adaugare_final(q -> getInfo());

    return p;
}

List & List::operator = (const List &p) //supraincarcarea atribuirii
{
    Nod *q;
    delete []prim;
    prim = ultim = NULL;
    for(q = p.prim; q != NULL; q = q -> getNext())
        this -> adaugare_final(q -> getInfo());
    return (*this);

}
int main()
{
    int k;
    cout << "\nDoriti sa cititi din fisier sau de la tastatura?(1 - de la tastatura; altfel - fisier): ";
    cin >> k;
    if(k == 1) ///citire de la tastatura
    {
        //prima lista
        List l;
        cout << "\nCiteste prima lista:\nn = ";
        cin >> l;
        cout << l;

        //a doua lista
        List q;
        cout << "\n\nCiteste a doua lista:\nn = ";
        cin >> q;
        cout << q;

        //concatenare
        List p;
        p = l + q;
        cout << "\n\nDupa concatenare:" << p;

        //o stergere din prima lista
        l.sterge_final();
        cout << "\n\nDupa stergerea ultimului nod din prima lista:";
        cout << l;
    }
    else ///citire din fisier
    {
        ifstream fin("ex.txt");

        //prima lista
        List l;
        cout << "\nCiteste prima lista:\n";
        fin >> l;
        cout << l;

        //a doua lista
        List q;
        cout << "\n\nCiteste a doua lista:\n";
        fin >> q;
        cout << q;

        //concatenare
        List p;
        p = l + q;
        cout << "\n\nDupa concatenare:" << p;

        //o stergere din prima lista
        l.sterge_final();
        cout << "\n\nDupa stergerea ultimului nod din prima lista:";
        cout << l;
    }
    return 0;
}
