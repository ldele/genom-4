#ifndef DNA_READER_HPP
#define DNA_READER_HPP

#include <string>
#include <fstream>

class DNA
{
public:
	DNA() = default;
	virtual ~DNA() = default;

	bool isEmpty() { return (mHeader == "") && (mFwd == "") && (mRv == ""); }

	std::string mHeader;
	std::string mFwd;
	std::string mRv;
};

class SuperDNAReader
{
public:
	SuperDNAReader() = default;
	virtual ~SuperDNAReader() = default;

	DNA getPrev() { return mPrev;　}
	
	DNA start(std::string filepath);
	DNA next();
	bool eof();

private:
	DNA mPrev;
	std::ifstream mFileStream;
};

#endif