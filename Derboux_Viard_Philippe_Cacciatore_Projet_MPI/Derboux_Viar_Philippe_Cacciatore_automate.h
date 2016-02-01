#ifndef AUTOMATE_H_INCLUDED
#define AUTOMATE_H_INCLUDED
#include "Derboux_Viar_Philippe_Cacciatore_etat.h"
#include "Derboux_Viar_Philippe_Cacciatore_transition.h"
#include <vector>

using namespace std;

class Automate
{
      map<string, Etat*> etats;
      map<string, Transition*> transitions;
      vector <string> etiquettes; //tab des différentes étiquette existante
      // map temporaire des etats et transitions
      map<string, Etat*> newEtats;
      map<string, Transition*> newTransitions;


  public :
   bool chargement (string filename);
   bool EstStandard();
   void standardiser();
    bool Estdeterministe();
    void determiniser(string source);
    bool Estcomplet();
    void completer();
    void minimiser();
    void afficher();
    bool uniqueEntree();
    bool reconnaisanceMot();
    void transfer();
    string fusionEntre();
    void langage(string mot);
    ~Automate();


};


#endif // AUTOMATE_H_INCLUDED
