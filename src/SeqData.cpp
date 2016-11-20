#include "SeqData.hpp"

SeqData::SeqData(std::string seq, size_t pos, std::string str, bool fwd, double score)
:mSeq(seq)
,mPos(pos)
,mStrand(str)
,mFwd(fwd)
,mScore(score)
{
}

char SeqData::fwd() const
{
    if (mFwd) return '+';
    else return '-';
}

char SeqData::operator[](const size_t& pos) const
{
    return mSeq[pos];
}

SeqData& SeqData::operator+=(const double& score)
{
	mScore += score;
	return *this;
}

bool SeqData::operator>(const double& score) const
{
	return mScore > score;
}

size_t SeqData::length() const
{
    return mSeq.length();
}

std::ostream& operator<<(std::ostream& out, const SeqData& sd)
{
    out << sd.mStrand << " " << sd.mPos << " " << sd.fwd() << " " << sd.mSeq << " " << sd.mScore << std::endl;
    return out;
}
