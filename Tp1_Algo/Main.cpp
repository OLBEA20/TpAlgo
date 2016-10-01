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

int main( int argc, const char* argv[] )
{
	Date date;
	Date date2(2016,9,29);
	Heure heure(24,14,11);
	Heure heure2(25,15,1);

	std::vector<std::vector<std::string>> hope;
	lireFichier("stop_times.txt", hope, ',', true);

	//int deltaTime = time(NULL);

	Arret arret(hope[4]);

	//deltaTime = time(NULL) - deltaTime;
	//std::cout << deltaTime << "(s)" << std::endl;
	std::cout<< arret.getHeureArrivee() << std::endl;

	for( int i = 0; i < 5; ++i){
		for(unsigned int j = 0; j < hope[i].size(); ++j){
			std::cout<< hope[i][j] << " ";
		}
		std::cout<<std::endl;
	}

	if(heure >= heure2){
		std::cout<< "FUCK YEAH!!"<<std::endl;
	}
	else{
		std::cout<< "HELL YEAH!!"<<std::endl;
	}

	std::cout<< date << std::endl;
	std::cout<< heure << std::endl;
	std::cout<< heure2 - heure << std::endl;
}


