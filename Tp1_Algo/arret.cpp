/*
 * arret.cpp
 *
 *  Created on: 2016-09-29
 *      Author: etudiant
 */

#include "arret.h"

Arret::Arret(const std::vector<std::string>& ligne_gtfs): m_station_id(std::stoi(ligne_gtfs[3])),
m_heure_arrivee(Heure(std::stoi(split(ligne_gtfs[1],':')[0]),std::stoi(split(ligne_gtfs[1],':')[1]),std::stoi(split(ligne_gtfs[1],':')[2]))),
m_heure_depart(Heure(std::stoi(split(ligne_gtfs[2],':')[0]),std::stoi(split(ligne_gtfs[2],':')[1]),std::stoi(split(ligne_gtfs[2],':')[2]))),
m_numero_sequence(std::stoi(ligne_gtfs[4])), m_voyage_id(ligne_gtfs[0]){
}

void Arret::setHeureArrivee(const Heure& p_heureArrivee) {
	Heure m_heure_arrivee(p_heureArrivee);
}

const Heure& Arret::getHeureArrivee() const {
	return m_heure_arrivee;
}

const Heure& Arret::getHeureDepart() const {
	return m_heure_depart;
}

void Arret::setHeureDepart(const Heure& p_heureDepart) {
	Heure m_heure_depart(p_heureDepart);
}

unsigned int Arret::getNumeroSequence() const {
	return m_numero_sequence;
}

void Arret::setNumeroSequence(unsigned int p_numeroSequence) {
	m_numero_sequence = p_numeroSequence;
}

unsigned int Arret::getStationId() const {
	return m_station_id;
}

void Arret::setStationId(unsigned int stationId) {
	m_station_id = stationId;
}

std::string Arret::getVoyageId() const {
	return m_voyage_id;
}

void Arret::setVoyageId(const std::string& voyageId) {
	m_voyage_id = voyageId;
}

bool Arret::operator <(const Arret& p_other) const {
	if(m_numero_sequence < p_other.getNumeroSequence()){
		return true;
	}
	else{
		return false;
	}
}

bool Arret::operator >(const Arret& p_other) const {
	if(m_numero_sequence > p_other.getNumeroSequence()){
		return true;
	}
	else{
		return false;
	}
}
