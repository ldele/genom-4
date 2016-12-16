#ifndef DNA_HPP
#define DNA_HPP

#include <string>
#include <fstream>
#include <vector>

<<<<<<< HEAD
/*!
 * @class DNA
 *
 * @brief Read dna file memorizing one dna fragment
 */
=======
/*! newIfstream class */
class newIfstream
{
	public:
	/*!
	 * Function 1
	 * gets current position in file
	 */
	unsigned long int getCPos() const { return mCPos; }

	/*!
	 * Function 2
	 * param const std::string& (filename)
	 * modified std::ifstream::open
	 */
	void open(const std::string&);

	/*!
	 * Function 3
	 * calls std::ifstream::close()
	 */
	void close() { mFileStream.close(); }
	
	/*!
	 * Function 4
	 * returns std::ifstream::eof()
	 */
	bool eof() { return mFileStream.eof(); }

	/*!
	 * Function 5
	 * returns std::ifstream::peek()
	 */
	char peek() { return mFileStream.peek(); }

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
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
class DNA
{
public:

	/*!
<<<<<<< HEAD
	 * @brief Default constructor
	 *
	 * @note you need to call DNA::start() to initialize DNA
=======
	 * Constructor (default)
	 * no param, everything initialized in void DNA::start(std::string&).
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
	 */
	DNA() = default;

	/*!
	 * @brief Default destructor
	 */
	virtual ~DNA() = default;

	/*!
	 * @brief Get forward dna fragment
	 *
	 * @return forward dna fragment (mFwd) 
	 */
	const std::string& fwd() const noexcept { return mFwd; }

	/*!
	 * @brief Get reverse dna fragment
	 *
	 * @return reverse dna fragment (not memorized)
	 */
	const std::string rv() const noexcept;

	/*!
	 * @brief Get current header
	 *
	 * @return mHeader (the current header of the dna fragment)
	 */
	const std::string& header() const noexcept { return mHeader; }

	/*!
	 * @brief Set or reset DNA ((re)initialize values and stream)
	 *
	 * @param filepath dna filename (/!\ no check)
	 * @return number of character in file
	 *
	 * @see Interface::readDNA()
	 */
    size_t start(const std::string&) noexcept;

	/*!
	 * @brief uUdate mFwd, mRv and mHeader
	 *
	 * @param size of pwm column
	 *
	 * @see Interface::readDNA()
	 */
<<<<<<< HEAD
	bool next(const std::size_t& size);

	/*!
	 * @brief Check if we reached end of dna file
	 * 
	 * @return mFileStream.eof()
	 *
	 * @see Interface::readDNA()
=======
	bool next(const size_t&);
	
	/*! 
	 * Function 6
	 * returns mFileStream.eof()
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
	 */
	bool eof() noexcept { return mFileStream.eof(); }

private:
	/*!
	 * @brief Change strand (We consider fwd and rv to be the same strand)
	 *
	 * @param size of pwm column
	 */
    void nextStrand(const std::size_t& size);

    /*!
<<<<<<< HEAD
     * @brief Read a dna fragment that has pwm column size. (from "" to fragment)
	 *
	 * @param size of pwm column
=======
     * Private function 2
     * param char (character to be added in the Fwd DNA fragment)
     * updates mFwd when we stay on the same strand
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
     */
    std::ifstream& getPartOfLine(const std::size_t& size);

    /*!
     * @brief Check dna fragments and some elements of file format
     *
     * file format : check presence of header and empty lines @n
     * dna fragment : search wrong characters (!= ACGTacgtNn.-)
     */
    void checkSeq();

<<<<<<< HEAD
private:
	std::string mHeader = "";      			///< header/strand name
	std::string mFwd = "";         			///< forward dna fragment
	std::ifstream mFileStream;  			///< dna filestream
=======
    /*!
     * Private function 4
     * checks if the sequence contains wrong characters (!= ACGTacgtNn.-)
     * if the sequence contains wrong characters, throw std::runtime_error and stops program 
     */
    void checkSeq() const;
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
};

#endif //DNA_HPP
