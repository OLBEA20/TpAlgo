/*
 * auxiliaires.cpp
 *
 *  Created on: 2016-09-28
 *      Author: etudiant
 */

#include "auxiliaires.h"
#include <time.h>

std::vector<std::string> split(const std::string& s, char delim) {
	std::vector<std::string> output;
	return output;
}

void lireFichier(std::string nomFichier,
		std::vector<std::vector<std::string> >& resultats, char delimiteur,
		bool rm_entete) {
}

Date::Date(){
	time_t seconds = time(NULL);
	struct tm *timeinfo = localtime(&seconds);
	m_jour = timeinfo->tm_mday;
	m_mois = timeinfo->tm_mon;
	m_an = timeinfo->tm_year;
}

Date::Date(unsigned int an, unsigned int mois, unsigned int jour): m_an(an), m_mois(mois), m_jour(jour) {
}

bool Date::operator ==(const Date& other) const {
	if( other.m_an == m_an && other.m_mois == m_mois && other.m_jour == m_jour){
		return true;
	}
	else{
		return false;
	}
}

bool Date::operator <(const Date& other) const {
	if(m_an < other.m_an){
		return true;
	}
	else if(m_an == other.m_an && m_mois < other.m_mois){
		return true;
	}
	else if(m_mois == other.m_mois && m_jour < other.m_jour){
		return true;
	}
	else{
		return false;
	}
}

bool Date::operator >(const Date& other) const {
	if(m_an > other.m_an){
		return true;
	}
	else if(m_an == other.m_an && m_mois > other.m_mois){
		return true;
	}
	else if(m_mois == other.m_mois && m_jour > other.m_jour){
		return true;
	}
	else{
		return false;
	}

}

std::ostream& operator<<(std::ostream & flux, const Date & p_date){
	return flux << p_date.m_an << "-" << p_date.m_mois << "-" << p_date.m_jour;
}

Heure::Heure() {
	time_t seconds = time(NULL);
	struct tm *timeinfo = localtime(&seconds);
	m_sec = timeinfo->tm_sec;
	m_min = timeinfo->tm_min;
	m_heure = timeinfo->tm_hour;
}

Heure::Heure(unsigned int heure, unsigned int min, unsigned int sec):m_heure(heure), m_min(min), m_sec(sec)  {
	int correction;

	if(m_sec > 60){
		correction = m_sec/60;
		m_min += correction;
		m_sec-=(correction*60);
	}
	if(m_min > 60){
		correction = m_min/60;
		m_heure += correction;
		m_min -= (correction*60);
	}
	if(m_heure > 30){
		correction = m_heure/30;
		m_heure -= (correction*30);
	}
	if(m_heure == 30 && (m_min > 0 || m_sec > 0)){
		m_heure = 0;
	}
}

Heure Heure::add_secondes(unsigned int secs) const {
	Heure heure(m_heure, m_min, m_sec + secs);

	return heure;
}
std::ostream & operator<<(std::ostream & flux, const Heure & p_heure){
	return flux << p_heure.m_heure << ":" << p_heure.m_min << ":" << p_heure.m_sec;
}

bool Heure::operator ==(const Heure& other) const {
	if(m_heure == other.m_heure && m_min == other.m_min && m_sec == other.m_sec){
		return true;
	}
	else{
		return false;
	}
}

bool Heure::operator <(const Heure& other) const {
	if(m_heure < other.m_heure){
		return true;
	}
	else if(m_heure == other.m_heure && m_min < other.m_min){
		return true;
	}
	else if(m_min == other.m_min && m_sec < other.m_sec){
		return true;
	}
	else{
		return false;
	}
}

bool Heure::operator >(const Heure& other) const {
	if(m_heure > other.m_heure){
		return true;
	}
	else if(m_heure == other.m_heure && m_min > other.m_min){
		return true;
	}
	else if(m_min == other.m_min && m_sec > other.m_sec){
		return true;
	}
	else{
		return false;
	}
}

bool Heure::operator <=(const Heure& other) const {
	if(m_heure < other.m_heure){
		return true;
	}
	else if(m_heure == other.m_heure && m_min < other.m_min){
		return true;
	}
	else if(m_min == other.m_min && m_sec < other.m_sec){
		return true;
	}
	else if(m_heure == other.m_heure && m_min == other.m_min && m_sec == other.m_sec){
		return true;
	}
	else{
		return false;
	}
}

bool Heure::operator >=(const Heure& other) const {
	if(m_heure > other.m_heure){
		return true;
	}
	else if(m_heure == other.m_heure && m_min > other.m_min){
		return true;
	}
	else if(m_min == other.m_min && m_sec > other.m_sec){
		return true;
	}
	else if(m_heure == other.m_heure && m_min == other.m_min && m_sec == other.m_sec){
		return true;
	}
	else{
		return false;
	}
}

int Heure::operator -(const Heure& other) const {
	int difference = ((m_heure - other.m_heure)*3600 + (m_min-other.m_min)*60 + (m_sec- other.m_sec));
	return difference;
}
