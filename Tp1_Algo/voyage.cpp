/*
 * voyage.cpp
 *
 *  Created on: 2016-10-01
 *      Author: etudiant
 */

#include "voyage.h"

Voyage::Voyage(const std::vector<std::string>& ligne_gtfs, Ligne* p_ligne): m_id(ligne_gtfs[2]), m_ligne(p_ligne),
	m_service_id(ligne_gtfs[1]), m_destination(ligne_gtfs[3]) {
}

std::vector<Arret> Voyage::getArrets() const {
	return m_arrets;
}

const std::string& Voyage::getDestination() const {
	return m_destination;
}

void Voyage::setDestination(const std::string& p_destination) {
	m_destination = p_destination;
}

std::string Voyage::getId() const {
	return m_id;
}

void Voyage::setId(std::string p_id) {
	m_id = p_id;
}

std::string Voyage::getServiceId() const {
	return m_service_id;
}

Ligne* Voyage::getLigne() const {
	return m_ligne;
}

void Voyage::setLigne(Ligne* p_ligne) {
	m_ligne = p_ligne;
}

void Voyage::setServiceId(std::string p_service_id) {
	m_service_id = p_service_id;
}

Heure Voyage::getHeureDepart() const {
	if(!m_arrets.empty()){
		return m_arrets.begin()->getHeureDepart();
	}
	else{
		throw std::logic_error("No stop registered");
	}
}

Heure Voyage::getHeureFin() const {
	if(m_arrets.size()>1){
		return m_arrets.end()->getHeureArrivee();
	}
	else{
		throw std::logic_error("No stop or only one stop registered.");
	}
}

bool Voyage::operator <(const Voyage& p_other) const {
	if(getHeureDepart() < p_other.getHeureDepart()){
		return true;
	}
	else{
		return false;
	}
}

void Voyage::setArrets(std::vector<Arret>& resultat) {
	m_arrets = resultat;
	std::sort(m_arrets.begin(), m_arrets.end());

	for(std::vector<Arret>::iterator it = m_arrets.begin(); it < m_arrets.end(); ++it){
		if(it->getHeureArrivee() == std::next(it)->getHeureArrivee()){
			std::next(it)->setHeureDepart(std::next(it)->getHeureDepart().add_secondes(30));
			std::next(it)->setHeureArrivee(std::next(it)->getHeureArrivee().add_secondes(30));
		}
	}
}

Arret& Voyage::arretDeLaStation(unsigned int p_num_station) {
	for(std::vector<Arret>::iterator it = m_arrets.begin(); it < m_arrets.end(); ++it){
		if(it->getStationId() == p_num_station){
			return *it;
		}
	}
	throw std::logic_error("No matching station.");
}

bool Voyage::operator >(const Voyage& p_other) const {
	if(getHeureFin() > p_other.getHeureFin()){
		return true;
	}
	else{
		return false;
	}
}
