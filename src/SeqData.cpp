#include "SeqData.hpp"

SeqData::SeqData(std::string m_seq, size_t m_pos, std::string m_str, bool m_fwd, double m_score)
:mSeq(m_seq)
,mPos(m_pos)
,mStrand(m_str)
,mFwd(m_fwd)
,mScore(m_score)
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

size_t SeqData::length() const
{
    return mSeq.length();
}

std::ostream& operator<<(std::ostream& out, const SeqData& sd)
{
    out << sd.mStrand << " " << sd.mPos << " " << sd.fwd() << " " << sd.mSeq << " " << sd.mScore << std::endl;
    return out;
}
