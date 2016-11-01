/*
 * reseau.cpp
 *
 *  Created on: 2016-10-31
 *      Author: etudiant
 */

#include "reseau.h"

Reseau::Reseau():nbSommets(0), nbArcs(0) {
}

void Reseau::ajouterSommet(unsigned int numero) throw (std::logic_error) {
	if(liste_arcs.find(numero) != liste_arcs.end()){
		std::list<std::tuple<unsigned int, unsigned int, unsigned int>> arcs;
		liste_arcs.insert({numero, arcs});
		nbSommets++;
	}
}

void Reseau::enleverSommet(unsigned int numero) throw (std::logic_error) {
	if(liste_arcs.find(numero) != liste_arcs.end()){
		liste_arcs.erase(numero);
		nbSommets--;
	}
}

void Reseau::ajouterArc(unsigned int numOrigine, unsigned int numDest,
		unsigned int cout, unsigned int type) throw (std::logic_error) {

	//verifie si le sommet d'origine est present
	if(liste_arcs.find(numOrigine) != liste_arcs.end()){
		std::list<std::tuple<unsigned int, unsigned int, unsigned int>> & liste_arcs_sommet = liste_arcs.find(numOrigine)->second;

		//verifie si l'arc n'est pas deja present
		if(std::find(liste_arcs_sommet.begin(),liste_arcs_sommet.end(), std::make_tuple(numDest, cout, type)) == liste_arcs_sommet.end()){
			liste_arcs.find(numOrigine)->second.push_back(std::make_tuple(numDest, cout, type));
			nbArcs++;
		}
	}
}

void Reseau::enleverArc(unsigned int numOrigine, unsigned int numDest)
		throw (std::logic_error) {

	//verifie si l'arc est present
	if(liste_arcs.find(numOrigine) != liste_arcs.end()){
		std::list<std::tuple<unsigned int, unsigned int, unsigned int>> & liste_arcs_sommet = liste_arcs.find(numOrigine)->second;

		//trouve les arcs correspondant a la destination et les supprime
		for(std::list<std::tuple<unsigned int, unsigned int, unsigned int>>::iterator it = liste_arcs_sommet.begin(); it != liste_arcs_sommet.end(); it++){
			if(std::get<0>(*it) == numDest){
				liste_arcs_sommet.erase(it);
				nbArcs--;
			}
		}
	}
}
