#include "DNAReader.hpp"


std::string _SOURCE_DIRECTORY_ = "/Users/FelixF/Desktop/DNAReader/";

std::string _ASSET_DIRECTORY_ = "res/";


void DNA::push_back(std::string base)
{
	if(base.length() != 1) throw "\"DNA::push_back\": expected single nucleotide as argument";
	mFwd += base;
	if(base == "A") mRv = "T" + mRv;
	if(base == "T") mRv = "A" + mRv;
	if(base == "C") mRv = "G" + mRv;
	if(base == "G") mRv = "C" + mRv;
}

void DNA::pop_front()
{
	mFwd.erase(0,1);
    mRv.pop_back();
}

void DNA::reset()
{
	mFwd = "";
	mRv = "";
}

DNAReader::~DNAReader()
{
	mFileStream.close();
}

#include <iostream>
void DNAReader::checkFile(std::string filename) const 
{
	//First check the name of the file

	std::regex r_filename(".*\\.fasta"); //we only accept fasta files

	if(!regex_match(filename, r_filename)) {throw "\"checkFile\": wrong file format";}

	//Check the file structure. We open and consume the whole file to make sure it's ok
	std::ifstream fileStream(_SOURCE_DIRECTORY_ + _ASSET_DIRECTORY_ + filename);
	if(!(fileStream.is_open() && fileStream.good())) {throw "\"checkFile\": file is bad";}
	
	//We expect alternating lines of metadata and dna sequences
	std::regex r_metaData("^>chr[[:digit:]]+\\|chr[[:digit:]]+:[[:digit:]]+-[[:digit:]]+$");
	std::regex r_DNABase("^[ACTG]$");
	
	while(!fileStream.eof())
	{
		std::string metaData;
		getline(fileStream, metaData);

		std::cout << metaData << std::endl;
		std::cout << regex_match(metaData, r_metaData) << std::endl;

		try{checkFormat(metaData, r_metaData);}
		catch(std::string e) {throw "\"checkFile()\": " + std::string(e);}
		
		std::string start("");
		std::string end("");

		//read the start base
		std::istringstream ss(metaData);
		ss.ignore(12, ':');
		getline(ss, start, '-');
		int DNAStart = std::stoi(start);
		std::cout << "Start: " << DNAStart << std::endl;
		//read the end base
		getline(ss, end, '\n');
		int DNAEnd = std::stoi(end);
		std::cout << "End: " << DNAEnd << std::endl;
		//compute the length of the DNA sequence
		int DNASize = DNAEnd - DNAStart;

		std::cout << DNASize << std::endl;

		for(int i(0); i < DNASize; ++i)
		{
			char s[2];
			fileStream.get(s,2); //read one base at a time (we don't know how big this file is)
			try{checkFormat(s, r_DNABase);}
			catch(std::string e) {throw "\"checkFile()\": " + std::string(e);}
		}
		//once we've extracted the DNA sequence of the expected length, there must not be any character left to extract before a new line

		// Following code produces odd outputs
		// char s[2];
		// fileStream.get(s,2);
		// if(s[0]!=0) {throw "\"checkFile()\": indicated DNA size does not correspond to DNA sequence";}
		
		std::string bologna;
		getline(fileStream, bologna);
		if(bologna != "") {throw "\"checkFile()\": indicated DNA size does not correspond to DNA sequence";}
	}
	//make sure to close the file
	fileStream.close();
}

void DNAReader::getMetaData() //we assume the the file we're reading is properly formatted since it passed our check
{
	//always check the stream
	try{checkFileStream();}
	catch(std::string e){ "\"getMetaData()\": " + std::string(e);}
	
	std::string s("");
	getline(mFileStream, s);
	//make sure we called the function at an appropriate time, and we're actually reading metadata
	std::regex r_metaData("^>chr[[:digit:]]{1,2}\\|chr[[:digit:]]{1,2}:[[:digit:]]+-[[:digit:]]+$");
	try{checkFormat(s, r_metaData);}
	catch(std::string e) {throw "\"getMetaData()\": " + std::string(e);}
	std::istringstream metaData(s);
	
	metaData.ignore(4);
	std::string chr("");
	getline(metaData,chr,'|');
	mCurrentDNAChr = std::stoi(chr);

	metaData.ignore(7,':');
	std::string start("");
	getline(metaData,start, '-');
	mCurrentDNAStart = std::stoi(start);

	std::string end("");
	getline(metaData, end, '\n');
	mCurrentDNAEnd = std::stoi(end);
}

