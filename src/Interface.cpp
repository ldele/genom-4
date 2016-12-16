#include "Interface.hpp"

#include <regex>
#include <iostream>
#include <stdexcept>
#include <map>

Interface::Interface(std::string const& dnaFilename, std::string const&  pwmFilename, std::string const& outputFilename)
:mDNAFilename(dnaFilename)
,mPWMFilename(pwmFilename)
,mOutFilename(outputFilename)
{
}

Interface::Interface(std::string const& dnaFilename, PWM const& newPWM, std::string const& outputFilename)
:mPWM(newPWM)
,mDNAFilename(dnaFilename)
,mPWMFilename("")
,mOutFilename(outputFilename)
{
    mSetPWM = true;
}

void Interface::output()
{
    checkFiles();
    if (!mSetPWM) {
        mPWM.openFromFile(mPWMFilename);      //initializes PWM
    }
	readDNA();								 //calculates scores and sets output
}

bool Interface::checkFile(std::string const& filename, std::string const& extension, std::ios_base::openmode openMode) noexcept
{
    std::regex r_check(".*\\" + extension);
    if ((!regex_match(filename, r_check) || (filename == extension))) return false;
    std::fstream file(filename, openMode);
    if (file.fail()) return false;
    file.close();
    return true;
}

bool Interface::setDNA(std::string const& filename)
{
    mDNAFilename = filename;
	if (checkFile(filename, ".fasta") || checkFile(filename, ".fa")) {
        return true;
    } else {
        throw std::runtime_error("Incorrect DNA file !");
    }
    return false;
}

bool Interface::setOut(std::string const& filename)
{
	mOutFilename = filename;
	if (checkFile(filename, ".fasta") || checkFile(filename, ".fa")) {
		return true;
	} else {
		throw std::runtime_error("Incorrect Output file !");
	}
	return false;
}

bool Interface::setPWM(std::string const& filename)
{
    mPWMFilename = filename;
    if (checkFile(filename, ".mat")) {
        mSetPWM = false;
        return true;
    } else {
        throw std::runtime_error("Incorrect PWM file !");
    }
    return false;
}

bool Interface::setPWM()
{
	if (checkFile(mPWMFilename, ".mat")) {
        mSetPWM = false;
        return true;
    } else {
        throw std::runtime_error("Incorrect PWM file !");
    }
    return false;
}

const PWM& Interface::setPWM(const PWM& newPWM)
{
    mSetPWM = true;
    return mPWM = newPWM;
}

void Interface::setThreshold(double const& threshold) noexcept
{
	mThreshold = double(threshold);
	mSetThresh = true;
}

void Interface::setThreshToDefault() noexcept
{
	mSetThresh = false;
}

void Interface::setPrintOnTerminal(bool pr) noexcept 
{
    mPinTerm = pr;
}

void Interface::checkFiles() const
{
	if (!checkFile(mDNAFilename) && !checkFile(mDNAFilename, ".fa")) throw std::runtime_error("Could not open DNA file !");
	if (!checkFile(mOutFilename, ".fasta", std::ios::out) && !checkFile(mOutFilename, ".fa", std::ios::out)) {
			throw std::runtime_error("Could not open Output file !");
	}
    if (!mSetPWM) {
        if (!checkFile(mPWMFilename, ".mat")) throw std::runtime_error("Could not open PWM file !");
    }
}

void Interface::readDNA()
{
    if (!mSetThresh) {
		setThreshold(log(0.25)*mPWM.size());                   //sets default threshold value
	}
	std::ofstream out(mOutFilename);
    size_t size = mDNA.start(mDNAFilename);                    //DNA initialization
    for (size_t i(0); !mDNA.eof(); ++i) {
        if (mDNA.next(mPWM.size())) {                          
            SeqData sFwd(mDNA.fwd(), i, mDNA.header());
            SeqData sRev(mDNA.rv(), i, mDNA.header(), false);
			if (readPWM(sFwd)) {
				out << sFwd;
				if (mPinTerm) std::cout << sFwd;
			}
			if (readPWM(sRev)) {
				out << sRev;
				if (mPinTerm) std::cout << sRev;
			}
        }
    }
	out.close();
}

bool Interface::readPWM(SeqData& sd)
{
    enum nuc {A, C, G, T, N};
    std::map<char, nuc> char2nuc{{'A',A},{'a',A},{'C',C},{'c',C},{'G',G},{'g',G},
                                {'T',T},{'t',T},{'N',N},{'n',N},{'-',N},{'.',N}};

    for (size_t j(0); j < mPWM.size(); ++j) {
        if(char2nuc[sd[j]] != 4) {
            if (mPWM[j*4 + char2nuc[sd[j]]] == 0) {
                sd += mThreshold;
                j = mPWM.size();
            } else {
                sd += log(mPWM[j*4 + char2nuc[sd[j]]]);
            }
        } else {
            sd += log(0.25);
        }
    }
    if (sd > mThreshold) {
		return true;
    }
	return false;
}
