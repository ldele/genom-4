#ifndef interface_H
#define interface_H

#include "DNA.hpp"
#include "PWM.hpp"
#include "SeqData.hpp"

/*! Interface class */
class Interface
{
public:
	/*!
	 * Constructor
	 * param1 DNA filename, param2 Output filename, param3 PWM filename
	 */
    Interface(std::string const&, std::string const&, std::string const&);

	/*!
	 * Function 1
	 * param std::string (filename)
	 * sets PWM
	 */
    bool setPWM(std::string const&);

    /*!
	 * Function 2
	 * param std::string (filename)
	 * sets DNA
	 */
    bool setDNA(std::string const&);

    /*!
	 * Function 3
	 * param std::string (filename)
	 * sets outputFile
	 */
    bool setOut(std::string const&);

    /*!
     *  Function 4
     *  param double
     *  sets threshold (if you don't want the default one)
     */
    void setThreshold(double const&);

	/*!
	 *	Function 5
	 *  param 1 std::string (filename), param 2 std::string (extension)
	 *  checks extension and ifstream
	 */
    static bool checkIfFile(std::string const&, std::string const& = ".fasta");

    /*!
	 *	Function 6
	 *  param 1 std::string (filename), param 2 std::string (extension)
	 *  checks extension and ofstream
	 */
    static bool checkOfFile(std::string const&, std::string const& = ".fasta");

	/*!
	 *  Function 7
	 *  no param
	 *  calculates output from DNA and PWM
	 */
    void output();

    /*!
     *  Function 8
     *  param std::ostream&
     *  prints output data (if stored in memory)
     */
    std::ostream& print(std::ostream&) const;

private:
    DNA mDNA; /*!< DNA fragments */
    PWM mPWM; /*!< Matrix containing scores (and controls) */
    std::string mDNAFileN; /*!< DNA filename */
    std::string mPWMFileN; /*!< PWM filename */
    std::string mOutFileN; /*!< Output filename */
    double mThreshold; /*!< Threshold; minimum interesting dna fragment score */
    std::vector<SeqData> mData;  /*!< Stored output data */
    bool mSetThresh = false; /*!< Boolean, is true if we changed the threshold otherwise we use default value */

	/*!
	 * private function 1
	 * no param
	 * Check the streams of DNA, PWM and Output files
	 */
    void checkFiles() const;

    /*!
     * private function 2
     * no param
     * Read DNA and set the score calculation
     */
    void FromDNAandPWM();

    /*!
     * private function 3
     * no param
     * calculate the scores and stores output data
     */
    void calcScore(SeqData&);
};

/*!
 * Bonus function
 * param 1 std::ostream&, param 2 Interface
 * calls void Interface::print(std::ostream&)
 * overloads '<<'
 */
std::ostream& operator<<(std::ostream&, Interface const&);

#endif

