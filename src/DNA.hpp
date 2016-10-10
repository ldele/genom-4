#ifndef DNA_HPP
#define DNA_HPP

#include <string>


class DNA
{

public:

    //Constructeur par défaut
    DNA (string filename);

    //Ouvre un fichier et le lit
    void openFromFile (string filename);
    
    //Retourne un segement avec une position de départ et une longeur donnée
    string returnSeg (unsigned int StartPos, unsigned int length);
    
    
private:

	//Vérifie s'il n'y a que des bases (ATGC) dans la séquence d'ADN
	bool checkDNAString ();
	
	//Attributs
	int size;
	string mDNAseq;
	
};


#endif

