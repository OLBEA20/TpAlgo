/*
 * ligne.cpp
 *
 *  Created on: 2016-10-05
 *      Author: etudiant
 */

#include ­"ligne.h"

Ligne::Ligne(const std::vector<std::string>& ligne_gtfs)
{
	m_id = ligne_gtfs[0];
	m_numero = ligne_gtfs[2];
	m_description = ligne_gtfs[4];
	m_categorie = ligne_gtfs[7];
	m_voyages = std::vector<Voyage*>;
}
static CategorieBus Ligne::couleurToCategorie(std::string couleur)
{
	switch(couleur)
	{
	case '97BF0D': return CategorieBus::METRO_BUS;
	case '013888': return CategorieBus::LEBUS;
	case 'E04503': return CategorieBus::EXPRESS;
	case '1A171B': return CategorieBus::COUCHE_TARD;
	default : throw std::logic_error("Error");
	}
}
static std::string Ligne::categorieToString(CategorieBus c)
{
	switch(c)
	{
	case CategorieBus::METRO_BUS: return '97BF0D';
	case CategorieBus::LEBUS: return '013888';
	case CategorieBus::EXPRESS: return 'E04503';
	case CategorieBus::COUCHE_TARD: return '1A171B';
	default: throw std::logic_error("Error");
	}
}
CategorieBus Ligne::getCategorie() const
{
	return m_categorie;
}
void Ligne::setCategorie(CategorieBus categorie)
{
	m_categorie = categorie;
}
std::pair<std::string, std::string> Ligne::getDestinations() const
{
	//vraiment pas claire
}
unsigned int Ligne::getId() const
{
	return m_id;
}
void Ligne::setId(unsigned int id)
{
	m_id = id;
}
const std::string& Ligne::getNumero() const
{
	return m_numero;
}
void Ligne::setNumero(const std::string& numero)
{
	m_numero = numero;
}
const std::vector<Voyage*>& Ligne::getVoyages() const
{
	return m_voyages;
}
void Ligne::setVoyages(const std::vector<Voyage*>& voyages)
{
	m_voyages = voyages;
}
void Ligne::addVoyage(Voyage* ptr_voyage)
{
	m_voyages.push_back(ptr_voyage);
}
const std::string& Ligne::getDescription() const
{
	return m_description;
}
void Ligne::setDescription(const std::string& description)
{
	m_description = description;
}
