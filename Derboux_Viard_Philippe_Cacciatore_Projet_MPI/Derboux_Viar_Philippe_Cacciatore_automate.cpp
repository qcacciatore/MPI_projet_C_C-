#include "Derboux_Viar_Philippe_Cacciatore_etat.h"
#include "Derboux_Viar_Philippe_Cacciatore_transition.h"
#include <fstream>
#include <sstream>
#include <vector>
#include "Derboux_Viar_Philippe_Cacciatore_automate.h"
#include <iostream>
#include "Derboux_Viar_Philippe_Cacciatore_groupe.h"

using namespace std;
void tri(string& chaine);

bool Automate :: Estcomplet()
{
    map<string, Etat*>::iterator  itEtat;
    map<string, Etat*>::iterator  itEtat2;
    map <string, Transition*>::iterator itTransition;
    map<string, Transition*>::iterator find(const string & clef);
    int const taille(etiquettes.size());
    int cpt(0);

    for(itEtat = etats.begin() ; itEtat != etats.end() ; ++itEtat) // etat source
    {
        for( int i(0); i<taille; i++) // etiquette
        {
            cpt=0;
            for (itEtat2 = etats.begin() ; itEtat2 != etats.end() ; ++itEtat2) //parcour les etats destination
            {
                itTransition=transitions.find(itEtat->first+etiquettes[i]+itEtat2->first);
                if (itTransition != transitions.end()) // si la transition existe
                {
                    cpt++;
                }
            }
            if (cpt==0) // alors aucune transition n'existe avec cet état de départ et cette etiquette
            {
                cout<<"l'Automate n'est pas complet car aucune transition partant de l'etat: "<<itEtat->first<<" et ayant pour etiquette :"<<etiquettes[i]<<endl<<endl;
                return false;
            }
        }
    }
    return true;
}

void Automate :: completer()
{
    map<string, Etat*>::iterator  itEtat;
    map<string, Etat*>::iterator  itEtat2;
    map <string, Transition*>::iterator itTransition;
    map<string, Transition*>::iterator find(const string & clef);
    int const taille(etiquettes.size());
    int cpt(0);

    etats["P"] = new Etat("P", "-"); // crée un nouvel état poubelle
    for( int i(0); i<taille; i++) // boucle l'état P sur lui même
    {
        transitions["P"+etiquettes[i]+"P"]= new Transition ("P", etiquettes[i], "P");
    }

    for(itEtat = etats.begin() ; itEtat != etats.end() ; ++itEtat) // etat source
    {
        for( int i(0); i<taille; i++) // etiquette
        {
            cpt=0; //compte le nombre de transition existante
            for (itEtat2 = etats.begin() ; itEtat2 != etats.end() ; ++itEtat2) //parcour les etats destination
            {
                itTransition=transitions.find(itEtat->first+etiquettes[i]+itEtat2->first);
                if (itTransition != transitions.end()) // si la transition existe
                {
                    cpt++;
                }
            }
            if (cpt==0) // alors aucune transition n'existe avec cet état de départ et cette etiquette
            {
                //création d'une transition vers l'etat poubelle
                transitions[itEtat->first+etiquettes[i]+"P"]= new Transition (itEtat->first, etiquettes[i], "P");
            }
        }
    }
}


void Automate :: transfer()
{
    map<string, Etat*>::iterator  itEtat;

    for(itEtat = etats.begin() ; itEtat != etats.end() ; ++itEtat)
    {
        delete itEtat->second;
    }

    map <string, Transition*>::iterator itTransition;
    for(itTransition = transitions.begin() ; itTransition != transitions.end() ; ++itTransition)
    {
        delete itTransition->second;
    }


    etats=newEtats;
    transitions=newTransitions;
/*
        for(itEtat = newEtats.begin() ; itEtat != newEtats.end() ; ++itEtat)
        {
            etats[itEtat->first]= new Etat (itEtat->first, itEtat->second->getStatut());
            //delete itEtat->second;
        }

        for(itTransition = newTransitions.begin() ; itTransition != newTransitions.end() ; ++itTransition)
        {
            transitions[itTransition->first]=new Transition (itTransition->second->getSource(), itTransition->second->getEtiquette(), itTransition->second->getDesti());
            //delete itTransition->second;
        }
*/

}

