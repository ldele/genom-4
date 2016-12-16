#include "PWM.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

using namespace std;

PWM::PWM(const PWM& other)
:mPWM(other.mPWM)
{
	checkAll();
}

PWM::PWM(std::vector<double> const& tab)
{
	if (tab.size()%4 == 0 && tab.size() != 0) {
		mPWM.resize(tab.size()/4);
		for (size_t i(0); i < tab.size(); ++i) {
			mPWM[i/4].push_back(tab[i]);
		}
		checkAll();
	} else {
		throw std::runtime_error("PWM constructor, vector<double> has a wrong size.");
	}
}

const PWM& PWM::operator=(PWM&& other)
{
	std::swap(mPWM, other.mPWM);
	checkAll();
	return *this;
}

const PWM& PWM::operator=(const PWM& other)
{
	mPWM = other.mPWM;
	checkAll();
	return *this;
}

const PWM& PWM::operator=(const std::vector<std::vector<double>>& other)
{
    mPWM = other;
    checkAll();
    return *this;
}

double PWM::operator[](const size_t& pos) const
{
 	return mPWM[pos/4][pos%4];
}

std::ostream& PWM::print(std::ostream& out) const
{
	std::cout << "A" << setw(15) << "C" << setw(15) << "G" << setw(15) << "T" << std::endl;
	for (const auto& line: mPWM) {
		for (const auto& score: line) {
			out << left << setw(15) << score;
		}
		out << std::endl;
	}
	return out;
}

void PWM::saveToFile(const string& filename)
{
    std::ofstream file_out;
    file_out.open(filename);
    if(file_out.fail()){
        throw std::runtime_error("Unable to save PWM to file: " + filename);
    }
    
    for(size_t i(0); i < mPWM.size(); ++i)
    {
        for(unsigned int j(0); j<4; ++j)
        {
            char c[100];
            std::sprintf(c, "%.2f\t", mPWM[i][j]);
            file_out << c;
        }
        if(i < (mPWM.size()-1)) file_out << "\n";
    }
    file_out.close();
}

bool PWM::checkSize(const string& filename) const
{
	std::ifstream lecture(filename);
	if (lecture.fail()) {
		throw std::runtime_error("Could not open PWM file !");
	}
	std::vector<double> tab;
	double sum(0); 
	do {
		double score(0); 
		lecture >> std::ws >> score;
		lecture >> std::ws;
		tab.push_back(score);
		sum += score;					
	} while (!lecture.eof());
	lecture.close();
	if (tab.size()%4 != 0 and tab.size() != 0) {
		throw std::runtime_error("PWM file contains wrong number of elements : " + std::to_string(tab.size()));
	} else if (tab.size() == 0) {
		throw std::runtime_error("PWM file is empty !");
	}
	if (sum == 0) {
		throw std::runtime_error("In PWM file; total sum equals 0 (null matrix or wrong format) !");
	}
	return (sum > 0);
}

void PWM::initPWM(const string& filename, void(PWM::*function)(const double&)const)
{
	std::ifstream lecture(filename);
	if (lecture.fail()) {
		throw std::runtime_error("Could not open PWM file !");
	}
	mPWM = std::vector<std::vector<double>> ();
	do {
		std::vector<double> tab(4);
		for (size_t i(0) ; i < 4 ; ++i) { 
									   
			lecture >> std::ws >> tab[i];
			lecture >> std::ws;

			(this->*function)(tab[i]);
		}
		mPWM.push_back(tab);							
							
	} while (!lecture.eof());

	lecture.close();
}

//lecture de la matrice, stockage en mémoire et tests
void PWM::openFromFile (const string& filename)
{ 
	if (!checkLetter(filename)) {
	   throw std::runtime_error("In PWM file; found invalid character !");
	} 
					
	if (checkSize(filename)) {
		void(PWM::*function)(const double&)const = &PWM::checkscorePPM;
		initPWM(filename, function);

	} else {
		void(PWM::*function)(const double&)const = &PWM::checkscorePSSM;
		initPWM(filename, function);

		transfoPPM();
	}
	transfoPPMC();
	returnToPPM();
}

//search is a test variable to search in file
//in order to search the file filename must be open
bool PWM::checkLetter (const string& filename) const
{	
	std::ifstream read(filename);
	if (read.fail()) {
		throw std::runtime_error("Could not open PWM file !");
	}
	std::string line("");
	std::string search("ABCDEFGHIJKLMNOPQRSTUVWXZYabcdefghijklmnopqrstuvwx+""\'ç%&&/(())===?yz(){}[]<>\\\"!@"); 
	
	while(getline(read, line)) {
		if (line.find_first_of(search) != string::npos) {
			return false;
		}
	}
	read.close();
	
	return true;
}   

