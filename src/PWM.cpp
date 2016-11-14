#include "PWM.hpp"
#include <iostream>
#include <array>

using namespace std;

//constructeur qui fait appel a la methode openfromfile
PWM::PWM(const char* filename)
{	
	this->openFromFile(filename);	
}


//lecture de la matrice, stockage en mémoire et tests
void PWM::openFromFile (const char* filename)
{ 
   if (checkLetter(filename) == false){
	   cout <<"erreur" << endl;
	  }
   else{

		   double score (0.0);  
		   unsigned int ligne(0);
		   ifstream lecture;
		   lecture.open(filename);
			
			//test si le fichier s'ouvre bien
		   try{
			  if (lecture.fail()){
					throw runtime_error("Error: File cannot be open !");
				}
		   }
			catch(std::runtime_error& e){
				cout << e.what() << endl;
		   } 
				
		   //calcule la somme des premiers éléments de la premiere ligne
		   //afin de déterminer s'il s'agit d'une matrice PWM ou PSSM
		   //et ensuite les valeurs sont stockés dans les attributs respectifs de la classe
		   //et la matrice est affichée
		   //si la somme est supérieur a 0, il s'agira d'une PWM car 
		   //une PSSM a des valeurs negatives (a cause du log de proba comprises entre 0 et 1)
		   ifstream read;
		   read.open(filename);
		   double somme (0.0);
		   
		   for (size_t i(0); i<4; ++i){ 
			     
				read >> std::ws;
				read >> score;
				somme+=score;
			}
			
			read.close();
					
		   if(somme >=0.0){
					
				  do{
						double sommeligne (0.0);
						mPWM.push_back(vector<double>());
					  
						for (size_t i(0) ; i<4 ; ++i){ 
								   
							lecture >> std::ws;
							lecture >> score;
							lecture >> std::ws;

							sommeligne+= score;
							checkscorePWM(score);
							mPWM[ligne].push_back(score);
						}
							
						checkLigne(sommeligne, ligne);
						sommeligne=0.0;
							
						++ligne;
						
				  }while (!lecture.eof());

				  lecture.close();

				  cout << " A                 C                 G                 T " << endl;
					
				  for (size_t i(0); i < mPWM.size(); ++i){
						 for (size_t j(0); j < 4; ++j){
							  
							 cout << mPWM[i][j] << "      ";
						 }
						 cout << endl;
					 }
			}
			else{
					 do{
						  mPSSM.push_back(vector<double>());
						  
						  for (size_t i(0); i<4 ; ++i){ 
								
								lecture >> std::ws;
								lecture >> score;
								
								checkscorePSSM(score);
								
								mPSSM[ligne].push_back(score);	
						  }	
						  ++ligne;
						  
					 }while (!lecture.eof());

					 lecture.close();

				     cout << " A                 C                 G                 T " << endl;
				     
					 for (size_t i(0); i < mPSSM.size(); ++i){
						 for (size_t j(0); j < 4; ++j){
							 
							 cout << mPSSM[i][j] << "      ";
						 }
						 cout << endl;
					}
			}
	}
	
}

//search is a test variable to search in file
//in order to search the file filename must be open
bool PWM::checkLetter (const char* filename){
	
	ifstream read;
	string line;
	string search = "abcdefghijklmnopqrstuvwx+""ç%&&/(())===?yz(){}[]"; 

	read.open(filename);
	
		while(!read.eof()){
		   getline(read, line);
		   
		   try{
				if (line.find_first_of(search) != string::npos){
					throw string ("Valeur introduite contient une lettre ou un caractère ");
					}
				}
		  catch(string const& erreur){
				cerr << "Erreur : " << erreur << endl;
				return false;
			}
		}
		
	read.close();
	
	return true;
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
}

//checker si le log est compris entre -infini et 0 (car proba sont comprises entre 0 et 1)
void PWM::checkscorePSSM(double score){
	
	try{
		if (score >= 0.0){
			throw string ("valeur logarithmique introduite est supérieure à 0");
		}
	}	
	catch(string const& erreur){
		cerr<< "Erreur : " <<erreur<<endl;
		}		
}

