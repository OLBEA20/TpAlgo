/*
 * arret.cpp
 *
 *  Created on: 2016-09-29
 *      Author: etudiant
 */

#include "arret.h"

Arret::Arret(const std::vector<std::string>& ligne_gtfs){
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
