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
		liste_sommets.insert({numero, std::make_pair(INFINI,0)});
		liste_sommets_visites.insert({numero,false});
		nbSommets++;
	}
	else{
		throw std::logic_error("Sommet deja existant");
	}
}

void Reseau::enleverSommet(unsigned int numero) throw (std::logic_error) {
	if(sommetExiste(numero)){
		nbArcs -= liste_arcs.find(numero)->second.size();
		liste_arcs.erase(numero);
		liste_sommets.erase(numero);
		liste_sommets_visites.erase(numero);
		nbSommets--;

		for(std::unordered_map<unsigned int,std::list<std::tuple< unsigned int, unsigned int, unsigned int>>>::iterator it = liste_arcs.begin(); it != liste_arcs.end(); ++it){
			enleverArc(it->first, numero);
		}
	}
	else{
		throw std::logic_error("Sommet n'existe pas");
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
			else{
				throw std::logic_error("L'arc existe deja");
			}
		}
		else{
			throw std::logic_error("Sommet de destination n'existe pas");
		}
	}
	else{
		throw std::logic_error("Sommet d'origine n'existe pas");
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
	else{
		throw std::logic_error("L'arc n'existe pas");
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
	else{
		throw std::logic_error("L'arc n'existe pas");
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

int Reseau::getCoutArc(unsigned int numOrigine,
		unsigned int numDestination) const throw (std::logic_error) {
	if(sommetExiste(numOrigine) && sommetExiste(numDestination)){
		const std::list<std::tuple<unsigned int, unsigned int, unsigned int>> & liste_arcs_sommet = liste_arcs.find(numOrigine)->second;

		for(std::list<std::tuple<unsigned int, unsigned int, unsigned int>>::const_iterator it = liste_arcs_sommet.begin(); it != liste_arcs_sommet.end(); ++it){
			if(std::get<0>(*it) == numDestination){
				return std::get<1>(*it);
			}
		}
		throw std::logic_error("arc n'existe pas");
	}
	else{
		throw std::logic_error("Arc n'existe pas");
	}
}

int Reseau::getTypeArc(unsigned int numOrigine,
		unsigned int numDestination) const throw (std::logic_error) {
	if(sommetExiste(numOrigine) && sommetExiste(numDestination)){
		const std::list<std::tuple<unsigned int, unsigned int, unsigned int>> & liste_arcs_sommet = liste_arcs.find(numOrigine)->second;

		for(std::list<std::tuple<unsigned int, unsigned int, unsigned int>>::const_iterator it = liste_arcs_sommet.begin(); it != liste_arcs_sommet.end(); ++it){
			if(std::get<0>(*it) == numDestination){
				return std::get<2>(*it);
			}
		}
		throw std::logic_error("arc n'existe pas");
	}
	else{
		throw std::logic_error("Arc n'existe pas");
	}
}

int Reseau::dijkstra(unsigned int numOrigine, unsigned int numDest,
		std::vector<unsigned int>& chemin) throw (std::logic_error) {

	if(sommetExiste(numOrigine) && sommetExiste(numDest)){

		for(std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int>>::iterator it = liste_sommets.begin(); it != liste_sommets.end(); ++it){
			it->second.first = INFINI;
			it->second.second = 0;
		}

		liste_sommets.find(numOrigine)->second.first = 0;
		liste_sommets.find(numOrigine)->second.second = numOrigine;
		std::unordered_map<unsigned int,std::pair<unsigned int, unsigned int>> liste_sommet_solutionne;
		std::unordered_map<unsigned int,std::pair<unsigned int, unsigned int>> liste_sommet_nonsolutionne = liste_sommets;

		for( int i = 0; i < nbSommets; ++i){
			unsigned int distMin = INFINI;
			unsigned int u = 0;

			//Determine le nouveau sommet solutionne
			for(std::unordered_map<unsigned int,std::pair<unsigned int, unsigned int>>::iterator it = liste_sommet_nonsolutionne.begin(); it != liste_sommet_nonsolutionne.end(); ++it){
				if(it->second.first <= distMin){
					u = it->first;
					distMin = it->second.first;
				}
			}
			liste_sommet_solutionne.insert({u,std::make_pair(liste_sommet_nonsolutionne.find(u)->second.first, liste_sommet_nonsolutionne.find(u)->second.second)});
			liste_sommet_nonsolutionne.erase(u);

			//verifie si on est rendu au sommet destination
			if(u == numDest){
				//verifie si on a trouve un chemin
				if(liste_sommet_solutionne.find(numDest)->second.first != INFINI){
					chemin.push_back(u);
					unsigned int u2 = u;
					while(u2 != numOrigine){
						u2 = liste_sommet_solutionne.find(u2)->second.second;
						chemin.push_back(u2);
					}
					std::reverse(chemin.begin(),chemin.end());
				}
				return liste_sommet_solutionne.find(numDest)->second.first;
			}

			std::list<std::tuple<unsigned int, unsigned int, unsigned int>> & liste_adjacence = liste_arcs.find(u)->second;
			for(std::list<std::tuple<unsigned int, unsigned int, unsigned int>>::iterator it = liste_adjacence.begin(); it != liste_adjacence.end(); ++it){

				//verifie si le sommet adjacent traite ne serais pas deja solutionne
				if(liste_sommet_nonsolutionne.find(std::get<0>(*it)) != liste_sommet_nonsolutionne.end()){

					unsigned int temp = liste_sommet_solutionne.find(u)->second.first + getCoutArc(u,std::get<0>(*it));
					if(temp < liste_sommet_nonsolutionne.find(std::get<0>(*it))->second.first){
						liste_sommet_nonsolutionne.find(std::get<0>(*it))->second.first = temp;
						liste_sommet_nonsolutionne.find(std::get<0>(*it))->second.second = u;
					}
				}
			}
		}
	}
	else{
		throw std::logic_error("Un des sommets est inexistant");
	}
}

int Reseau::bellmanFord(unsigned int numOrigine, unsigned int numDest,
		std::vector<unsigned int>& chemin) throw (std::logic_error) {

	if(sommetExiste(numOrigine) && sommetExiste(numDest)){

		for(std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int>>::iterator it = liste_sommets.begin(); it != liste_sommets.end(); ++it){
			it->second.first = INFINI;
			it->second.second = 0;
		}
		liste_sommets.find(numOrigine)->second.first = 0;

		unsigned int prevDist = liste_sommets.find(numDest)->second.first;
		for(int i = 0; i < (nbSommets-1); ++i){

			for(std::unordered_map<unsigned int,std::list<std::tuple<unsigned int, unsigned int, unsigned int>>>::iterator it = liste_arcs.begin(); it != liste_arcs.end(); ++it){
				std::list<std::tuple<unsigned int, unsigned int, unsigned int>> liste_sommets_adjacents = it->second;
				for(std::list<std::tuple<unsigned int, unsigned int, unsigned int>>::iterator it2 = liste_sommets_adjacents.begin(); it2 != liste_sommets_adjacents.end(); ++it2){
					unsigned int temp = liste_sommets.find(it->first)->second.first + std::get<1>(*it2);

					//verifie si temp < d(v)
					if(temp < liste_sommets.find(std::get<0>(*it2))->second.first){
						liste_sommets.find(std::get<0>(*it2))->second.first = temp;
						liste_sommets.find(std::get<0>(*it2))->second.second = it->first;
					}
				}
			}

			//Vefirie si on a relache tous les arc entre l'origine et la destination
			if(prevDist != INFINI && prevDist == liste_sommets.find(numDest)->second.first){
				break;
			}
			else{
				prevDist = liste_sommets.find(numDest)->second.first;
			}
		}
		//reconstruit le chemin entre les deux sommets
		chemin.push_back(numDest);
		unsigned int u = numDest;
		while(u != numOrigine){
			u = liste_sommets.find(u)->second.second;
			chemin.push_back(u);
		}
		std::reverse(chemin.begin(),chemin.end());

		return liste_sommets.find(numDest)->second.first;
	}
	else{
		throw std::logic_error("Un des sommets n'existe pas");
	}
}

bool Reseau::estFortementConnexe() const {

	std::unordered_map<unsigned int, bool> liste_sommets_visites2 = liste_sommets_visites;

	for(std::unordered_map<unsigned int, bool>::iterator it = liste_sommets_visites2.begin(); it != liste_sommets_visites2.end(); ++it){
		it->second = false;
	}

	std::list<unsigned int> noeud2visite;
	liste_sommets_visites2.begin()->second = true;
	noeud2visite.push_back(liste_sommets_visites2.begin()->first);

	while(!noeud2visite.empty()){
		unsigned int noeudTraite = noeud2visite.back();
		noeud2visite.pop_back();
		std::cout<<noeudTraite<<std::endl;
		std::list<std::tuple<unsigned int, unsigned int, unsigned int>> noeautAdjacents = liste_arcs.find(noeudTraite)->second;
		for(std::list<std::tuple<unsigned int, unsigned int, unsigned int>>::iterator it = noeautAdjacents.begin(); it != noeautAdjacents.end(); ++it){
			if(liste_sommets_visites2.find(std::get<0>(*it))->second == false){
				liste_sommets_visites2.find(std::get<0>(*it))->second = true;
				noeud2visite.push_back(std::get<0>(*it));
			}
		}
	}
	for(std::unordered_map<unsigned int, bool>::iterator it = liste_sommets_visites2.begin(); it != liste_sommets_visites2.end(); ++it){
		if(it->second == false){
			return false;
		}
	}
	return true;
}

int Reseau::getComposantesFortementConnexes(
		std::vector<std::vector<unsigned int> >& composantes) const {
	Reseau grapheInverse;
	std::unordered_map<unsigned int, unsigned int> fin;

	//ajoute les sommest au graphe inverse et construit le unordered_map pour le temps d'abandon lors du parcours du graphe.
	for(std::unordered_map<unsigned int, bool>::const_iterator it = liste_sommets_visites.begin(); it != liste_sommets_visites.end(); ++it){
		grapheInverse.ajouterSommet(it->first);
		fin.insert({it->first, 0});
	}

	for(std::unordered_map<unsigned int, std::list<std::tuple<unsigned int, unsigned int, unsigned int>>>::const_iterator it = liste_arcs.begin(); it != liste_arcs.end(); ++it){
		std::list<std::tuple<unsigned int, unsigned int, unsigned int>> liste_adjacent = it->second;
		for(std::list<std::tuple<unsigned int, unsigned int, unsigned int>>::const_iterator it2 = liste_adjacent.begin(); it2 != liste_adjacent.end(); ++it2){
			grapheInverse.ajouterArc(std::get<0>(*it2), it->first, std::get<1>(*it2), std::get<2>(*it2));
		}
	}




}
