#ifdef PWM_HPP
#define PWM_HPP

#include <vector>

/*! PWM class */

class PWM
{
public:

	//constructeur de PWM
	/*!
     * Constructor
     */
	PWM(string filename); 
	
	//fonction qui lit le fichier
	/*!
     * Function 1
     * Param filename 
     */
	void openFromFile (string filename); 
	
	
private:

	//verification de la matrice
	/*!
     * Private function
     * Check PWM file
     */
	bool checkPWM(); 
		
	// matrice de score
	vector<vector<double>> mPWM; /*!< PWM matrix */

};

#endif
