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

int main( int argc, const char* argv[] )
{
	Date date;
	Date date2(2016,9,29);
	Heure heure(24,14,11);
	Heure heure2(24,14,11);
	Heure heure3(24,15,41);


	std::vector<std::vector<std::string>> hope;
	std::vector<std::vector<std::string>> hope1;

	lireFichier("stop_times.txt", hope, ',', true);
	lireFichier("trips.txt", hope1, ',', true);

	std::vector<Arret> test;

	Arret arret(hope[0]);
	Arret arret1(hope[1]);
	Arret arret2(hope[2]);
	arret2.setHeureArrivee(Heure(7,1,30));

	test.push_back(arret);
	test.push_back(arret1);
	test.push_back(arret2);

	for(std::vector<Arret>::iterator it = test.begin(); it < test.end(); ++it){
		std::cout << it->getHeureArrivee() << std::endl;
		std::cout << it->getHeureDepart() << std::endl << std::endl;
	}


	for(std::vector<Arret>::iterator it = test.begin(); it < test.end(); ++it){
		if(it->getHeureArrivee() == std::next(it)->getHeureArrivee()){
			std::next(it)->setHeureDepart(std::next(it)->getHeureDepart().add_secondes(30));
			std::next(it)->setHeureArrivee(std::next(it)->getHeureArrivee().add_secondes(30));
		}
	}

	for(std::vector<Arret>::iterator it = test.begin(); it < test.end(); ++it){
		std::cout << it->getHeureArrivee() << std::endl;
		std::cout << it->getHeureDepart() << std::endl << std::endl;
	}

	/*for( int i = 0; i < 5; ++i){
		for(unsigned int j = 0; j < hope[i].size(); ++j){
			std::cout<< hope[i][j] << " ";
		}
		std::cout<<std::endl;
	}*/

}


