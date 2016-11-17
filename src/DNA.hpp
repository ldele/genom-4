#ifndef DNA_HPP
#define DNA_HPP

#include <string>
#include <fstream>

/*! DNA class */
class DNA
{
public:

	/*!
	 * Constructor (default)
	 * no param, everything initialized in void DNA::start(std::string&)
	 */
	DNA() = default;

	/*!
	 * Destructor (default)
	 */
	virtual ~DNA() = default;

	/*! 
	 * Function 1
	 * gets mFwd (forward DNA frag.)
	 */
	std::string fwd() const { return mFwd; }

	/*! 
	 * Function 2
	 * gets mRv (reverse DNA frag.)
	 */
	std::string rv() const { return mRv; }

	/*!
	 * Function 3
	 * gets mHeader (header/DNA strand name)
	 */
	std::string header() const { return mHeader; }

	/*! 
	 * Function 4
	 * param std::string (DNA filename)
	 * called in Interface, opens mFileStream and resets DNA fragments + mHeader
	 */
    void start(const std::string&); 

	/*! 
	 * Function 5
	 * param size_t (size of PWM)
	 * updates mFwd, mRv and mHeader
	 * called in Interface to update DNA (and get next fragments)
	 */
	bool next(const size_t&);
	
	/*! 
	 * Function 6
	 * no param
	 * returns mFileStream.eof()
	 */
	bool eof();

private:
	std::string mHeader; /*!< Header/strand name */
	std::string mFwd; /*!< Forward DNA fragment */
	std::string mRv; /*!< Reverse DNA fragment */
    std::ifstream mFileStream; /*!< DNA file stream */
    unsigned long int mCPos; /*!< Current position in the file */

	/*!
	 * Private function 1
	 * param size_t (size of PWM)
	 * called when we change of DNA strand
	 */
    void nextStrand(const size_t&);

    /*!
     * Private function 2
     * param char (character to be added in the Fwd DNA fragment)
     * is called to slide on DNA (1 char step) -1 ------- +1
     * (updates mFwd when we stay on the same strand)
     */
    void add(const char);

    /*! 
	 * Private function 3
	 * param const size_t& (size of PWM)
	 * resets mFwd and reads a DNA fragment of PWM size in file
     */
    std::istream& getPartOfLine(const size_t&);
};

#endif //DNA_HPP
