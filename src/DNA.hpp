#ifndef DNA_HPP
#define DNA_HPP

#include <string>
#include <fstream>

/*! newIfstream class */
class newIfstream
{
	public:
	/*!
	 * Function1 
	 * no param
	 * gets current position in file
	 */
	unsigned long int getCPos() const { return mCPos; }

	/*!
	 * Function2
	 * param const std::string& (filename)
	 * modified std::ifstream::open
	 */
	void open(const std::string&);

	/*!
	 * Function3
	 * calls std::ifstream::close()
	 */
	void close() { mFileStream.close(); }
	
	/*!
	 * Function3
	 * returns std::ifstream::eof()
	 */
	bool eof() { return mFileStream.eof(); }

	/*!
	 * Friend Function
	 * param1 newIfstream&, param2 template
	 * overloads '>>'
	 * ++mCPos for each element read in file.
	 */
	template<typename T>
	friend std::ifstream& operator>>(newIfstream&, T&);

	private:
	unsigned long int mCPos; /*!< current position in file */
	std::ifstream mFileStream; /*!< DNA filestream */
};

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
	newIfstream mFileStream; /*!< modified std::ifstream */

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
    newIfstream& getPartOfLine(const size_t&);

    void checkSeq() const;
};

#endif //DNA_HPP
