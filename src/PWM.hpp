#ifndef PWM_HPP
#define PWM_HPP

#include <vector>
#include <string>

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
<<<<<<< HEAD
	/*!
     * Private function
     * Check PWM file - Vérification de la matrice
     */
	void checkPWM();
=======

	/*!
     * Private function
     * Check si c'est la valeur introduite est une lettre
     */
	void checkLetter (double score);
	
	/*!
     * Private function
     * Check si valeur est comprise entre 0 et 1
     */
	void checkscorePWM(double score);
	
	
	/*!
     * Private function
     * Check si le log est compris entre -infini et 0
     */
	void checkscorePSSM(double score);
	
	/*!
     * Private function
     * check si la somme des valeurs d'une ligne de PWM est = 1
     */
	void checkLigne();
>>>>>>> 547f0b7c1e0a1497f74161b67b117e7ad5593bf1
		
	vector<vector<double>> mPWM; /*!< Matrice du score */

};

#endif
