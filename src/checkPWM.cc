#include <iostream>
#include <vector>
#include <string>

using namespace std;

//check si les nombres sont bien compris entre 0 et 1 
//va etre appelée dans le constructeur de PWM
//si c'est des valeurs negatives
void checkPWM(){
	
	//vector <vector<double>> mPWM (4, -1.0);
	
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

/*bool checkPWM2(){
	vector <double> mPWM (4.0,0.2);
	
	for (auto prob : mPWM){
		char c;
		try{
			if (prob==c){
				return false;
			}
		}
		catch{
			cout<<"Valeur introduite est une lettre"<<endl;
		}
		
	}
	
	for (auto prob : mPWM){
		try{
			if (prob => 0.0){
				try{
					if (prob <= 1.0){
							return true;
							}	
					else{
						throw string ("valeur introduite supérieure à 1.0");
						return false;
						}
					}
				catch (string const& erreur){
					cerr<< "Erreur :" <<erreur<<endl;
					}
			}
			else{
				throw string ("valeur negative introduite");
				//return false;	
				}
			}	
		catch (string const& erreur){
			cerr<< "Erreur : "<<erreur<<endl;
			}
	}		
}*/

int main (){
		
	checkPWM ();
	
	return 0;
}
