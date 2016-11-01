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
	if(!sommetExiste(numero)){
		std::list<std::tuple<unsigned int, unsigned int, unsigned int>> arcs;
		liste_arcs.insert({numero, arcs});
		nbSommets++;
	}
}

void Reseau::enleverSommet(unsigned int numero) throw (std::logic_error) {
	if(sommetExiste(numero)){
		nbArcs -= liste_arcs.find(numero)->second.size();
		liste_arcs.erase(numero);
		nbSommets--;

		for(std::unordered_map<unsigned int,std::list<std::tuple< unsigned int, unsigned int, unsigned int>>>::iterator it = liste_arcs.begin(); it != liste_arcs.end(); ++it){
			enleverArc(it->first, numero);
		}
	}
}

void Reseau::ajouterArc(unsigned int numOrigine, unsigned int numDest,
		unsigned int cout, unsigned int type) throw (std::logic_error) {

	//verifie si le sommet d'origine est present
	if(sommetExiste(numOrigine)){
		std::list<std::tuple<unsigned int, unsigned int, unsigned int>> & liste_arcs_sommet = liste_arcs.find(numOrigine)->second;

		//verifie si le sommet de destination existe
		if(sommetExiste(numDest)){
		//verifie si l'arc n'est pas deja present
			if(std::find(liste_arcs_sommet.begin(),liste_arcs_sommet.end(), std::make_tuple(numDest, cout, type)) == liste_arcs_sommet.end()){
				liste_arcs.find(numOrigine)->second.push_back(std::make_tuple(numDest, cout, type));
				nbArcs++;
			}
		}
	}
}

void Reseau::enleverArc(unsigned int numOrigine, unsigned int numDest)
		throw (std::logic_error) {

	//verifie si l'arc est present
	if(sommetExiste(numOrigine)){
		std::list<std::tuple<unsigned int, unsigned int, unsigned int>> & liste_arcs_sommet = liste_arcs.find(numOrigine)->second;

		//trouve les arcs correspondant a la destination et les supprime
		for(std::list<std::tuple<unsigned int, unsigned int, unsigned int>>::iterator it = liste_arcs_sommet.begin(); it != liste_arcs_sommet.end(); ++it){
			if(std::get<0>(*it) == numDest){
				it = liste_arcs_sommet.erase(it);
				nbArcs--;
			}
		}
	}
}

void Reseau::majCoutArc(unsigned int numOrigine, unsigned int numDest,
		unsigned int cout) throw (std::logic_error) {

	//vefifie si le somment d'origine est present
	if(sommetExiste(numOrigine)){
		std::list<std::tuple<unsigned int, unsigned int, unsigned int>> & liste_arcs_sommet = liste_arcs.find(numOrigine)->second;

		//Trouve l'arc en trouvant la destination correspondante et met a jour le cout de l'arc.
		for(std::list<std::tuple<unsigned int, unsigned int, unsigned int>>::iterator it = liste_arcs_sommet.begin(); it != liste_arcs_sommet.end(); ++it){
			if(std::get<0>(*it) == numDest){
				std::get<1>(*it) = cout;
			}
		}
	}
}

int Reseau::nombreSommets() const {
	return nbSommets;
}

int Reseau::nombreArcs() const {
	return nbArcs;
}

bool Reseau::estVide() const {
	if(nbSommets == 0){
		return true;
	}
	else{
		return false;
	}
}

bool Reseau::sommetExiste(unsigned int numero) const {
	if(liste_arcs.find(numero) == liste_arcs.end()){
		return false;
	}
	else{
		return true;
	}
}

bool Reseau::arcExiste(unsigned int numOrigine, unsigned int numDest) const
		throw (std::logic_error) {
	if(sommetExiste(numOrigine) && sommetExiste(numDest)){
		const std::list<std::tuple<unsigned int, unsigned int, unsigned int>> & liste_arcs_sommet = liste_arcs.find(numOrigine)->second;

		for(std::list<std::tuple<unsigned int, unsigned int, unsigned int>>::const_iterator it = liste_arcs_sommet.begin(); it != liste_arcs_sommet.end(); ++it){
			if(std::get<0>(*it) == numDest){
				return true;
			}
		}
		// l'arc n'a pas ete trouve elle n'existe donc pas
		return false;
	}
	else{
		return false;
	}
}
