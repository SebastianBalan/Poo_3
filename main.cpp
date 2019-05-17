#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class Examen
{

protected:

    char nume[101];
    float notaScris;///cel mult 5
    float puncteProiect;///cel mult 1p

public:
    static int nrCrt;


    Examen(char *s,float a,float b)
    {
        notaScris=a;
        puncteProiect=b;
        int i;
        for(i=0; i<strlen(s); i++)
            nume[i]=s[i];
        nume[i]=NULL;
    }

    Examen ()
    {
        nume[0]=NULL;
        notaScris=0;
        puncteProiect=0;
    }
    ~Examen() {}

    void operator=(Examen &e)
    {
        notaScris=e.notaScris;
        puncteProiect=e.puncteProiect;
        int i;
        for(i=0; i<strlen(e.nume); i++)
            nume[i]=e.nume[i];
    }

    friend istream &operator>>(istream &input, Examen &e)
    {
        cout<<"Introduceti numele examenului ";
        input>>e.nume;
        cout<<"Introduceti nota la examen ";
        input>>e.notaScris;
        cout<<"Introduceti punctele bonus din proiect ";
        input>>e.puncteProiect;
        return input;
    }

    virtual void afisare()=0;

};

int Examen::nrCrt=0;

class Partial : public Examen
{
private:
    float notaOral;///cel mult 5
    float quiz;///cel mult 2p

public:

    Partial(float a,float b,char *s,float c,float d) : Examen(s,c,d)
    {
        notaOral=a;
        quiz=b;
    }

    Partial():Examen()
    {
        notaOral=0;
        quiz=0;
    }
    ~Partial() {}

    friend istream &operator>>(istream &input, Partial &p)
    {
        cout<<"Introduceti numele examenului ";
        input>>p.nume;
        cout<<"Introduceti nota la examen ";
        input>>p.notaScris;
        cout<<"Introduceti punctele bonus din proiect ";
        input>>p.puncteProiect;
        cout<<"Introduceti nota obtinuta la examenul oral ";
        input>>p.notaOral;
        cout<<"Introduceti punctele obtinute la quiz ";
        input>>p.quiz;
        return input;
    }

    void afisare()
    {
        int j;
        Examen::nrCrt++;
        cout<<nrCrt<<".";
        for(j=0; j<strlen(nume); j++)
            cout<<nume[j];
        cout<<" cu nota la scris ";
        cout<<notaScris<<" si cu "<<notaOral<<" nota la oral si "<<puncteProiect<<" puncte bonus din proiect \n";
        try
        {
            if(notaScris<2.5 || notaOral<2.5 )
                throw "Picat";
        }
        catch(const char *mesaj)
        {
            cout<<mesaj<<endl;
        }
    }

};

template<class T>
class CatalogIndividual
{
private:
    vector<Partial*>catalog;
public:
    static int nrMatricol;

    CatalogIndividual() {}
    ~CatalogIndividual() {}
    CatalogIndividual(Partial *c)
    {
        catalog.push_back(c);
    }

    ///copy-constructor
    CatalogIndividual(CatalogIndividual<Partial> &c)
    {
        catalog=c.catalog;
    }

    CatalogIndividual<Partial>& operator+=(Partial &c)
    {
        catalog.push_back(&c);
        return *this;
    }

    void afisare()
    {
        Partial *P;

        for(int i=0; i<catalog.size(); i++)
        {
            try
            {
                P=dynamic_cast<Partial*>(catalog[i]);
                if(P)
                    throw "afisare";
            }
            catch (const char *mesaj)
            {
                P->afisare();
            }

        }
    }
};

///int CatalogIndividual<Examen>::nrMatricol=0;

int main()
{
    Partial p,pp;
    cin>>p;
    ///Examen::nrCrt++;
    CatalogIndividual<Partial> P;
    P+=p;
    P.afisare();
    cin>>pp;
    Examen::nrCrt=0;
    P+=pp;
    P.afisare();

    return 0;
}
