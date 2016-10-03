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

	for( int i = 0; i < 5; ++i){
		for(unsigned int j = 0; j < hope[i].size(); ++j){
			std::cout<< hope[i][j] << " ";
		}
		std::cout<<std::endl;
	}

	for( int i = 0; i < 5; ++i){
		for(unsigned int j = 0; j < hope1[i].size(); ++j){
			std::cout<< hope1[i][j] << " ";
		}
		std::cout<<std::endl;
	}

}


