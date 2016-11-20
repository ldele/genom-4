#include "DNA.hpp"

#include <stdexcept>

void DNA::start(const std::string& filepath)
{
    mFileStream.close();
	mFileStream.open(filepath);
	mCPos = 0.0;
    mHeader = "";
    mFwd = "";
    mRv = "";
}

bool DNA::next(const size_t& size)
{
    char nChar;
    mFileStream >> std::ws >> nChar;
    if (nChar == '>') nextStrand(size);
    else add(nChar);
    
    mCPos += mFwd.length();
    checkSeq();
    mRv = "";
    for(auto& base: mFwd) {
        if(base == 'A') mRv = "T" + mRv;
        if(base == 'T') mRv = "A" + mRv;
        if(base == 'C') mRv = "G" + mRv;
        if(base == 'G') mRv = "C" + mRv;
    }
    if (mFwd.length() != size) return false;
    return true;
}

void DNA::nextStrand(const size_t& size)
{
    mFileStream >> std::ws >> mHeader;
    mCPos += mHeader.length() + 1;
    mFwd = "";
    getPartOfLine(size);
}

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

std::istream& DNA::getPartOfLine(const size_t& size)
{
    for (char nChar('\0'); (mFwd.length() != size) and (!mFileStream.eof());) {
        mFileStream >> std::ws >> nChar;
        if (nChar == '>') {
            nextStrand(size);
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
    	throw std::runtime_error(" Found invalid character in: " + mFwd + ", at position: " + std::to_string(ePos + mCPos));
    }
}
