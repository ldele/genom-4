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

char SeqData::operator[](const size_t& p_b) const
{
    return mSeq[p_b];
}

size_t SeqData::length() const
{
    return mSeq.length();
}

std::ostream& SeqData::print(std::ostream& p_out) const
{
    p_out << mStrand << " " << mPos << " " << fwd() << " " << mSeq << " " << mScore << std::endl;
    return p_out;
}

std::ostream& operator<<(std::ostream& p_out, const SeqData& p_sd)
{
    p_sd.print(p_out);
    return p_out;
}
