#include <iostream>
#include <map>
#include <string>
#include "Derboux_Viar_Philippe_Cacciatore_transition.h"
using namespace std;

Transition :: Transition(string sourcep, string etiquettep, string destinationp) : source(sourcep), etiquette(etiquettep), destination(destinationp){};


string Transition :: getSource()
{
    return source;
}

string Transition ::getDesti()
{
    return destination;
}

string Transition ::getEtiquette()
{
    return etiquette;
}

void Transition :: setSource(string psource)
{
    source= psource;
}
