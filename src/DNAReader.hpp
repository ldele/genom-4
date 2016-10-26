#ifndef DNA_READER_HPP
#define DNA_READER_HPP

#include <string>
#include <fstream>
class DNA
{
public:
	DNA() : mFwd(""), mRv("") {}
	virtual ~DNA() = default;

	void push_back(std::string base);
	void pop_front();

private:
	std::string mFwd;
	std::string mRv;
}

class DNAReader
{
public:
	DNAReader(unsigned int readFrame) : mReadFrame(readFrame) {}
	virtual ~DNAReader();

	bool openFile(std::string filename); // returns true if file succesfully opened

	void next(); // throws an error if no next base
	void nextDNA(); // throws an error if no next DNA strand

	bool endOfFile() const;
	bool readingDNA() const;

	DNA getCurrentSegment() const { return mCurrentSegment; }
	int currentChromosome() const { return mCurrentDNAChr; }
	int currentStartBase() const { return mCurrentDNAStart; }
	int currentEndBase() const { return mCurrentDNAEnd; }
	int currentDNASize() const { return mCurrentDNASize; }
	int currentBase() const { 
		if(readingDNA()) return mCurrentBase; 
		else return 0;
	}
private:
	unsigned int mReadFrame;

	unsigned int mCurrentDNAChr;
	unsigned int mCurrentDNAStart;
	unsigned int mCurrentDNAEnd;
	unsigned int mCurrentDNASize;
	unsigned int mCurrentBase;

	ifstream mFileStream;
	DNA mCurrentSegment;

	bool mReadingDNA;

	void checkFile(std::string filename) const;
	bool getMetaData() const;
	bool getFirstDNASeg() const;

	void checkFormat(std::string s, std::regex r);
	void checkFileStream();
}

#endif /* DNA_READER_HPP */