Automate :: ~Automate()
{
    map<string, Etat*>::iterator  itEtat;
    for(itEtat = etats.begin() ; itEtat != etats.end() ; ++itEtat)
    {
        delete itEtat->second;
    }

    map <string, Transition*>::iterator itTransition;
    for(itTransition = transitions.begin() ; itTransition != transitions.end() ; ++itTransition)
    {
        delete itTransition->second;
    }

    map<string, Etat*>::iterator  itnewEtat;
    for(itnewEtat = etats.begin() ; itEtat != etats.end() ; ++itnewEtat)
    {
        delete itnewEtat->second;
    }

    map <string, Transition*>::iterator itnewTransition;
    for(itnewTransition = transitions.begin() ; itTransition != transitions.end() ; ++itnewTransition)
    {
        delete itnewTransition->second;
    }


}

bool Automate :: chargement (string filename)
{
    string file = "Automates/Derboux_Viar_Philippe_Cacciatore#"+filename + ".txt";

    ifstream fichier(file.c_str()); //ouvre le fichier

    if (fichier)  // si l'ouverture à réussis
    {
        string contenu;
        getline(fichier, contenu); // on récupére la 1er ligne
        int nbetiquette;
        nbetiquette = contenu.size();
        nbetiquette -=5;
        nbetiquette = nbetiquette/2;
        for (int i(0); i < nbetiquette; i++)
        {
            etiquettes.push_back("0");
            etiquettes[i]=contenu[(2*i)+6]; // on rentre les différentes étiquettes existance dans un tableau
        }
        string statutp;
        while (fichier>>statutp) // tant qu'il y as une ligne + on lit le statut
        {
            string etatp;
            fichier>>etatp;

            etats[etatp] = new Etat(etatp, statutp); // crée un nouvel état
            for (int i (0); i < nbetiquette; i++)
            {
                string transp;
                fichier>>transp;
                if (transp.size()>1) // si la chaine contient le carractère ,
                {
                    int cb = transp.size();
                    for (int cpt (0); cpt<cb; cpt++)// cas particulier plusieurs etats
                    {
                        transitions[etatp+etiquettes[i]+transp[cpt]]= new Transition (etatp, etiquettes[i], transp.substr(cpt,1));
                        cpt++;
                    }
                }

                else if (transp != "-")
                {
                    transitions[etatp+etiquettes[i]+transp]= new Transition (etatp, etiquettes[i], transp); // créer nouvelle transition
                }
            }
        }


    }
    else
    {
        cout<<"IMPOSSIBLE D'OUVRIR FICHIER"<<endl;
        return false;
    }
}

void Automate :: afficher ()
{
    int const taille(etiquettes.size());

    cout<<" Etats";

    for (int i=0; i <taille ; i++)
    {
        cout<<"      "<<etiquettes[i];
    }
    cout<<endl;
    map<string, Etat*>::iterator  itEtat;
    map <string, Transition*>::iterator itTransition;
    map<string, Etat*>::iterator  itEtat2;
    for(itEtat = etats.begin() ; itEtat != etats.end() ; ++itEtat)
    {

        if (itEtat->second->getStatut()=="ES") // cas particulier pour affichage (espace en moins)
        {
            cout<<itEtat->second->getStatut()<<"   ";
        }
        else
        {
            cout<<itEtat->second->getStatut()<<"    ";
        }
        int cb1 (4);
        cb1-=itEtat->first.size();
        while (cb1>0)
        {
            cb1--;
            cout<<" ";
        }
        cout<<itEtat->first<<"   ";

        for (int i=0; i <taille ; i++)
        {
            int exist=0;
            string trans="";
            for (itEtat2 = etats.begin() ; itEtat2 != etats.end() ; ++itEtat2) //parcour les etats
            {
                map<string, Transition*>::iterator find(const string & clef);
                itTransition=transitions.find(itEtat->first+etiquettes[i]+itEtat2->first);
                if (itTransition != transitions.end()) // la transition existe
                {
                    exist++;
                    if (exist > 1)
                    {
                        trans+=","+itEtat2->first;
                    }
                    else
                    {
                        trans+=itEtat2->first;
                    }
                }
            }
            if (exist==0)
            {
                trans="-";
                exist=1;
            }
            cout<<trans;
            int cb (6);
            cb-=(trans.size()-1);//(2*exist);
            while (cb>0)
            {
                cb--;
                cout<<" ";
            }

        }
        cout<<endl;
    }

}
bool Automate :: uniqueEntree() //vérification de l'existence d'une et une seule entrée
{
    map<string, Etat*>::iterator it; //intitialisation de l'itérateur
    int cpt = 0; //cpt pour le nbre d'entrées
    //string tmp; // tmp pour le nom de l'état
    for(it = etats.begin(); it != etats.end(); ++it) //parcours de la liste des entrées
    {
        if (it->second->getStatut() == "E" || it->second->getStatut() == "ES") //vérification que l'état est bien un entrée
        {
            //tmp = it->second->getnom; //tmp prend le nom de l'état
            cpt++; //incrémentation du compteur ...
        }
        if (cpt>1)
        {
            return false;
        }
    }
    return true;

}