void DNAReader::getFirstDNASeg()
{
	try {checkFileStream();}
	catch(std::string e) {throw "\"getFirstDNASeg()\": " + std::string(e);}

	mCurrentSegment.reset();

	for(unsigned int i(0); i < mReadFrame; ++i)
	{
		char base[2];
		std::regex r_DNABase("^[ACTG]$");
		mFileStream.get(base,2);
		std::cout << i << ": " << base << std::endl;
		try{checkFormat(base, r_DNABase);}
		catch(std::string e) {throw "\"getFirstDNASeg()\": " + std::string(e);}
		mCurrentSegment.push_back(base);
	}

	mCurrentBase = mCurrentDNAStart;
	mReadingDNA = true;
}

void DNAReader::openFile(std::string filename)
{
	try{checkFile(filename);}
	catch(std::string e) {throw "\"openFile()\": " + std::string(e);}

	//open the file, check that it's ok, and get the meta data and sequence for the first segment
	mFileStream.open(_SOURCE_DIRECTORY_ + _ASSET_DIRECTORY_ + filename);
	try{checkFileStream();}
	catch(std::string e) {throw "\"openFile()\": " + std::string(e);}
	try{getMetaData();}
	catch(std::string e) {throw "\"openFile()\": " + std::string(e);}
	try{getFirstDNASeg();}
	catch(std::string e) {throw "\"openFile()\": " + std::string(e);}

	mEOF = false;
}

void DNAReader::next()
{
	if(mFileStream.eof())
	{
		mEOF = true;
		return;
	}
	try{checkFileStream();}
	catch(std::string e) {throw "\"next()\": " + std::string(e);}

	mCurrentBase += 1;

	//get a single character
	char s[2];
	mFileStream.get(s,2);

	if(!mFileStream.good() && !mFileStream.eof())
	{
		std::string bidon;
		getline(mFileStream, bidon); //get rid of the newline character
		mFileStream.clear(); //get rid of fail bit
		nextDNA();
		return;
	}

	std::regex r("^[ACTG]$"); // probably over robust, since we always check files before opening them?
	try{checkFormat(s,r);}
	catch(std::string e) {throw "\"next()\": " + std::string(e);}

	mCurrentSegment.push_back(s);
	mCurrentSegment.pop_front();

	// if(mFileStream.eof()) return;
}

void DNAReader::nextDNA()
{
	try{checkFileStream();}
	catch(std::string e) {throw "\"nextDNA()\": " + std::string(e);}

	//if we finished reading the previous segment
	if(!mReadingDNA)
	{
		try{getMetaData();}
		catch(std::string e) {throw "\"nextDNA()\": " + std::string(e);}
		try{getFirstDNASeg();}
		catch(std::string e) {throw "\"nextDNA()\": " + std::string(e);}
	}
	else
	{
		//consume the rest of the line we're reading (presumably DNA)
		std::string s;
		getline(mFileStream, s);
		//check if the stream is still good, and we're not at the end of the file
		try{checkFileStream();}
		catch(std::string e) {throw "\"nextDNA()\": " + std::string(e);}

		try{getMetaData();}
		catch(std::string e) {throw "\"nextDNA()\": " + std::string(e);}
		try{getFirstDNASeg();}
		catch(std::string e) {throw "\"nextDNA()\": " + std::string(e);}
	}		
}

bool DNAReader::endOfFile() const
{
	return mEOF;
}

bool DNAReader::readingDNA() const
{
	return mReadingDNA;
}

void DNAReader::checkFormat(std::string s, std::regex r) const
{
	if(!regex_match(s,r)) {throw std::string("unexpected file formatting or invalid character");}
}

void DNAReader::checkFormat(char* s, std::regex r) const
{
	if(!regex_match(s,r)) {throw std::string("unexpected file formatting or invalid character");}
}

void DNAReader::checkFileStream() const
{
	if(!mFileStream.is_open()) {throw std::string("file stream is not open");}
	if(!mFileStream.good()) {throw std::string("file stream not good");}
	if(mFileStream.eof()) {throw std::string("end of file");}
}
