#ifndef PWM_HPP
#define PWM_HPP

#include <vector>
#include <string>
#include <fstream>

/*!
 * @class PWM
 */
class PWM
{
public:
	/*!
<<<<<<< HEAD
	 * @brief Default Constructor
=======
	 * default constructor enabled
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
	 */
	PWM() = default;

	/*!
	 * @brief Copy Constructor
	 */
	PWM(const PWM&);

	/*!
	 * @brief Constructor std::vector<double>
	 *
	 * @param tab of scores
	 */
	PWM(std::vector<double> const&);

	/*!
	 * @brief rvalue copy
	 *
	 * @param other PWM (rvalue state)
	 * @return *this
	 */
	const PWM& operator=(PWM&&);

	/*!
	 * @brief lvalue copy
	 *
	 * @param other PWM (lvalue state)
	 * @return *this
	 */
	const PWM& operator=(const PWM&);

	/*!
     * @brief lvalue copy from 2D double vector
     *
     * @param 2D vector of doubles
     * @return *this
     */
	const PWM& operator=(const std::vector<std::vector<double>>&);
	
	/*!
     * @brief Initialize, check and normalize PWM
     *
     * @param filename containing pwm input data
     *
     * @note All matrices are converted to PPM format.
     * PPM initialization -> positive values & no null lines (only zeros)
     * PSSM initialization -> negative values & no -inf lines (only -inf)
     */
	void openFromFile (const std::string& filename); 

	/*!
<<<<<<< HEAD
	 * @brief Get column size of PWM.
	 * 
	 * @return pwm column size (if PWM is a M(n,4) matrix, return n)
=======
	 * Function 2
	 * returns size_t (if PWM is a M(x,4) matrix, returns x)
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
	 */
	size_t size() const { return mPWM.size(); }

	/*!
<<<<<<< HEAD
	 * @brief Get score in a specified position of PWM
	 * 
	 * @param pos 1D position in matrix (line 1 line 2 line 3 ...)
	 * @return score of the specified position.
	 */
    double operator[](const size_t&) const;

    /*!
     * @brief Print values of a specified matrix
     *
     * @param[out] out std::cout or filestream
     * @return out (parameter) modified stream
     */
    std::ostream& print(std::ostream& out) const;

    /*!
     * @brief save pwm to file
     *
     * @param filepath of output
     */
    void saveToFile(const std::string& filename);
	
	/*!
	 * @brief Extract consensus from PWM
	 *
	 * @return consensus dna fragment of mPWM
	 */
	std::string PWMToConsensus() const;

private:

	/*!
	 * @brief Check all values of PWM (for post-initialization or copy)
	 *
	 * @note since first initialization of PWM is done from a file 
	 * (using openFromFile). This function should never throw exceptions.
	 * -> other initialization?
	 */
	void checkAll();

=======
	 * Function 3
	 * param size_t (i*4 + column(depends of character; for example A is 0 and G is 2))
	 * returns score
	 */
    double operator[](const size_t&);
	
	/*!
	 * Function 4	
	 * returns mPWM matrix (std::vector<std::vector<double>>)
	 */
	vector<vector<double> > getmPWM () {return mPWM;}

	/*!
	 * Function 5
	 * returns the sequence which has the highest overall score
	 */
	std::string PWMToConsensus (vector<vector<double> >);

private:

>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
	/*!
     * @brief Check if the input values are valid characters (only numbers are allowed)
     *
     * @param filename containing pwm input data
     * @return true if the pwm input file contains only valid characters.
     */
	bool checkLetter(const std::string& filename) const;

	/*!
	 * @brief Check number of elements in file and determines if we use the PSSM or the PPM algorithm.
	 *
	 * @param filename containing pwm input data
	 *
	 * @return true -> PPM algorithm used
	 * false -> PSSM algorithm used
	 *
	 * number of elements in file needs to be a multiple of 4
	 */
	bool checkSize(const std::string& filename) const;

	/*!
	 * @brief Initialize mPWM
	 *
	 * @param filename containing pwm input data
	 * @param function checkscorePPM or checkscorePSSM (program recognizes format)
	 */
	void initPWM(const std::string& filename, void(PWM::*function)(const double&)const);
	
	/*!
     * @brief Check if the parameter is between 0 and 1 (for PPM algorithm)
     *
     * @param score to check and add in mPWM
     */
	void checkscorePPM(const double& score) const;
	 
	/*!
     * @brief Check if the value is negative (for PSSM algorithm)
     *
     * @param score to check and add in mPWM
     */
	void checkscorePSSM(const double& score) const;
	
	/*!
     * @brief Function converting mPWM from PPM to PPMC
     *
     * @note PPMs contain values between 0 and 1. The sum of each line equals 1.
     * @n PPMCs are normalized PPMs obtained by divising each line member by the max value of its line. 
     * @n max value of each line will be 1. (/!\ max values need to be != 0)
     */
	void transfoPPMC();

	/*!
	 * @brief Function converting mPWM from PPMC to PPM
	 *
	 * Divise each element by the sum of its line. /!\ sums need to be != 0 
	 */
	void returnToPPM();
	
	/*!
     * @brief Function converting mPWM from PPM to PSSM
     *
     * @note PSSM are obtained by taking the natural logarithm of each PPM members.
     * @n PSSM = ln(PPM)
     */
	void transfoPSSM();
	
	/*!
     * @brief Function converting mPWM from PSSM to PPM
     */
	void transfoPPM();
	
	/*!
     * @brief Function converting mPWM from PSSM to PSSMC
     *
     * @note PSSMC are noramalized PSSM obtained by substracting the max value of each line from all line members.
     */
	void transfoPSSMC();

private:
	std::vector<std::vector<double>> mPWM; 		///< Matrix containing the scores
};

#endif
