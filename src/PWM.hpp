#ifdef PWM_HPP
#define PWM_HPP

#include <vector>

class PWM
{
public:

	//constructeur de PWM
	PWM(string filename); 
	
	//fonction qui lit le fichier
	void openFromFile (string filename); 
	
	
private:

	//verification de la matrice
	bool checkPWM(); 
		
	// matrice de score
	vector<vector<double>> mPWM;  

}
