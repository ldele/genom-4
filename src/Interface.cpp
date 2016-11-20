#include "Interface.hpp"

#include <regex>
#include <map>
#include <iostream>
#include <stdexcept>

Interface::Interface(std::string const& DNAfile, std::string const& Outfile, std::string const& PWMfile)
:mDNAFileN(DNAfile)
,mPWMFileN(PWMfile)
,mOutFileN(Outfile)
{
}

void Interface::output()
{
	try {
	    checkFiles();
	    mPWM.openFromFile(mPWMFileN);
	    FromDNAandPWM();
	    print(std::cout);
	    std::ofstream write(mOutFileN);
	  	print(write);
	    write.close();
	} catch (std::runtime_error error) {
		std::cerr << error.what() << std::endl;
	}
}

std::ostream& Interface::print(std::ostream& p_out) const
{
    for (const auto& seq: mData) {
        p_out << seq;
    }
    return p_out;
}

bool Interface::checkIfFile(std::string const& filename, std::string const& extension)
{
    std::regex r_check(".*\\" + extension);
    if ((!regex_match(filename, r_check) || (filename == extension))) return false;
    std::ifstream file(filename);
    if (file.fail()) return false;
    file.close();
    return true;
}

bool Interface::checkOfFile(std::string const& filename, std::string const& extension)
{
    std::regex r_check(".*\\" + extension);
    if ((!regex_match(filename, r_check) || (filename == extension))) return false;
    std::ofstream file(filename);
    if (file.fail()) return false;
    file.close();
    return true;
}

bool Interface::setDNA(std::string const& filename)
{
    mDNAFileN = filename;
    return checkIfFile(filename, ".fasta");
}

bool Interface::setOut(std::string const& filename)
{
    mOutFileN = filename;
    return checkOfFile(filename, ".fasta");
}

bool Interface::setPWM(std::string const& filename)
{
    mPWMFileN = filename;
    return checkIfFile(filename, ".mat");
}

void Interface::setThreshold(double const& thresh)
{
    mThreshold = double(thresh);
    mSetThresh = true;
}

void Interface::checkFiles() const
{
    if (!(checkIfFile(mDNAFileN) && checkIfFile(mPWMFileN, ".mat") && checkOfFile(mOutFileN))) {
        throw std::runtime_error("Opening of a file failed !");
    }
}

void Interface::FromDNAandPWM()
{
    mData = std::vector<SeqData>();
    if (!mSetThresh) {
		setThreshold(log(0.25)*mPWM.size());
	}
    mDNA.start(mDNAFileN);
    for (size_t i(0); !mDNA.eof(); ++i) {
        if (mDNA.next(mPWM.size())) {
            SeqData sFwd(mDNA.fwd(), i, mDNA.header());
            SeqData sRev(mDNA.rv(), i, mDNA.header(), false);

            calcScore(sFwd);
            calcScore(sRev);
        }
    }
}

void Interface::calcScore(SeqData& sd)
{
    typedef enum {A, C, G, T, N} nuc;
    std::map<char, nuc> char2nuc{{'A',A},{'a',A},
                                 {'C',C},{'c',C},
                                 {'G',G},{'g',G},
                                 {'T',T},{'t',T},
                                 {'N',N},{'n',N},{'-',N},{'.',N}};

    for (size_t j(0); j < mPWM.size(); ++j) {
        if(char2nuc[sd[j]] != 4) {
            if (mPWM[j*4 + char2nuc[sd[j]]] == 0) {
                sd += mThreshold;
                j = mPWM.size();
            } else {
                sd += log(mPWM[j*4 + char2nuc[sd[j]]]);
            }
        }
    }
    if (sd > mThreshold) {
        mData.push_back(sd);
    }
}

std::ostream& operator<<(std::ostream& p_out, Interface const& p_inter)
{
    p_inter.print(p_out);
    return p_out;
}
