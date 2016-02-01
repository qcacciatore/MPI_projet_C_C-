
#include <iostream>
#include <map>
#include "Derboux_Viar_Philippe_Cacciatore_etat.h"
#include "Derboux_Viar_Philippe_Cacciatore_automate.h"
#include "Derboux_Viar_Philippe_Cacciatore_transition.h"
#include <string>
 #include <stdio.h>

using namespace std;
void tri(string chaine);

int main()
{
    Automate *oto;
    string rep;


    cout << "----------------------------------" << endl;
        cout << "       TAI Mathematique pour l'informatique" << endl;
        cout << "----------------------------------" << endl << endl;
    do
    {
    string filename="";
    oto = new (Automate);
        cout<<"quel fichier voulez vous ouvrir ? (exemple 02)";
        cin>>filename;

        if (oto->chargement(filename)== true) // vérification le fichier est ouvert
        {
            cout << "----------------------------------" << endl;
            cout << "       Automate de depart" << endl;
            cout << "----------------------------------" << endl << endl;
            oto->afficher();
            cout<<endl<<endl<<"voulez vous standardiser ? (oui : 0, non : 1)"<<endl;
            cin>>rep;
            if (rep == "0")
            {
                if (oto->EstStandard()== true)
                {
                    cout<<"l'automate est deja standard"<<endl<<endl;
                    oto->afficher();
                }
                else
                {
                    oto->standardiser();
                    cout << "----------------------------------" << endl;
                    cout << "       Automate standardise" << endl;
                    cout << "----------------------------------" << endl << endl;
                    oto->afficher();
                    delete(oto);
                    oto = new (Automate);
                    oto->chargement(filename);
                }
                cout<<endl<<"voulez vous charger un nouvel automate (0) ou voulez vous continuer (1)?"<<endl;
            cin>>rep;
            }
            if(rep=="1")
            {
                cout << "----------------------------------" << endl;
                cout << "       Automate de depart" << endl;
                cout << "----------------------------------" << endl << endl;
                oto->afficher();
                cout<<endl<<"determiniser (1) :";
                cin >>rep;
                cout<<endl;
                if (oto->Estdeterministe()==false)
                {
                    oto->determiniser(oto->fusionEntre());
                    oto->transfer();
                    cout << "----------------------------------" << endl;
                    cout << "       Automate deterministe" << endl;
                    cout << "----------------------------------" << endl << endl;
                    oto->afficher();
                    cout<<endl<<endl;
                }
                else
                {
                    cout<<"l'automate est deja deterministe"<<endl;
                    oto->afficher();
                }
                do
                {
                    cout<<"completer : 1, reconaissance d'un mot : 0"<<endl;
                    cin>>rep;
                    if (rep == "0")
                    {
                        string mot="";
                        cout<<"entrez un mot (0 : mot vide) : ";
                        cin>>mot;
                        oto->langage(mot);
                    }
                }
                while(rep=="0");

                if (oto->Estcomplet()==false)
                {
                    oto->completer();
                    cout << "----------------------------------" << endl;
                    cout << "       Automate complet" << endl;
                    cout << "----------------------------------" << endl << endl;
                    oto->afficher();
                }
                else
                {
                    cout<<"l'automate est deja complet"<<endl;
                    oto->afficher();
                }
                do
                {
                    cout<<endl<<"minimiser : 1, reconaissance d'un mot : 0"<<endl;
                    cin>>rep;
                    if (rep == "0")
                    {
                        string mot="";
                        cout<<"entrez un mot (0 : mot vide) : ";
                        cin>>mot;
                        oto->langage(mot);
                    }
                }
                while(rep=="0");

                oto->minimiser();
                cout << "----------------------------------" << endl;
                cout << "       Automate  minimise" << endl;
                cout << "----------------------------------" << endl << endl;
                oto->afficher();

                do
                {
                    cout<<"continuer : 1, reconaissance d'un mot : 0"<<endl;
                    cin>>rep;
                    if (rep == "0")
                    {
                        string mot="";
                        cout<<"entrez un mot (0 : mot vide) : ";
                        cin>>mot;
                        oto->langage(mot);
                    }
                }while(rep=="0");

                cout<<endl<<endl<<"charger un nouvel automate ? ( oui :1, quitter : 0)"<<endl<<endl;
                cin>>rep;
                delete(oto);
            }
        }
    }
    while (rep != "0");
}


void tri(string& chaine)
{
    int k=0;
    int taille = chaine.size();
    for(int j=1; j<taille; j++)
    {
        for(int i=0; i<taille-1; i++)
        {
            if(chaine[i] > chaine[i+1])
            {
                k = chaine[i] - chaine[i+1];
                chaine[i] -= k;
                chaine[i+1] += k;
            }
        }
    }
}
