/*
 * voyage.cpp
 *
 *  Created on: 2016-10-01
 *      Author: etudiant
 */

#include "voyage.h"

Voyage::Voyage(const std::vector<std::string>& ligne_gtfs, Ligne* p_ligne) {
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

void Voyage::setServiceId(std::string p_service_id) {
	m_service_id = p_service_id;
}
