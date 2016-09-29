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
	setJour(timeinfo->tm_mday);
	setMois(timeinfo->tm_mon + 1);
	setAn(1900 + timeinfo->tm_year);
}

Date::Date(unsigned int an, unsigned int mois, unsigned int jour): m_an(an), m_mois(mois), m_jour(jour) {
}

bool Date::operator ==(const Date& other) const {
	if( other.getAn() == getAn() && other.getMois() == getMois() && other.getJour() == getJour()){
		return true;
	}
	else{
		return false;
	}
}

bool Date::operator <(const Date& other) const {
	if(getAn() < other.getAn()){
		return true;
	}
	else if(getAn() == other.getAn() && getMois() < other.getMois()){
		return true;
	}
	else if(getMois() == other.getMois() && getJour() < other.getJour()){
		return true;
	}
	else{
		return false;
	}
}

bool Date::operator >(const Date& other) const {
	if(getAn() > other.getAn()){
		return true;
	}
	else if(getAn() == other.getAn() && getMois() > other.getMois()){
		return true;
	}
	else if(getMois() == other.getMois() && getJour() > other.getJour()){
		return true;
	}
	else{
		return false;
	}

}

unsigned int Date::getAn() const {
	return m_an;
}

void Date::setAn(unsigned int an) {
	m_an = an;
}

unsigned int Date::getJour() const {
	return m_jour;
}

void Date::setJour(unsigned int jour) {
	m_jour = jour;
}

unsigned int Date::getMois() const {
	return m_mois;
}

void Date::setMois(unsigned int mois) {
	m_mois = mois;
}

std::ostream& operator<<(std::ostream & flux, const Date & p_date){
	return flux << p_date.m_an << "-" << p_date.m_mois << "-" << p_date.m_jour;
}

Heure::Heure() {
	time_t seconds = time(NULL);
	struct tm *timeinfo = localtime(&seconds);
	setSec(timeinfo->tm_sec);
	setMin(timeinfo->tm_min);
	setHeure(timeinfo->tm_hour);
}

Heure::Heure(unsigned int heure, unsigned int min, unsigned int sec):m_heure(heure), m_min(min), m_sec(sec)  {
	int correction;

	if(getSec() > 60){
		correction = getSec()/60;
		setMin(getMin() + correction);
		setSec(getSec()- correction*60);
	}
	if(getMin() > 60){
		correction = getMin()/60;
		setHeure(getHeure() + correction);
		setMin(getMin() - correction*60);
	}
	if(getHeure() > 30){
		correction = getHeure()/30;
		setHeure(getHeure() - correction*30);
	}
	if(getHeure() == 30 && (getMin() > 0 || getSec() > 0)){
		setHeure(0);
	}
}

Heure Heure::add_secondes(unsigned int secs) const {
	Heure heure(m_heure, m_min, m_sec + secs);

	return heure;
}
std::ostream & operator<<(std::ostream & flux, const Heure & p_heure){
	return flux << p_heure.m_heure << ":" << p_heure.m_min << ":" << p_heure.m_sec;
}

unsigned int Heure::getHeure() const {
	return m_heure;
}

void Heure::setHeure(unsigned int heure) {
	m_heure = heure;
}

unsigned int Heure::getMin() const {
	return m_min;
}

void Heure::setMin(unsigned int min) {
	m_min = min;
}

unsigned int Heure::getSec() const {
	return m_sec;
}

void Heure::setSec(unsigned int sec) {
	m_sec = sec;
}

bool Heure::operator ==(const Heure& other) const {
	if(getHeure() == other.getHeure() && getMin() == other.getMin() && getSec() == other.getSec()){
		return true;
	}
	else{
		return false;
	}
}

bool Heure::operator <(const Heure& other) const {
	if(getHeure() < other.getHeure()){
		return true;
	}
	else if(getHeure() == other.getHeure() && getMin() < other.getMin()){
		return true;
	}
	else if(getMin() == other.getMin() && getSec() < other.getSec()){
		return true;
	}
	else{
		return false;
	}
}

bool Heure::operator >(const Heure& other) const {
	if(getHeure() > other.getHeure()){
		return true;
	}
	else if(getHeure() == other.getHeure() && getMin() > other.getMin()){
		return true;
	}
	else if(getMin() == other.getMin() && getSec() > other.getSec()){
		return true;
	}
	else{
		return false;
	}
}

bool Heure::operator <=(const Heure& other) const {
	if(getHeure() < other.getHeure()){
		return true;
	}
	else if(getHeure() == other.getHeure() && getMin() < other.getMin()){
		return true;
	}
	else if(getMin() == other.getMin() && getSec() < other.getSec()){
		return true;
	}
	else if(getHeure() == other.getHeure() && getMin() == other.getMin() && getSec() == other.getSec()){
		return true;
	}
	else{
		return false;
	}
}

bool Heure::operator >=(const Heure& other) const {
	if(getHeure() > other.getHeure()){
		return true;
	}
	else if(getHeure() == other.getHeure() && getMin() > other.getMin()){
		return true;
	}
	else if(getMin() == other.getMin() && getSec() > other.getSec()){
		return true;
	}
	else if(getHeure() == other.getHeure() && getMin() == other.getMin() && getSec() == other.getSec()){
		return true;
	}
	else{
		return false;
	}
}

int Heure::operator -(const Heure& other) const {
	int difference = ((getHeure() - other.getHeure())*3600 + (getMin()-other.getMin())*60 + (getSec()- other.getSec()));
	return difference;
}
