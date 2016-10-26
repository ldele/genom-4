#include "DNA.hpp"
#include <string>


DNA::DNA (std::string filename)
{
    openFromFile(filename);
}


void DNA::openFromFile (std::string filename){
	
}
   

std::string DNA::returnSeg (unsigned int startpos, unsigned int lenght ){

	return mDNAseq.substr(startpos, lenght);

} 


bool DNA::checkDNAString(std::string mDNAseq1){  		//methode permettant de lire la sequence et de controler 
														//si cette dernière ne contient pas d'erreur
	size_t found = mDNAseq1.find_first_not_of("ATGC");  //fonction qui retourne la position de la première lettre qui n'est pas un ATGC
														//retourne string::npos si toutes les lettres sont ATGC
	if (found!=std::string::npos) {
		return false;
		} else {
			return true;
		}
}

