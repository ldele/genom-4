#include "PWM.hpp"


void PWM::openFromFile (string filename)
{
	
}

void PWM::checkLetter (double score){
	
	string sScore = to_string (score);
	size_t found =sScore.find_first_of("abcdefghijklmnopqrstuvwxyz");   //fonction qui retourne la position de la première lettre qui n'est pas un ATGC
            
      try{             
		if (found!=std::string::npos){
				throw string ("valeur introduite est une lettre");
			}
		}
		catch (string const& erreur){
			cerr<< "Erreur : "<<erreur<<endl;
		}	
}

//check si les nombres sont bien compris entre 0 et 1 
//va etre appelée dans la methode openfile
//si c'est des valeurs negatives
//fait appel a checkLetter
void PWM::checkscorePWM(double score){
			
		try{
			if (score >= 0.0){
				try{
					if (score >= 1.0){
							throw string ("probabilité introduite est supérieure à 1.0");
							}	
					}
				catch (string const& erreur){
					cerr<< "Erreur : " <<erreur<<endl;
					}
			}
			else{
				throw string ("probabilité introduite est negative");	
				}
			}	
		catch (string const& erreur){
			cerr<< "Erreur : "<<erreur<<endl;
			}
			
		checkLetter(score);							
}

//checker si le log est compris entre -infini et 0 (car proba sont comprises entre 0 et 1)
void PWM::checkscorePSSM(double score){
	
	try{
		if (score >= 0.0){
				throw string ("valeur logarithmique introduite est supérieure à 0");
			}
		}	
	catch (string const& erreur){
		cerr<< "Erreur : " <<erreur<<endl;
		}
		
	checkLetter(score);	
		
}

//checker si sur la ligne la somme des valeurs vaut 0
void PWM::checkLigne() {
	
	double somme (0.0);

	for (auto ligne : mPWM){
		for (auto prob : ligne){
			somme+=prob;
			}
		try{
			if (somme!=1.0){
					throw string ("somme des probabilites de la ligne n'est pas égale à 1.0");
				}
			}
		catch (string const& erreur){
			cerr<< "Erreur : "<<erreur<<endl;
		}
		
		somme = 0.0;
	}
}
