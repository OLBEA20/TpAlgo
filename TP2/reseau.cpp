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

	std::vector<std::vector<unsigned int>> paramRemplissage;

	if(getComposantesFortementConnexes(paramRemplissage) == 1){
		return true;
	}
	else{
		return false;
	}
}

int Reseau::getComposantesFortementConnexes(
		std::vector<std::vector<unsigned int> >& composantes) const {
	std::list<unsigned int> fin;
	std::unordered_map<unsigned int, bool> sommetVisitee;

	std::unordered_map<unsigned int, std::list<std::tuple< unsigned int, unsigned int, unsigned int>>> grapheInverse;
	//ajoute les sommest au graphe inverse et construit le unordered_map pour le temps d'abandon lors du parcours du graphe.
	for(std::unordered_map<unsigned int, bool>::const_iterator it = liste_sommets_visites.begin(); it != liste_sommets_visites.end(); ++it){
		std::list<std::tuple<unsigned int, unsigned int, unsigned int>> arcs;
		grapheInverse.insert({it->first, arcs});
		sommetVisitee.insert({it->first, false});
	}

	//ajout des arcs au graphe inverse
	for(std::unordered_map<unsigned int, std::list<std::tuple<unsigned int, unsigned int, unsigned int>>>::const_iterator it = liste_arcs.begin(); it != liste_arcs.end(); ++it){
		std::list<std::tuple<unsigned int, unsigned int, unsigned int>> liste_adjacent = it->second;
		for(std::list<std::tuple<unsigned int, unsigned int, unsigned int>>::const_iterator it2 = liste_adjacent.begin(); it2 != liste_adjacent.end(); ++it2){
			grapheInverse.find(std::get<0>(*it2))->second.push_back(std::make_tuple(it->first, std::get<1>(*it2), std::get<2>(*it2)));
		}
	}
	std::vector<std::vector<unsigned int>> vBuffer;
	for(std::unordered_map<unsigned int, bool>::iterator it = sommetVisitee.begin(); it != sommetVisitee.end(); ++it){
		if(!it->second){
			std::vector<unsigned int> vBuffer2;
			vBuffer.push_back(vBuffer2);
			const_cast<Reseau*>( this )->explore(sommetVisitee, grapheInverse, vBuffer, fin, it->first, 0);
		}
	}

	for(std::unordered_map<unsigned int, bool>::iterator it = sommetVisitee.begin(); it != sommetVisitee.end(); ++it){
		it->second = false;
	}

	std::list<unsigned int> buffer;
	std::unordered_map<unsigned int, std::list<std::tuple<unsigned int, unsigned int, unsigned int>>> copie_liste_arcs = liste_arcs;
	int nbComposante = 0;
	for(std::list<unsigned int>::reverse_iterator it = fin.rbegin(); it != fin.rend(); ++it){
		if(!sommetVisitee.find(*it)->second){
			std::vector<unsigned int> v;
			composantes.push_back(v);
			const_cast<Reseau*>( this )->explore(sommetVisitee, copie_liste_arcs,  composantes, buffer, *it, nbComposante);
			nbComposante++;
		}
	}

	return nbComposante;
}

void Reseau::explore(std::unordered_map<unsigned int, bool> & graphe ,
			std::unordered_map<unsigned int, std::list<std::tuple< unsigned int, unsigned int, unsigned int>>> & grapheInverse, std::vector<std::vector<unsigned int> >& composantes,
			std::list<unsigned int> & fin, unsigned int v, unsigned int index) {
	graphe.find(v)->second = true;
	composantes[index].push_back(v);
	std::list<std::tuple<unsigned int, unsigned int, unsigned int>> sommentAdjacents = grapheInverse.find(v)->second;
	for(std::list<std::tuple<unsigned int, unsigned int, unsigned int>>::iterator it2 = sommentAdjacents.begin(); it2 != sommentAdjacents.end(); ++it2){
		if(!graphe.find(std::get<0>(*it2))->second){
			explore(graphe, grapheInverse, composantes, fin, std::get<0>(*it2), index);
		}
	}
	fin.push_back(v);
}
