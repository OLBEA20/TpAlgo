/*
 * auxiliaires.cpp
 *
 *  Created on: 2016-09-28
 *      Author: etudiant
 */

#include "auxiliaires.h"
#include <time.h>
#include <sstream>


std::vector<std::string> split(const std::string& s, char delim) {
	std::vector<std::string> output;
    std::stringstream is;
    is.str(s);
    std::string item;
    while (getline(is, item, delim)) {
        output.push_back(item);
    }
	return output;
}

void lireFichier(std::string nomFichier,
		std::vector<std::vector<std::string> >& resultats, char delimiteur,
		bool rm_entete) {

	std::ifstream folder(nomFichier, std::ios::in);
	if(folder){
		std::string item;
		while(getline(folder, item)){
			resultats.push_back(split(item, delimiteur));
		}
		if(rm_entete){
			resultats.erase(resultats.begin());
		}
	}
	else{
		throw std::logic_error("Error");
	}
}

Date::Date(){
	time_t seconds = time(NULL);
	struct tm *timeinfo = localtime(&seconds);
	m_jour = timeinfo->tm_mday;
	m_mois = timeinfo->tm_mon + 1;
	m_an = timeinfo->tm_year + 1900;
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
	return flux << std::setw(4) << std::setfill('0') << p_date.m_an << "-" << std::setw(2) << std::setfill('0') <<
			p_date.m_mois << "-" << std::setw(2) << std::setfill('0') << p_date.m_jour;
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

	if(m_sec >= 60){
		correction = m_sec/60;
		m_min += correction;
		m_sec-=(correction*60);
	}
	if(m_min >= 60){
		correction = m_min/60;
		m_heure += correction;
		m_min -= (correction*60);
	}
	if(m_heure >= 30){
		correction = m_heure/30;
		m_heure -= (correction*30);
	}
}

Heure Heure::add_secondes(unsigned int secs) const {
	Heure heure(m_heure, m_min, m_sec + secs);

	return heure;
}
std::ostream & operator<<(std::ostream & flux, const Heure & p_heure){

	return flux << std::setw(2)<< std::setfill('0') <<  p_heure.m_heure << ":" << std::setw(2) << std::setfill('0') << p_heure.m_min
			<< ":" << std::setw(2)<< std::setfill('0') << p_heure.m_sec;
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
