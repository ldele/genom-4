#ifndef PWM_HPP
#define PWM_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <stdexcept>

/*! PWM class */
using namespace std;

class PWM
{
public:
	/*!
	 * default constructor enabled
	 */
	PWM() = default;

	/*!
     * Constructeur
     * param PWM filename
     */
	PWM(const std::string& filename); 
	
	/*!
     * Function 1
     * Ouvre un fichier et le lit
     */
	void openFromFile (const std::string& filename); 

	/*!
	 * Function 2
	 * returns size_t (if PWM is a M(x,4) matrix, returns x)
	 */
	size_t size() const { return mPWM.size(); }

	/*!
	 * Function 3
	 * param size_t (i*4 + column(depends of character; for example A is 0 and G is 2))
	 * returns score
	 */
    double operator[](const size_t&);
	
	/*!
	 * Function 4	
	 * returns mPWM matrix (std::vector<std::vector<double>>)
	 */
	vector<vector<double> > getmPWM () {return mPWM;}

	/*!
	 * Function 5
	 * returns the sequence which has the highest overall score
	 */
	std::string PWMToConsensus (vector<vector<double> >);

private:

	/*!
     * Private function
     * Check si la valeur introduite est une lettre ou un caractère - Vérification de la matrice
     */
	bool checkLetter(const std::string& filename);
	
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
     * Check si la somme des valeurs d'une ligne de PWM est = 1
     */
	void checkLigne(double somme, unsigned int l);
	
	/*!
     * Private function
     * Methode qui transforme la matrice PPM a (PPM / la constante (plus grande valeur de la matrice))
     */
	void transfoPPMC();
	
	/*!
     * Private function
     * Methode qui transforme la matrice PPM a log(PPM)
     */
	void transfoPSSM();
	
	/*!
     * Private function
     * Methode qui transforme la matrice PSSM a exp(PSSM)
     */
	void transfoPPM();
	
	/*!
     * Private function
     * Methode qui transforme la matrice PSSM a (PSSM - la constante (plus grande valeur de la matrice))
     */
	void transfoPSSMC();

	vector<vector<double> > mPWM; /*!< Matrice du score */
	
	vector<vector<double> > mPPMC; /*!< Matrice obtenue en faisant PPM / la constante (plus grande valeur de la matrice) */

	vector<vector<double> > mPSSM; /*!< Matrice obtenue en faisant log(PPM) */
	
	vector<vector<double> > mPSSMC; /*!< Matrice obtenue en faisant PSSM -la constante (plus grande valeur de la matrice) */

	bool mIsPPM; /*!< True if PWM is PPM/PPMC and false if PWM is PSSM/PSSMC */

};

#endif