bool Automate ::  Estdeterministe ()
{
    if (uniqueEntree() == true) //vérification de l'existence d'une et une seule entrée
    {
        map<string, Transition*>::iterator it; //intitialisation de l'itérateur
        map<string, Transition*>::iterator it2; //intitialisation de l'itérateur

        for(it = transitions.begin(); it != transitions.end(); ++it) //parcours de la liste des transitions
        {
            for(it2 = transitions.begin(); it2 != transitions.end(); ++it2) //parcours de la deuxième liste des transitions pour trouver une potentielle paire source/transition
            {
                if (it->first != it2->first)
                {
                    // pour ne pas comparer le meme état
                    if  ((it->second->getSource() == it2->second->getSource())&& (it->second->getEtiquette() == it2->second->getEtiquette())) //si cette paire est trouvée, le bool retourn faux.
                    {
                        cout<<"l'automate n'est pas deterministe car plusieurs choix sont possible a patir de l'etat : "<<it->second->getSource()<<"  avec l'etiquette :  "<<it->second->getEtiquette()<<endl<<endl;
                        return false;
                    }
                }
            }
        }
    }
    else
    {
        cout<<"l'automate n'est pas deterministe car il y plus d'une entrée"<<endl;
        return false;   // retourne faux si il y a plus d'une entrée.
    }

    return true;
}

void Automate :: determiniser(string source)
{
    int const nbetiquette(etiquettes.size());
    int taille = source.size();
    map<string, Etat*>::iterator itEtat;
    map<string, Etat*>::iterator itnewEtat;
    map<string, Transition*>::iterator itTransition;
    int statut=0;
    string destination ="";
    for (int i (0); i < nbetiquette; i++)
    {
        destination ="";
        statut=0;
        for (int cpt(0); cpt<taille ; cpt++) // pour tout les etat contenu dans notre source
        {
            for(itEtat = etats.begin(); itEtat != etats.end(); ++itEtat)
            {
                itTransition=transitions.find(source[cpt]+etiquettes[i]+itEtat->first);
                if (itTransition != transitions.end()) // si la transition existe
                {
                    destination+=itEtat->first;
                    if (itEtat->second->getStatut()=="S" || itEtat->second->getStatut()=="ES" )
                    {
                        statut=1;
                    }
                }
            }
        }
        if(destination !="")
        {
            tri(destination);
            newTransitions[source+etiquettes[i]+destination] = new Transition(source, etiquettes[i], destination); // on crée la transition

            itnewEtat=newEtats.find(destination);

            if (itnewEtat == newEtats.end()) // si l'etat n'existe pas
            {
                //on crée l'état
                if(statut==1)//alors l'etat est une sortie
                {
                    newEtats[destination] = new Etat(destination, "S");
                }
                else
                {
                    newEtats[destination] = new Etat(destination, "-");
                }
                determiniser(destination); // on rapelle la fonction avec le nouvelle état

            }
        }
    }
}

string Automate :: fusionEntre()
{
    map<string, Etat*>::iterator itEtat;
    string entree="";
    int statut=0;
    for(itEtat = etats.begin(); itEtat != etats.end(); ++itEtat) //parcours de la liste des entrées
    {
        if (itEtat->second->getStatut() == "E" || itEtat->second->getStatut() == "ES")
        {
            entree+=itEtat->first;
            if (itEtat->second->getStatut() == "ES")
            {
                statut=1;
            }
        }
    }
    tri(entree); // tri les char de la chaine
    if (statut==1)// création d'un état ES
    {
        newEtats[entree] = new Etat (entree,"ES" );
    }
    else // création d'un état entrée
    {
        newEtats[entree] = new Etat(entree,"E" );
    }
    return entree;

}

