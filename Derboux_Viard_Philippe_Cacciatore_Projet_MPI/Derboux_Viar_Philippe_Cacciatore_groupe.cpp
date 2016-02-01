#include <iostream>
#include "Derboux_Viar_Philippe_Cacciatore_etat.h"
#include "Derboux_Viar_Philippe_Cacciatore_automate.h"
#include "Derboux_Viar_Philippe_Cacciatore_groupe.h"
#include <string>
#include <map>


using namespace std;

Groups::Groups()
{
    nbr_etats = 0;
    nbr_groups = 0;
    names = new string[1000];
    num_group = new int[1000];

}

string Groups::getname(int index)
{
    return names[index];
}

int Groups::getnumgroup(int index)
{
    return num_group[index];
}

int Groups::getnumgroup(string namee)
{
    for (int tmp=0; tmp < nbr_etats; tmp++)
    {
        if( names[tmp] == namee)
        {
            return num_group[tmp];
        }
    }
}

int Groups::getnbre()
{
    return nbr_etats;
}

int Groups::getnbrgroups()
{
    return nbr_groups;
}
void Groups::setname(int index, string namee)
{
    names[index] =  namee;
}

void Groups::setnumgroup(int index, int numgroup)
{
    num_group[index] = numgroup;
}

void Groups::incnbretats()
{
    nbr_etats = nbr_etats + 1;
}

bool Groups::elexist(string element)
{
    for (int x=0; x < nbr_etats; x++)
    {
        if(names[x] == element)
        {
            return true;
        }
    }
    return false;
}

int Groups::getnumetat(string x)
{
    for (int tmp=0; tmp < nbr_etats; tmp++)
    {
        if (names[tmp] == x)
        {
            return tmp;
        }
    }
}

Groups::Groups(const Groups& x): nbr_etats(x.nbr_etats), nbr_groups(x.nbr_groups), names(x.names), num_group(x.num_group)
{

}

void Groups::setnbrgroups(int x)
{
    nbr_groups = x;

}

void Groups::affiche_a_minimise()
{
    for (int x=1; x < nbr_groups + 1; x++)
    {
        cout << " groupe : " << x << " est composé des etats : ";
        for (int y=0; y < nbr_etats; y++)
        {
            cout << names[y] << " : gr " << x<<endl;
        }
        cout << endl;
    }
}

int Groups::gettaillegroupe(int nummer)
{
    int cpt=0;
    for (int x=0; x < nbr_etats; x++)
    {
        if(num_group[x] == nummer)
        {
            cpt = cpt+1;
        }
    }
    return cpt;
}







