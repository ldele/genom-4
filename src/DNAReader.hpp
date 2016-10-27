#ifndef DNA_READER_HPP
#define DNA_READER_HPP

#include <string>
#include <fstream>
#include <regex>

class DNA
{
public:
	DNA() : mFwd(""), mRv("") {}
	virtual ~DNA() = default;

	void push_back(std::string base);
	void pop_front();
    void reset();
    
    std::string forward() const { return mFwd; }
    std::string reverse() const { return mRv; }

private:
	std::string mFwd;
	std::string mRv;
};

class DNAReader
{
public:
	DNAReader(unsigned int readFrame) : mReadFrame(readFrame) {}
	virtual ~DNAReader();

	void openFile(std::string filename);

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
	int currentReadFrame() const { return mReadFrame; }
private:
    bool mEOF;
	unsigned int mReadFrame;

	unsigned int mCurrentDNAChr;
	unsigned int mCurrentDNAStart;
	unsigned int mCurrentDNAEnd;
	unsigned int mCurrentDNASize;
	unsigned int mCurrentBase;

    std::ifstream mFileStream;
	DNA mCurrentSegment;

	bool mReadingDNA;

	void checkFile(std::string filename) const;
	void getMetaData();
	void getFirstDNASeg();

	void checkFormat(std::string s, std::regex r) const;
    void checkFormat(char* s, std::regex r) const;
	void checkFileStream() const;
};

#endif /* DNA_READER_HPP */