bool Automate :: EstStandard()
{
    int cpt=0;
    map<string,Etat*>::iterator itetat;
    map<string,Transition*>::iterator ittransition;

    for(itetat = etats.begin() ; itetat != etats.end() ; ++itetat)
    {
        if(itetat->second->getStatut()=="E" || itetat->second->getStatut()=="ES")
        {
            cpt++;

            for(ittransition = transitions.begin() ; ittransition != transitions.end() ; ++ittransition)
            {
                if(ittransition->second->getDesti()== itetat->second->getNom())
                {
                    cout<<"L'automate n'est pas standard une transition pointe sur une entree."<<endl<<endl;
                    return false;
                }
            }
        }
    }

    if(cpt>1)
    {
        cout<<"L'automate n'est pas standard car il y a "<<cpt<<" entrees."<<endl;
        return false;
    }

    return true;
}


void Automate :: standardiser()
{
    map<string,Etat*>::iterator itetat;
    map<string,Transition*>::iterator ittransition;

    etats["i"]= new Etat("i", "E"); //création d'un état entrée pour standardiser


    for(itetat = etats.begin() ; itetat != etats.end() ; ++itetat) //parcourir les états
    {
        if ((itetat->second->getStatut()=="E" || itetat->second->getStatut()=="ES") && itetat->first!="i")  //test si l'état est une entrée ou une entrée/sortie
        {
            for(ittransition = transitions.begin() ; ittransition != transitions.end() ; ++ittransition) //parcourir les transitions
            {
                if (ittransition->second->getSource()==itetat->first) //si la source de ta transition est une entree
                {


                    transitions["i"+ittransition->second->getEtiquette()+ittransition->second->getDesti()]= new Transition ("i", ittransition->second->getEtiquette(), ittransition->second->getDesti());


                    if (itetat->second->getStatut() == "ES") //si l'état est une entrée et une sortie (donc reconnaissance du mot vide)
                    {
                        itetat->second->setStatut("S"); // l'entrée sortie devient une sortie simple
                        etats["i"]->setStatut("ES");//L'état standard doit reconnaitre le mot vide, donc est une entrée/sortie
                    }
                    else itetat->second->setStatut("-"); //si l'état une une entrée simple, il devient un état normal
                }
            }
        }
    }

}

