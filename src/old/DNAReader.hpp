#ifndef DNA_READER_HPP
#define DNA_READER_HPP

#include <string>
#include <fstream>
#include <regex>


class DNA
{
	
public:
	/*!
     * Constructeur par défaut
     */
	DNA() : mFwd(""), mRv("") {}
	
	/*!
     * Destructeur par défaut
     */
	virtual ~DNA() = default;
	
	/*!
     * Function 1
     * Rajoute le prochain nucléotide à la séquence
     */
	void push_back(std::string base);
	
	/*!
     * Function 2
     * Enlève le premier nucléotide de la séquence
     */
	void pop_front();
	
	/*!
     * Function 3
     * Supprime la séquence
     */
    void reset();
    
    /*!
     * Function 4,5
     * Getters des attributs
     */
    std::string forward() const { return mFwd; }
    std::string reverse() const { return mRv; }

private:

	/*!
     * Private function
     * Check DNA file - Vérifie s'il n'y a que des bases (ATGC) dans la séquence d'ADN
     */
	bool checkDNAString (std::string);

	//Attributs
	std::string mFwd;	/*!< Séquence d'ARNm forward  */
	std::string mRv;	/*!< Séquence d'ARNm reverse (=complémentaire)  */
};



class DNAReader
{
	
public:

	/*!
     * Constructeur par défaut
     */
	DNAReader(unsigned int readFrame) : mReadFrame(readFrame) {}
	
	/*!
     * Destructeur par défaut
     */
	virtual ~DNAReader();

	/*!
     * Function  1
     * Ouvre un fichier et le lit
     */
	void openFile(std::string filename);

	/*!
     * Function 2
     * Change de cadre de lecture d'un nucléotide
     * Lance une erreur si pas de base suivante
     */
	void next();
	
	/*!
     * Function 3
     * Passe à la séquence suivante d'ADN
     * Lance une erreur si pas d'ADN suivant
     */
	void nextDNA(); 

	/*!
     * Function 4
     * Test si on est à la fin du fichier
     */
	bool endOfFile() const;
	
	/*!
     * Function 5
     * Permet de savoir si on est en train de lire de l'ADN
     */
	bool readingDNA() const;

	/*!
     * Getters
     */
	DNA getCurrentSegment() const ;
	int currentChromosome() const ;
	int currentStartBase() const ;
	int currentEndBase() const ;
	int currentDNASize() const ;
	int currentBase() const ;
	int currentReadFrame() const ;
	
	
private:

	/*!
     * Booléen permettant d'effectuer des tests
     */
    bool mEOF;
    bool mReadingDNA;
    
    /*!
     * Attributs
     */
	unsigned int mReadFrame;
	unsigned int mCurrentDNAChr;
	unsigned int mCurrentDNAStart;
	unsigned int mCurrentDNAEnd;
	unsigned int mCurrentDNASize;
	unsigned int mCurrentBase;
	
    std::ifstream mFileStream;
	DNA mCurrentSegment;

	/*!
     * Check si c'est les bons formats de fichier,
     * et que le fichier est bien écrit
     */
	void checkFile(std::string filename) const;
	void getMetaData();
	void getFirstDNASeg();
	void checkFormat(std::string s, std::regex r) const;
    void checkFormat(char* s, std::regex r) const;
	void checkFileStream() const;
};

#endif /* DNA_READER_HPP */
