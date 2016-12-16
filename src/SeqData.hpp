#ifndef SeqData_hpp
#define SeqData_hpp

#include <fstream>
#include <vector>

/*! @class SeqData
 */
class SeqData
{
public:
    /*!
     * @brief Constructor
     *
     * @param seq dna fragment sequence (e.g. ACCGAAC)
     * @param pos fragment number (first fragment in file then 0)
     * @param head header
     * @param fwd true if this is a dna forward fragment (false reverse)
     */
    SeqData(std::string const&, size_t const&, std::string const&, bool const& = true);

    /*!
<<<<<<< HEAD
     * @brief Get a dna base from fragment.
     *
     * @param pos position in dna fragment
     * @return A, C, G, T etc... from sequence.
=======
     * Function 1
     * returns '+' if the DNA fragment is on the fwd strand and '-' if it is on the reverse
>>>>>>> 144d52dedad94a311f5f5b9b22a2c3cad37aaadb
     */
    const char& operator[](const size_t&) const;

    /*!
     * @brief Update score
     *
     * @param score single nucleotide score from PWM
     * @return *this
     */
    SeqData& operator+=(const double&) noexcept;

    /*!
     * @brief Compare dna fragment score to threshold
     *
     * @param threshold mThreshold from Interface @see Interface.hpp
     * @return true if score > threshold
     */
    bool operator>(const double&) const noexcept;

    /*!
     * @brief Get dna fragment
     *
     * @return mSeq
     */
    const std::string& getSeq() const noexcept { return mSeq; }

    /*!
     * @brief Get position in DNA strand
     *
     * @return mPos
     */
    const size_t& pos() const noexcept { return mPos; }

    /*!
     * @brief Get Score
     *
     * @return mScore
     */
    const double& score() noexcept { return mScore; }

    /*!
     * @brief To know if the SeqData contains a reverse or forward sequence
     *
     * @return true if the sequence is forward, false ortherwise
     */
    bool fwd() const noexcept;

    /*!
     * @brief Print sequence data
     *
     * @param[out] out std::cout, std::ofstream
     * @param[in] sd SeqData
     */
    friend std::ostream& operator<<(std::ostream&, const SeqData&) noexcept;

private:
    std::string mSeq;       ///< dna fragment sequence
    size_t mPos;            ///< dna fragment number
    std::string mStrand;    ///< header/dna strand name
    char mFwd;              ///< '+' for forward dna fragment, '-' for reverse
    double mScore = 0.0;    ///< dna fragment score
};

#endif // SeqData_hpp
