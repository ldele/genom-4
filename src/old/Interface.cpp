#include "Interface.hpp"
#include <regex>

size_t const convert(char const& base)
{
    if (base == 'A') {  return 0; }
    if (base == 'C') {  return 1; }
    if (base == 'G') {  return 2; }
    if (base == 'T') {  return 3; }
    throw std::string("1 base != ACGT");
    return 4; //!Will never return 4... (Definitive control is done in DNA?)
}

Interface::Interface(std::string const& DNAfile, std::string const& Outfile, std::string const& PWMfile)
:mDNA()
,mPWM(PWMfile) //! Je ne veux pas lancer PWM::openFromFile dans le constructeur
,mDNAFileN(DNAfile)
,mPWMFileN(PWMfile)
,mOutFileN(Outfile)
{
    if (!checkFiles()) {
        throw std::runtime_error("Interface badly initialized !");
    }
}

void Interface::output()
{
    try {
        if (!checkFiles()) {
            throw std::string("the opening of files failed !");
        }
        if (!mPWM.openFromFile()) {
            throw std::string("of errors in the PWM input data !");
        }
        if (!FromDNAandPWM()) {
            throw std::string("of errors in the DNA input data !");
        }
    } catch (std::string m_error) {
        std::cerr << "No output because " << m_error << std::endl;
    }
}

bool Interface::checkIfFile(std::string const& filename, std::string const& extension) const
{
    std::regex r_check(".*\\" + extension);
    if ((!regex_match(filename, r_check) || (filename == extension))) {
        return false;
    }
    std::ifstream file(filename);
    if (file.fail()) {
        return false;
    }
    file.close();
    return true;
}

bool Interface::checkOfFile(std::string const& filename, std::string const& extension) const
{
    std::regex r_check(".*\\" + extension);
    if ((!regex_match(filename, r_check) || (filename == extension))) {
        return false;
    }
    std::ofstream file(filename);
    if (file.fail()) {
        return false;
    }
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
    return mPWM.newFile(filename); //! newFile n'existe pas... se serait un setFileName dans PWM -> une autre conception...
}

void Interface::setThreshold(double const& thresh)
{
    threshold = double(thresh);
}

bool Interface::checkFiles() const
{
    return checkIfFile(mDNAFileN) && checkIfFile(mPWMFileN, ".mat") && checkOfFile(mOutFileN);
}

bool Interface::FromDNAandPWM()
{
/*!
 Note: J'ai voulu faire des tests en utilisant un cmake avec des fichiers DNA et PWM non-complets.
       Au lieu d'utiliser un DNAReader(que je ne sais pas encore utiliser), j'ai utilisé un pointeur sur
       un ifstream pour itérer sur DNA depuis l'interface...
*/

    setThreshold(log(0.25)*mPWM.size()); //! Valeur par défaut, ne permet pas l'utilisation de setThreshold en dehors de l'interface.
    std::ifstream DNAFile(mDNAFileN);
    std::ofstream OutFile(mOutFileN);
    for (size_t i(0); !DNAFile.eof(); ++i) {
        mDNA.readDNAFromFile(&DNAFile, mPWM.size()); //! Pour changer de segment/séquence

        OutputSeqData sFwd;
        OutputSeqData sRev;
        sFwd.Number = i;
        sRev.Number = i;
        sRev.Fwd = '-';

        sFwd.Seq = mDNA.currentSeq(); //! Prend le segment fwd dans DNA
        sRev.Seq = mDNA.reverseSeq(); //! Prend le segment rev dans DNA
        calcScore(sFwd, OutFile); //! calcule le score du segment fwd
        calcScore(sRev, OutFile); //! calcule le score du segment rev
    }
    DNAFile.close();
    OutFile.close();
    return true; //! Pour plus tard... En cas de prob. en cours de route dans DNA ?
}

void Interface::calcScore(OutputSeqData& OSD, std::ofstream& file)
{
    if ((OSD.Seq.length() == mPWM.size())) {
        for (size_t j(0); j < mPWM.size(); ++j) {
            if (mPWM.score(j, convert(OSD.Seq[j])) == 0) {
                OSD.Score += threshold;
            } else {
                OSD.Score += log(mPWM.score(j, convert(OSD.Seq[j])));
            }
        }
        if (OSD.Score > threshold) {
            file << OSD.Strand << " " << OSD.Number << " " << OSD.Fwd << " " << OSD.Seq << " " << OSD.Score << std::endl;
            std::cout << OSD.Strand << " " << OSD.Number << " " << OSD.Fwd << " " << OSD.Seq << " " << OSD.Score << std::endl;
        }
        mDNAandPWM.push_back(OSD);
    } //!else : we reached end of file. -> Le dernier segment avait la taille mPWM.size()-1
}
