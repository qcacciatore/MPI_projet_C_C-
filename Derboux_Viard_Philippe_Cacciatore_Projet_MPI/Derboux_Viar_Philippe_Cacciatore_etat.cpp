#include <iostream>
#include <map>
#include <string>
#include "Derboux_Viar_Philippe_Cacciatore_etat.h"
using namespace std;

Etat :: Etat (string pnom, string pstatut) : nom(pnom), statut(pstatut){};

string Etat :: getStatut()
{
    return statut;
}

string Etat :: getNom()
{
    return nom;
}

void Etat :: setStatut(string statutp)
{
    statut= statutp;
}

void Etat :: setNom(string pnom)
{
    nom=pnom;
}