//checker si sur la ligne la somme des valeurs vaut 0
void PWM::checkLigne(double somme, unsigned int l) {
	
		try{
			if (somme < 0.9 or somme > 1.1){
				throw string ("somme des probabilites de la ligne n'est pas égale à 1.0");
				}
			}
		catch (string const& erreur){
			cerr<< "Erreur : "<<erreur<< " a la ligne " << l <<endl;
		}	
}

//methode qui transforme la matrice PPM a (PPM / la constante (plus grande valeur de la matrice))
void PWM::transfoPPMC() 
{
	double max(0.0);
		
	//recherche du maximum de la matrice PWM et on la stock
	for ( size_t i (0); i <  mPWM.size(); ++i){
		for ( int j (0); j < 4 ; ++j){
			if (max <= mPWM[i][j]){
				max = mPWM[i][j];
			}
		} 	if (max != 0.0){				//check pour ne pas avoir de division par 0.0
			mPPMC[i][0] = mPWM[i][0]/max;
			mPPMC[i][1] = mPWM[i][1]/max;
			mPPMC[i][2] = mPWM[i][2]/max;
			mPPMC[i][3] = mPWM[i][3]/max;
		}
	}
}

//methode qui transforme la matrice PPM a log(PPM)
void PWM::transfoPSSM()
{
	for (size_t i (0); i < mPWM.size() ; ++i){
		for (int j (0); j < 4 ; ++j){
			if(mPWM[i][j] == 0.0){
				mPSSM[i][j] = -99.8;
			}
			else{
				mPSSM[i][j] = log(mPWM[i][j]);
			}
		}
	}
}

//methode qui transforme la matrice PSSM a exp(PSSM)
void PWM::transfoPPM()
{
	//on parcourt la matrice en prenant l'exponentielle
	for (size_t i (0); i < mPWM.size(); ++i){
		for (int j (0); j < 4 ; ++j){
				mPSSM[i][j] = exp(mPWM[i][j]);
				cout << mPSSM[i][j] << "  ";
			}
			cout << endl;
		}
}

//methode qui transforme la matrice PSSM a (PSSM - la constante (plus grande valeur de la matrice))
void PWM::transfoPSSMC()
{
	
	double max(-10);
		
	//recherche du maximum de la matrice PSSM et on la stock
	for ( size_t i (0); i <  mPWM.size(); ++i){
		for ( int j (0) ; j < 4 ; ++j){
				if (max <= mPWM[i][j])
				{
					max = mPWM[i][j];
				}
			} if(max != 0.0){							//check pour ne pas avoir de division par 0.0
				mPSSMC[i][0] = mPWM[i][0]-max;
				mPSSMC[i][1] = mPWM[i][1]-max;
				mPSSMC[i][2] = mPWM[i][2]-max;
				mPSSMC[i][3] = mPWM[i][3]-max;
			}
	} 	
}


// Trouver consensus depuis la matrice
std::string PWM::PWMToConsensus (vector<vector<double> > matrice)
{
	std::string consensus ("");
	double MAX(0.0);
	
	array <std::string, 4> nuc = {"A", "C", "G", "T"}; // Tableau contenant les 4 nucléotides
	int lettre;
	
	//recherche du maximum de la matrice et on stock la lettre correspondante
	//NB: Quelque soit le type de matrice le score le plus élevé correspond toujours à la lettre la plus probable
	for ( size_t i (0); i <  matrice.size(); ++i){
		MAX = 0.0;
		for ( int j (0); j < 4 ; ++j){
			if (MAX <= matrice[i][j]){
				MAX = matrice[i][j];
				lettre = j;
				}
		} 
		consensus += nuc[lettre];
	}
	std::cout << "CONSENSUS:   " << consensus << endl;
	return consensus;
}



