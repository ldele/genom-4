#ifndef interface_H
#define interface_H

#include "DNA.hpp"
#include "PWM.hpp"
#include "SeqData.hpp"

/*!
 * @class Interface 
 */
class Interface
{
public:
    /*!
     * @brief Default constructor
     */
    explicit Interface() = default;

	/*!
	 * @brief Constructor
	 *
	 * @param dnaFilename has to be @em fasta or @em fa
     * @param pwmFilename has to be @em mat
     * @param outputFilename
	 */
	explicit Interface(std::string const&, std::string const&, std::string const&);

    /*!
     * @brief Constructor (with PWM already initialized)
     *
     * @param dnaFilename has to be @em fasta or @em fa
     * @param newPWM has to be in norm
     * @param outputFilename
     */
	explicit Interface(std::string const&, PWM const&, std::string const&);

	/*!
	 *  @brief Copy deleted
	 */
	Interface& operator=(const Interface&) = delete;

    /*!
     * @brief Calculate output from DNA and PWM
     *
     * @return 0 if everything went as expected and 1 if there was an issue.
     *
	 * @note Call output() to run the program
     *
     * The program stops without delivering output if :
     *      @n it cannot open dna or pwm file,        
     *      @n it finds an unallowed character in the pwm or dna file,
     *      @n it finds errors in input format that have impact on output values.
     */
	void output();

    /*!
     * @brief Set new dna input file
     *
     * @param filename dna filename (has to be @em fasta)
     * @return checkFile(filename, ".fasta") return value @see Interface::checkFile()
     */
    bool setDNA(std::string const&);

    /*!
<<<<<<< HEAD
     * @brief Set new output file
     *
     * @param filename output filename (has to be @em fasta)
     * @return checkFile(filename, ".fasta") return value @see Interface::checkFile()
=======
     *  Function 4
     *  param double 
     *  We only accept negative values, everthing above 0 sets (or resets) mSetThresh to false which 
     *	means that we reset mThreshold to default value.)
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
     */
    bool setOut(std::string const&);

	/*!
	 * @brief Set new pwm input file
	 *
	 * @param filename pwm filename (has to be @em mat)
	 * @return checkFile(filename, ".fasta", std::ios::out) return value @see Interface::checkFile()
	 */
    bool setPWM(std::string const&);

    /*!
     * @brief Say we use stored pwm input filename to initialize PWM 
     *
     * @return checkFile(mOutFilename, ".fasta", std::ios::out) return value @see Interface::checkFile() 
     */
    bool setPWM();

<<<<<<< HEAD
    /*!
     * @brief To set if we print output on terminal or not.
     *
     * @param pr true we print ouptut on terminal \n false we don't 
     */
    void setPrintOnTerminal(bool) noexcept;
=======
	/*!
	 *  Function 7
	 *  calculates output from DNA and PWM
	 */
    void output();
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb

    /*!
     * @brief Set new PWM
     *
     * @param newPWM other PWM
     * @return mPWM
     *
     * @see PWM::operator=(PWM const&)
     */
    const PWM& setPWM(const PWM& newPWM);

    /*!
     * @brief Set the score threshold
     *
     * @param threshold new mThreshold
     */
    void setThreshold(double const&) noexcept;

	/*!
	 * @brief Reset threshold to default value
	 *
	 * @note Threshold default value is 'PWM column size' * ln(0.25)
	 */
	void setThreshToDefault() noexcept;

	/*!
<<<<<<< HEAD
	 * @brief Check fstream and filename
	 *
	 * @param filename name of a file
	 * @param extension @em fasta, @em mat, etc
	 * @param openMode file openmode (std::ios::in, std::ios::out, ...)
	 * @return false if the program cannot open the file or the file does not possess the specified extension.
	 */
    static bool checkFile(std::string const&, std::string const& = ".fasta", std::ios_base::openmode = std::ios::in) noexcept;

private:
	/*!
	 * @brief Check all files & streams
=======
	 * private function 1
	 * Checks the streams of DNA, PWM and Output files
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
	 */
    void checkFiles() const;

    /*!
<<<<<<< HEAD
     * @brief Iterate on DNA (reads dnafile and updates fragments)
     *
     * Function called in Interface::output()
=======
     * private function 2
     * Reads DNA and sets the score calculation
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
     */
	void readDNA();

    /*!
<<<<<<< HEAD
     * @brief Calculate dna fragment scores using PWM
     *
     * @param sd dna fragment and all data @see SeqData
	 * @return true if SeqData's score > threshold
     *
     * function called in Interface::readDNA()
=======
     * private function 3
     * calculates the scores and stores output data
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
     */
	bool readPWM(SeqData&);

private:
    DNA mDNA;                       ///< dna fragments
    PWM mPWM;                       ///< pwm Matrix
    std::string mDNAFilename;       ///< dna input filename
    std::string mPWMFilename;       ///< pwm input filename
	std::string mOutFilename;		///< output filename
    double mThreshold;              ///< score threshold
    bool mSetThresh = false;        ///< true, the program uses an user threshold value, @n false the default value
    bool mSetPWM = false;           ///< true, the program doesn't need to initialize PWM from a file
    bool mPinTerm = false;          ///< true, print output in terminal
};

#endif

