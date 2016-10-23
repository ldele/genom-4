#ifdef PWM_HPP
#define PWM_HPP

#include <vector>
#include <string>

class PWM
{
public:

	//constructeur de PWM
	PWM(string filename); 
	
	//fonction qui lit le fichier
	void openFromFile (string filename); 
	
	
private:

	//check si c'est la valeur introduite est une lettre
	void checkLetter (double score);
	
	//check si valeur est comprise entre 0 et 1
	void checkscorePWM(double score);
	
	//checker si le log est compris entre -infini et 0
	void checkscorePSSM(double score);
	
	//check si la somme des valeurs d'une ligne de PWM est = 1
	void checkLigne();
		
	// matrice de score
	vector<vector<double>> mPWM;  

}
