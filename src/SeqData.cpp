#include "SeqData.hpp"

SeqData::SeqData(std::string const& seq, size_t const& pos, std::string const& head, bool const& fwd)
:mSeq(seq)
,mPos(pos)
,mStrand(head)
{
	if (fwd) mFwd = '+';
	else mFwd = '-';
}

const char& SeqData::operator[](const size_t& pos) const
{
    return mSeq[pos];
}

SeqData& SeqData::operator+=(const double& score) noexcept
{
	mScore += score;
	return *this;
}

bool SeqData::operator>(const double& threshold) const noexcept
{
	return mScore > threshold;
}

bool SeqData::fwd() const noexcept
{
    if (mFwd == '+' ) {
        return true;
    } else {
        return false;
    }
}

std::ostream& operator<<(std::ostream& out, const SeqData& sd) noexcept
{
    out << sd.mStrand << " " << sd.mPos << " " << sd.mFwd << " " << sd.mSeq << " " << sd.mScore << std::endl;
    return out;
}
