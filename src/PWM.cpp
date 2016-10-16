#include "PWM.hpp"


void PWM::openFromFile (string filename)
{
	
}

//va etre appelée dans le corps du constructeur de PWM afin de vérifier
//les valeurs placées dans le tableau
void PWM::checkPWM()
{
	for (auto ligne : mPWM){
		for (auto prob : ligne){
				try{
					if (prob >= 0.0){
						try{
							if (prob >= 1.0){
									throw string ("valeur introduite supérieure à 1.0");
									}	
							}
						catch (string const& erreur){
							cerr<< "Erreur : " <<erreur<<endl;
							}
					}
					else{
						throw string ("valeur introduite est negative");	
						}
					}	
				catch (string const& erreur){
					cerr<< "Erreur : "<<erreur<<endl;
					}						
			}
	}		
}