//called in openFromFile
void PWM::checkscorePPM(const double& score) const
{
	if (score < 0.0) {
		throw std::runtime_error("In PWM file; negative value found in detected PPM format !");
	}							
}

void PWM::checkscorePSSM(const double& score) const
{
	if (score > 0.0) {
		throw std::runtime_error("In PWM file; positive value found in detected PSSM format !");
	}	
}

//convert PPM into PPMC
void PWM::transfoPPMC()
{
	for (size_t i(0); i < mPWM.size(); ++i) {

		double max(mPWM[i][0]);
		for (const auto& score: mPWM[i]) {
			if (score > max) max = score;
		}
		if (max == 0.0) {
            //throw std::runtime_error("In PWM file; an only zero line found in PPM format !");
            for (auto& score: mPWM[i]) {
                score = 1;
            }
        } else {
            for (size_t j(0); j < mPWM[i].size(); ++j) {
                mPWM[i][j] = mPWM[i][j]/max;
            }
        }
	}
}

//convert PPMC into PPM 
void PWM::returnToPPM()
{
	for (size_t i(0); i < mPWM.size(); ++i) {
		double sum(0.0);
		for (const auto& score: mPWM[i]) {
			sum += score;
		}
		for (size_t j(0); j < mPWM[i].size(); ++j) {
			mPWM[i][j] = mPWM[i][j]/sum;
		}
	}
}

//convert PPM into PSSM
void PWM::transfoPSSM()
{
	for (size_t i (0); i < mPWM.size() ; ++i) {
		for (int j (0); j < 4 ; ++j) {
			mPWM[i][j] = log(mPWM[i][j]);
		}
	}
}

//convert PSSM into PPM
void PWM::transfoPPM()
{
	//on parcourt la matrice en prenant la puissance e^x 
	for (size_t i (0); i < mPWM.size() ; ++i) {
		double sum(0);
		for (int j (0); j < 4 ; ++j) {
			mPWM[i][j] = exp(mPWM[i][j]);
			sum += mPWM[i][j];
		}
		if (sum == 0) {
            //throw std::runtime_error("In PWM file; an only zero line found in PPM format !");
            for (int j (0); j < 4 ; ++j) {
                mPWM[i][j] = 0.25;
            }
		}
	}
}

//convert PSSM into PSSMC
void PWM::transfoPSSMC()
{
	for (size_t i(0); i < mPWM.size(); ++i) {
		double max(mPWM[i][0]);
		for (const auto& score: mPWM[i]) {
			if (score > max) max = score;
		}
		for (size_t j(0); j < mPWM[i].size(); ++j) {
			mPWM[i][j] = mPWM[i][j] - max;
		}
	}
}

std::string PWM::PWMToConsensus() const 
{
	std::string consensus ("");	
	std::vector<std::string> nuc = {"A", "C", "G", "T"};
	int letter;
	
	//seek max score on each line
	for (const auto& line: mPWM) {
		double max(0.0);
		for (int j(0); j < 4 ; ++j) {
			if (max < line[j]) {
				max = line[j];
				letter = j;
			}
		} 
		consensus += nuc[letter];
	}
	//std::cout << "CONSENSUS:   " << consensus << endl;
	return consensus;
}

void PWM::checkAll()
{
	double sum(0.0);
	size_t size(0.0);
	for (const auto& line: mPWM) {
		for (const auto& score: line) {
			sum += score;
			++size;
		}
	}
	if (size%4 != 0 and size != 0) {
		throw std::runtime_error("PWM contains wrong number of elements : " + std::to_string(size));
	} else if (size == 0) {
		throw std::runtime_error("PWM is empty (null) !");
	}
	if (sum == 0.0) {
		throw std::runtime_error("In PWM file; total sum equals 0 (null matrix or wrong format) !");
	} else if (sum > 0) {
		for (const auto& line: mPWM) {
			for (const auto& score: line) {
				checkscorePPM(score);
			}
		}
	} else {
		for (const auto& line: mPWM) {
			for (const auto& score: line) {
				checkscorePSSM(score);
			}
		}
		transfoPPM();
	}
	transfoPPMC();
	returnToPPM();
}



