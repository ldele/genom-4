#include "DNA.hpp"

#include <iostream>
#include <stdexcept>

<<<<<<< HEAD
size_t DNA::start(const std::string& filepath) noexcept
=======
/*
 * We need to call the following function each time we initialize a new DNA. (Or if we want to reset one)
 */
void DNA::start(const std::string& filepath)
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
{
    mFileStream.close();
	mFileStream.open(filepath);
    if (mFileStream.fail()) {
        throw std::runtime_error("Could not open DNA file !");
    }
    mFileStream.seekg(0,std::ios_base::end);
    std::ios_base::streampos end_pos = mFileStream.tellg();
    mHeader = "";
    mFwd = "";
    mFileStream.seekg(0);
    return static_cast<size_t>(end_pos);
}

<<<<<<< HEAD
const std::string DNA::rv() const noexcept
{
    std::string Rv("");
=======
/*
 * Core function. The following function changes the DNA fragments. 
 * It is designed to be called in an iterator. 
 */
bool DNA::next(const size_t& size)
{
    char nChar;
    mFileStream >> nChar;
    if (nChar == '>') nextStrand(size); //In this condition we update header.
    else add(nChar); //Otherwise we update mFwd.
    
    checkSeq(); //Checks the characters in mFwd.
    mRv = "";
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
    for(auto& base: mFwd) {
        if(base == 'A') Rv = "T" + Rv;
        if(base == 'T') Rv = "A" + Rv;
        if(base == 'C') Rv = "G" + Rv;
        if(base == 'G') Rv = "C" + Rv;
    }
    return Rv;
}

bool DNA::next(const size_t& size)
{
    if (!mFileStream.is_open()) {
        throw std::runtime_error("DNA file is not open !");
    }
<<<<<<< HEAD
    char rChar;
    mFileStream >> std::ws >> rChar;
    if (rChar == '>' or rChar == '<') {
        nextStrand(size);                               
    } else {
        if (mFwd != "") {
            mFwd.erase(0,1);
        }
        if (rChar != ('\0')) mFwd += rChar;
    }

    checkSeq();
=======
    if (mHeader == "") {
    	throw std::runtime_error("We expected header in DNA file !");
    }
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
    if (mFwd.length() != size) return false;
    return true;
}

void DNA::nextStrand(const size_t& size)
{
<<<<<<< HEAD
    mHeader = "";
    size_t i(0);
    for (char c('\0'); mFileStream.peek() != '\n' and mFileStream.peek() != ' ' and mFileStream.peek() != '\t' and !mFileStream.eof(); ++i) {
        mFileStream >> std::ws >> c;
        if (i < 64) {
            if (c != '\0') mHeader += c;
        }
    }

    if (i > 64) {
        std::cerr << "In DNA; header length > 64 characters." << std::endl;
        std::cerr << "The header was reduced to : " + mHeader << std::endl;
        std::cerr << "Some dna could be part of the header, please check DNA input file." << std::endl;
    }
    if (mFileStream.peek() != '\n' && !mFileStream.eof()) {
        std::cerr << "In DNA; expected \\n after header !" << std::endl;
=======
    mFileStream >> mHeader;
    if (mFileStream.peek() != '\n') {
    	throw std::runtime_error("In DNA; we expected \\n after header ! Wrong file format !");
    }
    mFwd = "";
    getPartOfLine(size);
}

//updates mFwd. -> better performances if we use deques/queues ?
void DNA::add(const char c)
{
    std::string str("");
    str += c;
    for (size_t i(1); i < mFwd.size(); ++i) {
    	mFwd[i-1] = mFwd[i];
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
    }

    getPartOfLine(size);
}

std::ifstream& DNA::getPartOfLine(const size_t& size)
{
<<<<<<< HEAD
	mFwd = "";
    for (char rChar; mFwd.length() != size && !mFileStream.eof();) {
        mFileStream >> std::ws >> rChar;
        mFileStream >> std::ws;
        if (rChar == '<' or rChar == '>') {
            nextStrand(size); //recursion
=======
    for (char nChar('\0'); (mFwd.length() != size) and (!mFileStream.eof());) {
        mFileStream >> nChar;
        if (nChar == '>') {
            nextStrand(size); //recursion.
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
            return mFileStream;
        }
        else if (rChar != '\0') mFwd += rChar;
    }
    return mFileStream;
}

void DNA::checkSeq()
{
	size_t pos = mFwd.find_first_not_of("ACGTacgtNn.-");
    if (pos != std::string::npos) {
    	throw std::runtime_error("In DNA file; found invalid character in : " + mFwd);
    }
    if (mHeader == "") {
        throw std::runtime_error("Header was expected in DNA file !"); // or not?
    }
    if (mFileStream.peek() == '\n') {
        mFileStream.get();
    	if (mFileStream.peek() == '\n') {
            throw std::runtime_error("In DNA file; found empty line !");
    	}
    }
}

<<<<<<< HEAD
=======
void newIfstream::open(const std::string& filename) 
{
    mFileStream.open(filename, std::ios::in);
    mCPos = 0;
}

/*
 * I wanted to use inheritance from ifstream but the following function was never called..
 */
template<typename T>
std::ifstream& operator>>(newIfstream& file, T& sth) 
{
    file.mFileStream >> std::ws >> sth;
    ++file.mCPos;
    return file.mFileStream;
}
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
