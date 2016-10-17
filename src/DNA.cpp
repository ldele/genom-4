#include "DNA.hpp"
#include <string>



DNA::DNA (string filename)
{
    openFromFile(filename);
}


void DNA::openFromFile (string filename){
	
}
   
    
string DNA::returnSeg (unsigned int StartPos, unsigned int length){
	
}

bool checkDNAstring(std::string mDNAseq1){   //methode permettant de lire la sequence et de controler 
	                                         //si cette dernière ne contient pas d'erreur

size_t found = mDNAseq1.find_first_not_of("ATGC");   //fonction qui retourne la position de la première lettre qui n'est pas un ATGC
                                                     //retourne string::npos si toutes les lettres sont ATGC

if (found!=std::string::npos) {
	return false;
	} else {
		return true;
	}
}
