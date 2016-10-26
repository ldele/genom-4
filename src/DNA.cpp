#include "DNA.hpp"
#include <string>
#include <fstream>


DNA::DNA (const char*  filename)
{
    openFromFile(filename);
}


void DNA::openFromFile(const char* filename)
{
    /* Méthode à revoir car utilisation de vector de char au lieu de string
     * 
    std::string tmp;  						// variable temporaire
    std::ifstream lecture (filename);
    
    if (lecture.fail()) 
    {
        throw std::string("Error: File cannot be open !");
    }

      do 
    {
       lecture >> tmp;
       infoSeq.push_back(tmp);    	//infoSeq est un vector de string;
       lecture >> std::ws >> tmp;  // DNASeq est un vector de string;
       DNASeq.push_back(tmp);
    } while (!lecture.eof());
   
    lecture.close();
    */
    
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

