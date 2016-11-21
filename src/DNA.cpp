#include "DNA.hpp"

#include <iostream>
#include <stdexcept>

/*
 * We need to call the following function each time we initialize a new DNA. (Or if we want to reset one)
 */
void DNA::start(const std::string& filepath)
{
    mFileStream.close();
	mFileStream.open(filepath);
    mHeader = "";
    mFwd = "";
    mRv = "";
}

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
    for(auto& base: mFwd) {
        if(base == 'A') mRv = "T" + mRv;
        if(base == 'T') mRv = "A" + mRv;
        if(base == 'C') mRv = "G" + mRv;
        if(base == 'G') mRv = "C" + mRv;
    }
    if (mHeader == "") {
    	throw std::runtime_error("We expected header in DNA file !");
    }
    if (mFwd.length() != size) return false;
    return true;
}

void DNA::nextStrand(const size_t& size)
{
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
    }
    mFwd.pop_back();
    if (c != ('\0')) mFwd += str;
}

bool DNA::eof()
{
	return mFileStream.eof();
}

newIfstream& DNA::getPartOfLine(const size_t& size)
{
    for (char nChar('\0'); (mFwd.length() != size) and (!mFileStream.eof());) {
        mFileStream >> nChar;
        if (nChar == '>') {
            nextStrand(size); //recursion.
            return mFileStream;
        }
        if (nChar != '\0') mFwd += nChar;
    }
    return mFileStream;
}

void DNA::checkSeq() const 
{
	size_t ePos = mFwd.find_first_not_of("ACGTacgtNn.-");
    if (ePos != std::string::npos) {
    	throw std::runtime_error(" Found invalid character in: " + mFwd + ", at position: " + std::to_string(mFileStream.getCPos()));
    }
}

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