void Automate::minimiser()
{
    map<string,Etat*>::iterator itetat; //on creer un curseur d'objet etats
    map<string,Transition*>::iterator transition1;
    map<string,Transition*>::iterator transition2;
    map<string,Etat*> etatmin; //on creer un curseur d'objet etats
    map<string,Transition*> transmin;
    int validation_minimisation = 0;

    Groups liste;

    int testtemp =0;
    int testtemp2 =0;

    for(itetat = etats.begin() ; itetat != etats.end() ; ++itetat) //parcourir les états
    {
        liste.setname(liste.getnbre(), itetat->first);

        if (itetat->second->getStatut() == "S" ||  itetat->second->getStatut() == "ES")
        {
            liste.setnumgroup(liste.getnbre(),1); //groupe terminal
            testtemp = 1;

        }
        else
        {
            liste.setnumgroup(liste.getnbre(),2); //groupe non terminal
            testtemp2 = 1;
        }

        liste.incnbretats();
    }
    liste.setnbrgroups(testtemp + testtemp2);

    do
    {
        Groups recursiv;

        for (int tmp=1; tmp < liste.getnbrgroups() + 1; tmp++) //on itère les groupes d'états
        {
            if (liste.gettaillegroupe(tmp) == 1) //cas d'un seul element dans le groupe
            {
                for(int temps=0; temps < liste.getnbre(); temps++)
                {
                    if(liste.getnumgroup(temps) == tmp)
                    {
                        recursiv.setnbrgroups(recursiv.getnbrgroups() + 1);
                        recursiv.setname(recursiv.getnbre(), liste.getname(temps));
                        recursiv.setnumgroup(recursiv.getnbre(), recursiv.getnbrgroups());
                        recursiv.incnbretats();
                    }
                }
            }
            else
            {
                for (int tmp2=0; tmp2 < liste.getnbre() - 1; tmp2++) //on parcours la liste des etats de l'automate
                {
                    if(liste.getnumgroup(tmp2) == tmp) //on cherche un etat apartenant au groupe
                    {
                        for (int tmp3 = tmp2+1; tmp3 < liste.getnbre(); tmp3++) //on itere à partir de cet état...
                        {
                            if (liste.getnumgroup(tmp3) == tmp) //les suivants qui appartiendront au meme groupe
                            {
                                string itetat1;
                                string itetat2;
                                int verif_similitudes = 0;

                                for (int tmp4=0; tmp4 < etiquettes.size(); tmp4++)//on compare les transitions des etats choisis
                                {
                                    //etiquette[0]
                                    for(itetat = etats.begin() ; itetat != etats.end() ; ++itetat) //parcourir les états
                                    {
                                        transition1=transitions.find(liste.getname(tmp2)+etiquettes[tmp4]+itetat->first);
                                        transition2 = transitions.find(liste.getname(tmp3)+etiquettes[tmp4]+itetat->first);
                                        if (transition1 != transitions.end()) // la transition existe
                                        {
                                            itetat1 = itetat->first;
                                        }

                                        if (transition2 != transitions.end()) // la transition existe
                                        {
                                            itetat2 = itetat->first;
                                        }
                                    }

                                    if(liste.getnumgroup(itetat1) == liste.getnumgroup(itetat2))
                                    {
                                        verif_similitudes = verif_similitudes + 1;

                                    }
                                }

                                if(recursiv.getnbre() == 0)
                                {
                                    recursiv.setnbrgroups(recursiv.getnbrgroups() + 1);
                                    recursiv.setname(recursiv.getnbre(), liste.getname(tmp2));
                                    recursiv.setnumgroup(recursiv.getnbre(), recursiv.getnbrgroups());
                                    recursiv.incnbretats();

                                    if(verif_similitudes == etiquettes.size()) //si les transitions sont les memes
                                    {
                                        recursiv.setname(recursiv.getnbre(), liste.getname(tmp3));
                                        recursiv.setnumgroup(recursiv.getnbre(), recursiv.getnumgroup(liste.getname(tmp2)));
                                        recursiv.incnbretats();


                                    }
                                    else
                                    {
                                        recursiv.setname(recursiv.getnbre(), liste.getname(tmp3));
                                        recursiv.setnumgroup(recursiv.getnbre(),recursiv.getnumgroup(liste.getname(tmp2)) +1);
                                        recursiv.incnbretats();
                                        recursiv.setnbrgroups(recursiv.getnbrgroups() + 1);

                                    }
                                }
                                else
                                {
                                    if(verif_similitudes == etiquettes.size()) //si les transitions sont les memes
                                    {
                                        if (recursiv.elexist(liste.getname(tmp2)) == false)
                                        {
                                            recursiv.setname(recursiv.getnbre(), liste.getname(tmp2));
                                            recursiv.setnumgroup(recursiv.getnbre(), recursiv.getnbrgroups() +1);
                                            recursiv.setnbrgroups(recursiv.getnbrgroups() + 1);
                                            recursiv.incnbretats();


                                        }

                                        if (recursiv.elexist(liste.getname(tmp3)) == true)
                                        {
                                            recursiv.setnumgroup(recursiv.getnumetat(liste.getname(tmp3)), recursiv.getnumgroup(liste.getname(tmp2)));

                                        }
                                        else
                                        {
                                            recursiv.setname(recursiv.getnbre(), liste.getname(tmp3));
                                            recursiv.setnumgroup(recursiv.getnbre(), recursiv.getnumgroup(liste.getname(tmp2)));
                                            recursiv.incnbretats();

                                        }

                                    }
                                    else
                                    {
                                        if (recursiv.elexist(liste.getname(tmp2)) == false)
                                        {
                                            recursiv.setname(recursiv.getnbre(), liste.getname(tmp2));
                                            recursiv.setnumgroup(recursiv.getnbre(), recursiv.getnbrgroups() +1);
                                            recursiv.setnbrgroups(recursiv.getnbrgroups() + 1);
                                            recursiv.incnbretats();

                                        }

                                        if (recursiv.elexist(liste.getname(tmp3)) == false)
                                        {
                                            recursiv.setname(recursiv.getnbre(), liste.getname(tmp3));
                                            recursiv.setnumgroup(recursiv.getnbre(), recursiv.getnbrgroups() + 1);
                                            recursiv.setnbrgroups(recursiv.getnbrgroups() + 1);
                                            recursiv.incnbretats();


                                        }
                                    }
                                }

                            }
                        }
                    }
                }
            }
        }
        if (liste.getnbrgroups() == recursiv.getnbrgroups())
        {
            liste = recursiv;
            validation_minimisation = 1;
        }
        else
        {
            liste = recursiv;
        }
    }
    while(validation_minimisation == 0);
    if (validation_minimisation == 1)
    {
        //-----LISTE A RECUPERER POUR AFFICHAGE D'AUTOMATE MINIMISE-----
        cout << endl << "l'automate est donc bien minimise!";
        cout << endl;
        cout << "groupes des etats : ";
        for (int x=0; x < liste.getnbre(); x++)
        {
            cout << liste.getname(x) << " - " << liste.getnumgroup(x) << ", ";
        }
        cout << endl;
        cout << "nombre de groupes apres minimisation: " << liste.getnbrgroups() << endl;

        for (int tmp=1; tmp < liste.getnbrgroups() + 1; tmp++) //on liste les groupes
        {
            string statut="-";

            for(int tmp2=0; tmp2 < liste.getnbre(); tmp2++) //on liste les elements
            {
                if (liste.getnumgroup(tmp2) == tmp)
                {
                    if (etats[liste.getname(tmp2)]->getStatut()=="ES" || (statut=="S" && etats[liste.getname(tmp2)]->getStatut()=="E") || (statut=="E" && etats[liste.getname(tmp2)]->getStatut()=="S"))
                    {
                        statut="ES";
                    }
                    else if(etats[liste.getname(tmp2)]->getStatut()=="S" && statut!="ES" )
                    {
                        statut="S";
                    }
                    else if(etats[liste.getname(tmp2)]->getStatut()=="E" && statut !="ES")
                    {
                        statut="E";
                    }
                    for (int i(0); i< etiquettes.size(); i++)
                    {
                        for(itetat = etats.begin() ; itetat != etats.end() ; ++itetat) // etat source
                        {
                            transition1=transitions.find(liste.getname(tmp2)+etiquettes[i]+itetat->first);

                            if (transition1 != transitions.end()) // si la transition existe
                            {
                                ostringstream oss1;
                                ostringstream oss2;
                                oss1 << tmp;
                                oss2 << liste.getnumgroup(itetat->first);
                                string temp = oss1.str();
                                string temp2 = oss2.str();
                                transmin[temp+etiquettes[i]+ temp2]= new Transition (temp, etiquettes[i], temp2);

                                //cout<<transitions[liste.getname(tmp2)+etiquettes[i]+itetat->first];
                            }

                        }
                    }
                    /*
                    for(itetat = etats.begin() ; itetat != etats.end() ; ++itetat) // etat source
                    {
                        for(int x=1; x < liste.getnbrgroups() + 1; x++
                        {
                            if(itetat->first == groupr)
                        }
                        if(itetat->first !=)
                        delete itetat->second;
                    }
                    */

                }

                string temp;
                ostringstream oss;
                oss << tmp;
                temp = oss.str();
                etatmin[temp]= new Etat(temp, statut); // on crée l'état du groupe correspondant

            }
        }

    }
    etats=etatmin;
    transitions=transmin;
}

