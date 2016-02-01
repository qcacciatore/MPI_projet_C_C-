#ifndef GROUPE_H_INCLUDED
#define GROUPE_H_INCLUDED

#include <string>

class Groups
{
    private:
    string* names;
    int* num_group;
    int nbr_etats;
    int nbr_groups;

    public:

    Groups();
    Groups(const Groups& x);
    string getname(int index);
    int getnumgroup(int index);
    int getnumgroup(string namee);
    int getnbre();
    int getnumetat(string x);
    void setname(int index, string namee);
    void setnumgroup(int index, int numgroup);
    void incnbretats();
    int getnbrgroups();
    void setnbrgroups(int x);
    bool elexist(string element);
    void affiche_a_minimise();
    int gettaillegroupe(int nummer);

};

#endif // GROUPE_H_INCLUDED
