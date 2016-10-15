#ifndef DNA_HPP
#define DNA_HPP

#include <string>

/*! DNA class */

class DNA
{

public:
	
    //Constructeur par défaut
    /*!
     * Constructor
     */
    DNA (string filename);

    //Ouvre un fichier et le lit
     /*!
     * Function 1
     * Param filename 
     */
    void openFromFile (string filename);
    
    //Retourne un segement avec une position de départ et une longeur donnée
     /*!
     * Function 2
     * Param StartPos as first argument
     * Param length of the DNA sequence as second argument
     */
    string returnSeg (unsigned int StartPos, unsigned int length);
    
    
private:

	//Vérifie s'il n'y a que des bases (ATGC) dans la séquence d'ADN
	 /*!
     * Private function
     * Check DNA file
     */
	bool checkDNAString();
	
	//Attributs
	int size; /*!< Size of the DNA strand */
	string mDNAseq; /*!< Sequence of the DNA */
	
};


#endif