void Automate :: langage(string mot)
{
    map<string,Etat*>::iterator itetat;
    map<string,Transition*>::iterator itTransition;

    int     taille =mot.size(); // on calcule la taille de mot
    string entree="";

    if (mot == "0") // test du mot vide
    {
        for(itetat = etats.begin() ; itetat != etats.end() ; ++itetat) //parcourir les états
        {
            if (itetat->second->getStatut()=="ES")
            {
                cout<<"l'automate reconnait le mot vide "<<endl;;
                return;
            }
        }
        cout<<"l'automate ne reconnait pas le mot vide "<<endl;
        return;
    }

    for(itetat = etats.begin() ; itetat != etats.end() ; ++itetat) //parcourir les états
    {
        if (itetat->second->getStatut()=="ES" || itetat->second->getStatut()=="E"  ) // on cherche l'entrée
        {
            entree= itetat -> first;
        }
    }
    //boucle pour lire le mot
    for (int i(0); i<taille; i++)
    {
        for(itetat = etats.begin() ; itetat != etats.end() ; ++itetat) //parcourir les états
        {
            itTransition=transitions.find(entree+mot[i]+itetat->first);
            if (itTransition != transitions.end()) // si la transition existe
            {
                entree=itetat->first;
                break; // on stop la boucle for
            }
        }
        if(itetat==etats.end())
        {
            cout<<"le langage n'est pas reconnut par l'automate"<<endl;
        }
    }
    if (etats[entree]->getStatut()=="S" || etats[entree]->getStatut()=="ES" )
    {
        cout<<"le langage est reconnu par l'automate"<<endl;
    }
    else
    {
        cout<<"le mot rentre ne permet pas d'aboutir a une sortie"<<endl;
    }

}
