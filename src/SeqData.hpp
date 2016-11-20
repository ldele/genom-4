#ifndef SeqData_hpp
#define SeqData_hpp

#include <fstream>

/*! SeqData class */
class SeqData
{
public:
    /*!
     *  Constructor
     *  param1 std::string (sequence), param2 size_t (number), 
     *  param3 std::string (header), param4 bool (fwd or rev), param5 double (score)
     */
    SeqData(std::string, size_t, std::string, bool = true, double = 0.0);

    /*!
     * Function 1
     * returns '+' if mFwd, '-' if !mFwd
     */
    char fwd() const;

    /*!
     * Function 2
     * param size_t (position in sequence)
     * returns A, C, G, T etc... from seq.
     * overloads '[]'
     */
    char operator[](const size_t&) const;

    /*!
     * Function 3
     * returns DNA seq. length
     */
    size_t length() const;

    /*!
     * Function 4
     * param std::ostream&
     * prints data
     * overloads '<<'
     */
    friend std::ostream& operator<<(std::ostream&, const SeqData&);

private:
    std::string mSeq;  /*!< DNA frag. sequence */
    size_t mPos;  /*!< DNA frag. number */
    std::string mStrand;  /*!< Header/DNA frag. name */
    bool mFwd;  /*!< True for fwd DNA frag., false for reverse */

public:
    double mScore;  /*!< DNA frag. score */
};

#endif // SeqData_hpp
