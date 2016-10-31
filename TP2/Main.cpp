/*
 * Main.cpp
 *
 *  Created on: 2016-09-28
 *      Author: etudiant
 */

#include <iostream>
#include "auxiliaires.h"
#include <time.h>
#include "arret.h"
#include "voyage.h"
#include "ligne.h"
#include <unordered_map>

using namespace std;

int main( int argc, const char* argv[] )
{
	Date date1;
	Heure heure1;

	unsigned int deltaTime = time(NULL);

	std::vector<std::vector<std::string>> fichierArrets;
	std::vector<std::vector<std::string>> fichierVoyages;
	std::vector<std::vector<std::string>> fichierStation;
	std::vector<std::vector<std::string>> fichierLigne;

	std::vector<Ligne> vLigne;
	std::vector<Station> vStation;
	std::vector<Voyage> vVoyage;
	std::vector<Arret> vArret;

	unordered_map<string,vector<Arret>> mArret;

	lireFichier("stop_times.txt", fichierArrets, ',', true);
	lireFichier("trips.txt", fichierVoyages, ',', true);
	lireFichier("stops.txt", fichierStation, ',', true);
	lireFichier("routes.txt", fichierLigne, ',', true);

	for(unsigned int i = 0; i < fichierLigne.size(); ++i)
	{
		vLigne.push_back(Ligne(fichierLigne[i]));
	}


	for(unsigned int i = 0; i < fichierStation.size(); ++i)
	{
		vStation.push_back(Station(fichierStation[i]));
	}


	for(unsigned int i = 0; i < fichierArrets.size(); ++i)
	{
		if(mArret.count(fichierArrets[i][0]) == 0){
			vector<Arret> vArret2;
			vArret2.push_back(Arret(fichierArrets[i]));
			mArret.insert({fichierArrets[i][0], vArret2});
		}
		else{
			mArret.find(fichierArrets[i][0])->second.push_back(Arret(fichierArrets[i]));
		}
	}
	cout<<time(NULL) - deltaTime<<endl;

	for(unsigned int i = 0; i < fichierVoyages.size(); ++i)
	{
		for(unsigned int j = 0; j < vLigne.size(); ++j)
		{
			if(stoul(fichierVoyages[i][0]) == vLigne[j].getId())
			{
				vVoyage.push_back(Voyage(fichierVoyages[i], &vLigne[j]));
				vVoyage.back().setArrets(mArret.find(vVoyage[vVoyage.size()-1].getId())->second);
			}
		}
	}

	sort(vVoyage.begin(), vVoyage.end());

	deltaTime = time(NULL) - deltaTime;
	cout<<deltaTime;

	ofstream outfile;
	outfile.open("test.txt");
	outfile << "Chargement des donnees terminee en : " << deltaTime << " s" << endl ;
	outfile << "====================== " << endl << "LIGNES DE LA RTC" << endl;
	outfile << "COMPTE = " << vLigne.size() << endl << "======================" << endl;
	for(vector<Ligne>::iterator it = vLigne.begin(); it < vLigne.end(); ++it)\
	{
		outfile << *it;
	}
	outfile << "====================== " << endl << "STATIONS DE LA RTC" << endl;
	outfile << "COMPTE = " << vStation.size() << endl << "======================" << endl;
	for(vector<Station>::iterator it = vStation.begin(); it < vStation.end(); ++it)\
	{
		outfile << *it;
	}

	outfile << "====================== " << endl << "VOYAGES DE LA JOURNEE DU " << date1 << endl << heure1 << "-" << heure1.add_secondes(3600) << endl;
	outfile << "COMPTE = " << vVoyage.size() << endl << "======================" << endl;
	for(vector<Voyage>::iterator it = vVoyage.begin(); it < vVoyage.end(); ++it)\
	{
		if((it->getHeureDepart()- heure1 < 3600) && (it->getHeureDepart() - heure1 > 0)){
			outfile << *it;
		}
	}
}

