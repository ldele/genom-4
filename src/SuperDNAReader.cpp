#include "SuperDNAReader.hpp"

#include <iostream>

DNA SuperDNAReader::start(std::string filepath)
{
	mFileStream.open(filepath);

    while(!mFileStream.eof())
    {
        std::string header;
        getline(mFileStream, header);
        std::string sequence;
        getline(mFileStream, sequence);
        std::size_t found(sequence.find_first_not_of("ACTGNactgn.-"));
        if(found != std::string::npos)
        {
            std::cerr << "Found invalid character: " << sequence[found] << ", at position: "
            << found;
        }
    }
    mFileStream.close();
    
	mFileStream.open(filepath);
	
	getline(mFileStream, mPrev.mHeader);
	getline(mFileStream, mPrev.mFwd);
	mPrev.mRv = "";

	for(auto& base: mPrev.mFwd)
	{
		if(base == 'A') mPrev.mRv = "T" + mPrev.mRv;
		if(base == 'T') mPrev.mRv = "A" + mPrev.mRv;
		if(base == 'C') mPrev.mRv = "G" + mPrev.mRv;
		if(base == 'G') mPrev.mRv = "C" + mPrev.mRv;
	}

	return mPrev;
}

DNA SuperDNAReader::next()
{
	mPrev.mHeader = "";
	mPrev.mFwd = "";
	mPrev.mRv = "";

	getline(mFileStream, mPrev.mHeader);
	getline(mFileStream, mPrev.mFwd);
	for(auto& base: mPrev.mFwd)
	{
		if(base == 'A') mPrev.mRv = "T" + mPrev.mRv;
		if(base == 'T') mPrev.mRv = "A" + mPrev.mRv;
		if(base == 'C') mPrev.mRv = "G" + mPrev.mRv;
		if(base == 'G') mPrev.mRv = "C" + mPrev.mRv;
	}

	return mPrev;
}

bool SuperDNAReader::eof()
{
	return mFileStream.eof();
}