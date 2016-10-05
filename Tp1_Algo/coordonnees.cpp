/*
 * arret.cpp
 *
 *  Created on: 2016-09-29
 *      Author: etudiant
 */

#include "coordonnees.h"
#include <cmath>

Coordonnees::Coordonnees(double latitude, double longitude)
{
	if(is_valide_coord(latitude, longitude))
	{
		m_latitude = latitude;
		m_longitude = longitude;
	}
	else
	{
		//ne creer pas lobjet ??
		m_latitude = 0;
		m_longitude = 0;
	}
}
double Coordonnees::getLatitude() const
{
	return m_latitude;
}
void Coordonnees::setLatitude(double p_latitude)
{
	if(!(p_latitude < -90 || p_latitude > 90))
		m_latitude = p_latitude;
}
double Coordonnees::getLongitude() const
{
	return m_longitude;
}
void Coordonnees::setLongitude(double p_longitude)
{
	if(!(p_longitude < -180 || p_longitude > 180))
		m_longitude = p_longitude
}
static bool Coordonnees::is_valide_coord(double p_latitude, double p_longitude)
{
	if(p_latitude < -90 || p_latitude > 90)
		return false;
	if(p_longitude < -180 || p_longitude > 180)
		return false;
	return true;
}
double Coordonnees::operator-(const Coordonnees& other) const
{
	//return double(12742*(asin(sin**2( (m_latitude - other.getLatitude())/2 ) + cos(other.getLatitude()) * cos(m_latitude) *sin**2( (m_longitude - other.getLongitude())/2 )));
}
