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
     * Constructeur par défaut
     */
	PWM(const char* filename); 
	
	/*!
     * Function 1
     * Ouvre un fichier et le lit
     */
	void openFromFile (const char* filename); 
	
	
	vector<vector<double> > getmPWM () {return mPWM;};
	std::string PWMToConsensus (vector<vector<double> > matrice);

private:

	  

	/*!
     * Private function
     * Check si la valeur introduite est une lettre ou un caractère - Vérification de la matrice
     */
	bool checkLetter(const char* filename);
	
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

};

#endif