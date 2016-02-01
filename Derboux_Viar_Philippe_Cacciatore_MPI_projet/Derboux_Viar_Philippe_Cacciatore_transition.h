#ifndef TRANSITION_H_INCLUDED
#define TRANSITION_H_INCLUDED

using namespace std;

class Transition
{
    private:
        string source;
        string destination;
        string etiquette;

    public:

        string getSource();
        string getDesti();
        string getEtiquette();
        void setSource(string psource);
        Transition(string sourcep, string etiquettep, string destinationp);
};


#endif // TRANSITION_H_INCLUDED
