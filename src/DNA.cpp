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

bool DNA::next(const size_t& p_size)
{
    char nChar;
    mFileStream >> std::ws >> nChar;
    if (nChar != '\0') ++mCPos;
    if (nChar == '>') nextStrand(p_size);
    else add(nChar);
    mRv = "";
    for(auto& base: mFwd) {
        if(base == 'A') mRv = "T" + mRv;
        if(base == 'T') mRv = "A" + mRv;
        if(base == 'C') mRv = "G" + mRv;
        if(base == 'G') mRv = "C" + mRv;
    }
    if (mFwd.length() != p_size) return false;
    return true;
}

void DNA::nextStrand(const size_t& p_size)
{
    mFileStream >> std::ws >> mHeader;
    mCPos += mHeader.length();
    mFwd = "";
    getPartOfLine(p_size);
    mCPos += mFwd.length();
}

void DNA::add(const char c)
{
    std::string str("");
    str += c;
    if (str.find_first_not_of("ACGTacgtNn.-") == std::string::npos) {
        for (size_t i(1); i < mFwd.size(); ++i) {
            mFwd[i-1] = mFwd[i];
        }
        mFwd.pop_back();
        mFwd += str;
    } else {
        if (c != '\0') {
            throw std::runtime_error(" Found invalid character: " + str + ", at position: " + std::to_string(mCPos));
        }
    }
}

bool DNA::eof()
{
	return mFileStream.eof();
}

std::istream& DNA::getPartOfLine(const size_t& p_size)
{
    for (char nChar('\0'); (mFwd.length() != p_size) and (!mFileStream.eof()); mFwd += nChar) {
        mFileStream >> std::ws >> nChar;
        if (nChar == '>') {
            ++mCPos;
            nextStrand(p_size);
            return mFileStream;
        }
    }
    return mFileStream;
}
