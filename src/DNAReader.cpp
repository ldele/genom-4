#include "DNAReader.hpp"
#include <regex>

#ifndef _SOURCE_DIRECTORY_
#define _SOURCE_DIRECTORY_ "/Users/FelixF/Education/EPFL/Programmation/genom-4/"
#endif

#ifndef _ASSET_DIRECTORY_
#define _ASSET_DIRECTORY_ "res/"
#endif

void DNA::push_back(std::string base)
{
	mFwd += base;
	if(base == "A") mRv += "T";
	if(base == "T") mRv += "A";
	if(base == "C") mRv += "G";
	if(base == "G") mRv += "C";
}

void DNA::pop_front()
{
	mFwd.erase(0,1);
	mRv.erase(0,1);
}

DNAReader::~DNAReader()
{
	ifstream.close();
}

void DNAReader::checkFile(std::string filename) const 
{
	//First check the name of the file
	regex r_filename("*.fasta"); //we only accept fasta files
	if(!regex_match(filename, r_filename)) throw "\"checkFile\": wrong file format";

	//Check the file structure. We open and consume the whole file to make sure it's ok
	ifstream fileStream(_SOURCE_DIRECTORY_ + _ASSET_DIRECTORY_ + filename);
	if(!(fileStream.is_open() && fileStream.good())) throw "\"checkFile\": file is bad";
	
	//We expect alternating lines of metadata and dna sequences
	regex r_metaData(">chr\d\\|chr\d:\d+-\d+");
	regex r_DNASeq("^[ACTG]+$");
	regex r_DNABase("^[ACTG]$");
	
	while(!fileStream.eof())
	{
		std::string metaData;
		fileStream.getline(metaData);
		try{checkFormat(metaData, r_metaData);}
		catch(std::string e) "\"checkFile()\": " + e;
		
		std::string start("");
		std::string end("");

		std::istringstream ss(metaData);
		ss.ignore(12, ":");
		metaData.get(start, 256, "-");
		int DNAStart = std::stoi(start);

		metaData.ignore(1);
		metaData.get(end, 256, "\n");
		int DNAEnd = std::stoi(end);

		int DNASize = DNAEnd - DNAStart;

		for(int i(0); i < DNASize; ++i)
		{
			std::string s;
			mFileStream.get(s)
			try{checkFormat(s, r_DNABase);}
			catch(std::string e) "\"checkFile()\": " + e;
		}

		//once we've extracted the DNA sequence of the expected length, the next character must either be a new line or the end of the file
		std::string s;
		if(mFileStream.get(s) != "\n" || !mFileStream.eof();) throw "\"checkFile()\": indicated DNA size does not correspond to DNA sequence";
	}

	fileStream.close();

	return true;
}

void DNAReader::getMetaData() const // assumes the stream is good
{
	try{checkFileStream();}
	catch(std::string e) "\"getMetaData()\": " + e;
	
	std::string s("");
	mFileStream.getline(s, '\n');
	// regex r_metaData(">chr\d\\|chr\d:\d+-\d+");
	// try{checkFormat(s, r_metaData);}
	// catch(std::string e) "\"getMetaData()\": " + e;
	std::istringstream metaData(s);
	
	metaData.ignore(4);
	std::string chr("");
	metaData.get(chr,2,"|");
	mCurrentDNAChr = std::stoi(chr);

	metaData.ignore(7,":");
	std::string start("");
	metaData.get(start, 256, "-");
	mCurrentDNAStart = std::stoi(start);

	metaData.ignore(1);
	std::string end("");
	metaData.get(end, 256, "\n");
	mCurrentDNAEnd = std::stoi(end);
}

void DNAReader::getFirstDNASeg() const
{
	try {checkFileStream;}
	catch(std::string e) throw "\"getFirstDNASeg()\": " + e;

	for(int i(0); i < mCurrentDNASize; ++i)
	{
		std::string base;
		mFileStream.get(base);
		mCurrentSegment.push_back(base);
	}
}

void DNAReader::openFile(std::string filename)
{
	try{checkFile(filename);}
	catch(std::string e) throw "\"openFile()\": " + e;

	//open the file, check that it's ok, and get the meta data and sequence for the first segment
	mFileStream.open(_SOURCE_DIRECTORY_ + _ASSET_DIRECTORY_ + filename);
	try{checkFileStream();}
	catch(std::string e) throw "\"openFile()\": " + e;
	try{getMetaData();}
	catch(std::string e) throw "\"openFile()\": " + e;
	try{getFirstDNASeg();}
	catch(std::string e) throw "\"openFile()\": " + e;
}

void DNAReader::next()
{
	try{checkFileStream();}
	catch(std::string e) throw "\"next()\": " + e;

	//get a single character
	std::string s;
	mFileStream.get(s);

	if(mFileStream.eof()) return;
	if(s == "\n"){
		mReadingDNA = false;
		return;
	}

	regex r("^[ACTG]$"); // probably over robust, since we always check files before opening them?
	try{checkFormat(s,r);}
	catch(std::string e) throw "\"next()\": " + e;

	mCurrentSegment.push_back(s);
	mCurrentSegment.pop_front();
	mCurrentBase += 1;
}

void DNAReader::nextDNA()
{
	try{checkFileStream();}
	catch(std::string e) throw "\"nextDNA()\": " + e;

	//if we finished reading the previous segment
	if(!mReadingDNA)
	{
		try{getMetaData();}
		catch(std::string e) throw "\"nextDNA()\": " + e;
		try{getFirstDNASeg();}
		catch(std::string e) throw "\"nextDNA()\": " + e;
	}
	else
	{
	//consume the rest of the line we're reading (presumably DNA)
	std::string s;
	mFileStream.getline(s);
	//check if the stream is still good, and we're not at the end of the file
	try{checkFileStream();}
	catch(std::string e) throw "\"nextDNA()\": " + e;

	try{getMetaData();}
	catch(std::string e) throw "\"nextDNA()\": " + e;
	try{getFirstDNASeg();}
	catch(std::string e) throw "\"nextDNA()\": " + e;
	}		
}

bool DNAReader::endOfFile()
{
	return mFileStream.eof();
}

bool DNAReader::readingDNA()
{
	return mReadingDNA;
}

void DNAReader::checkFormat(std::string s, std::regex r)
{
	if(!regex_match(s,r)) throw "unexpected file formatting or invalid character";
}

void DNAReader::checkFileStream()
{
	if(!(mFileStream.is_open() && mFileStream.good() && !mFileStream.eof())) throw "file stream is bad";
}
