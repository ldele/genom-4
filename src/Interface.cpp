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

<<<<<<< HEAD
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
=======
/* 
 * The program is centralized in the following function.
 * The function stops without delivering output if:
 *	we cannot open a file,
 *	we find an unallowed character in the PWM or DNA file. 
 */
void Interface::output()
{
	try {
	    checkFiles();
	    mPWM.openFromFile(mPWMFileN); //initializes PWM
	    FromDNAandPWM(); //calculates scores and sets output
	    print(std::cout); //prints output on terminal
	    std::ofstream write(mOutFileN);
	  	print(write); //writes output in the specified output file
	    write.close();
	} catch (std::runtime_error error) {
		std::cerr << error.what() << std::endl;
	}
}

/*
 * Interface::print is used to write the output data in a file or to 
 * print it on a terminal.
 */
std::ostream& Interface::print(std::ostream& out) const
{
    for (const auto& seq: mData) {
        out << seq;
    }
    return out;
}

/*
 * Generalized ifstream control function. Controls if the filename is correct (extension) 
 * and if we can open/find the file. 
 */
bool Interface::checkIfFile(std::string const& filename, std::string const& extension)
{
    std::regex r_check(".*\\" + extension);
    if ((!regex_match(filename, r_check) || (filename == extension))) return false;
    std::ifstream file(filename);
    if (file.fail()) return false;
    file.close();
    return true;
}

/*
 * Generalized ofstream control function. Controls if the filename is correct (extension) 
 * and if we can open/find the file. 
 */
bool Interface::checkOfFile(std::string const& filename, std::string const& extension)
{
    std::regex r_check(".*\\" + extension);
    if ((!regex_match(filename, r_check) || (filename == extension))) return false;
    std::ofstream file(filename);
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
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
<<<<<<< HEAD
	mSetThresh = false;
}

void Interface::setPrintOnTerminal(bool pr) noexcept 
{
    mPinTerm = pr;
=======
	if (thresh > 0) mSetThresh = false;
	else {
	    mThreshold = double(thresh);
	    mSetThresh = true; //if false we use ln(0.25)*PWM size
	}
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
}

//All files need to be ok, to run the program.
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
<<<<<<< HEAD
		setThreshold(log(0.25)*mPWM.size());                   //sets default threshold value
	}
	std::ofstream out(mOutFilename);
    size_t size = mDNA.start(mDNAFilename);                    //DNA initialization
    for (size_t i(0); !mDNA.eof(); ++i) {
        if (mDNA.next(mPWM.size())) {                          
=======
		setThreshold(log(0.25)*mPWM.size()); //default threshold value
	}
    mDNA.start(mDNAFileN); //initialize DNA
    for (size_t i(0); !mDNA.eof(); ++i) {
        if (mDNA.next(mPWM.size())) { //updates header, forward DNA seq. and reverse DNA seq.
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
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
<<<<<<< HEAD
    if (sd > mThreshold) {
		return true;
    }
	return false;
=======
    if (sd > mThreshold) { // Compares the threshold with the score stored in the SeqData
        mData.push_back(sd); 
    }
}

std::ostream& operator<<(std::ostream& out, Interface const& inter)
{
    inter.print(out);
    return out;
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
}
