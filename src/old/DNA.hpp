#ifndef DNA_HPP
#define DNA_HPP

#include <string>

/*! DNA class */

class DNA
{

public:
	
    /*!
     * Constructeur par défaut
     */
    DNA (const char* Filename);

     /*!
     * Function 1
     * Ouvre un fichier et le lit
     */
    void openFromFile (const char* filename);
    
     /*!
     * Function 2
     * Param StartPos as first argument
     * Param length of the DNA sequence as second argument
     * Retourne un segement avec une position de départ et une longeur donnée
     */
    std::string returnSeg (unsigned int StartPos, unsigned int length);
    
    
private:

	 /*!
     * Private function
     * Check DNA file - Vérifie s'il n'y a que des bases (ATGC) dans la séquence d'ADN
     */
	bool checkDNAString(std::string);
	
	//Attributs
	int size; /*!< Size of the DNA strand */
	std::string mDNAseq; /*!< Sequence of the DNA */
	
};


#endif
