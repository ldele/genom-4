#ifndef PWM_HPP
#define PWM_HPP

#include <vector>

/*! PWM class */

class PWM
{
public:
	/*!
     * Constructeur par défaut
     */
	PWM(string filename); 
	
	/*!
     * Function 1
     * Ouvre un fichier et le lit
     */
	void openFromFile (string filename); 
	
	
private:
	/*!
     * Private function
     * Check PWM file - Vérification de la matrice
     */
	void checkPWM();
		
	vector<vector<double>> mPWM; /*!< Matrice du score */

};

#endif
