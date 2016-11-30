#include <iostream>
#include "coordonnees.h"
#include "reseau.h"
#include <vector>
#include "investigation.h"

using namespace std;



int main() {
    GestionnaireInvestigation rtc("googletransit");

    cout << "Temps moyen de dijsktra " << rtc.tester_n_paires_dijsktra(10) << endl;

    cout << "Temps moyen de bellman " << rtc.tester_n_paires_bellman(10) << endl;

    cout << "Temps moyen de meilleur plus cour chemin " << rtc.tester_n_paires_meilleurPlusCourtChemin(10) << endl;

    /*Reseau reseau;

    reseau.ajouterSommet(1);
    reseau.ajouterSommet(2);
    reseau.ajouterSommet(3);
    reseau.ajouterSommet(4);
    reseau.ajouterSommet(5);
    reseau.ajouterSommet(6);

    reseau.ajouterArc(1,2,4);
    reseau.ajouterArc(1,3,2);
    reseau.ajouterArc(2,1,4);
    reseau.ajouterArc(2,3,1);
    reseau.ajouterArc(2,4,5);
    reseau.ajouterArc(3,1,2);
    reseau.ajouterArc(3,2,1);
    reseau.ajouterArc(3,4,8);
    reseau.ajouterArc(3,5,10);
    reseau.ajouterArc(4,2,5);
    reseau.ajouterArc(4,3,8);
    reseau.ajouterArc(4,5,2);
    //reseau.ajouterArc(4,6,6);
    reseau.ajouterArc(5,3,10);
    reseau.ajouterArc(5,4,2);
    //reseau.ajouterArc(5,6,3);
    reseau.ajouterArc(6,4,6);
    reseau.ajouterArc(6,5,3);

    vector<unsigned int> chemin;

    cout << reseau.meilleurPlusCourtChemin(1,6,chemin) << endl;

    for(auto sommet: chemin){
    	cout << sommet << endl;
    }*/

    return 0;
}
