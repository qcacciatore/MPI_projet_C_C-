#ifndef ETAT_H_INCLUDED
#define ETAT_H_INCLUDED
#include <string>
#include <map>

using namespace std;

class Etat
{
    string nom;
    string statut; // 0 rien, 1 entrée, 2 sortie, 3 les 2

public :
    string getNom();
    string getStatut();
    void setStatut(string pstatut);
    void setNom(string pnom);
    Etat(string pnom, string pstatut);
};

#endif // ETAT_H_INCLUDED
