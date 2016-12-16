#ifndef DNA_HPP
#define DNA_HPP

#include <string>
#include <fstream>
#include <vector>

/*!
 * @class DNA
 *
 * @brief Read dna file memorizing one dna fragment
 */
class DNA
{
public:

	/*!
	 * @brief Default constructor
	 *
	 * @note you need to call DNA::start() to initialize DNA
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
	bool next(const std::size_t& size);

	/*!
	 * @brief Check if we reached end of dna file
	 * 
	 * @return mFileStream.eof()
	 *
	 * @see Interface::readDNA()
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
     * @brief Read a dna fragment that has pwm column size. (from "" to fragment)
	 *
	 * @param size of pwm column
     */
    std::ifstream& getPartOfLine(const std::size_t& size);

    /*!
     * @brief Check dna fragments and some elements of file format
     *
     * file format : check presence of header and empty lines @n
     * dna fragment : search wrong characters (!= ACGTacgtNn.-)
     */
    void checkSeq();

private:
	std::string mHeader = "";      			///< header/strand name
	std::string mFwd = "";         			///< forward dna fragment
	std::ifstream mFileStream;  			///< dna filestream
};

#endif //DNA_HPP
