#include <gtest/gtest.h>

//INCLUDE HEADER FILES!

#include <string>

#include "../src/SuperDNAReader.hpp"

TEST(DNAReaderTest, CorrectOutput)
{
    std::string DNASeq("TCCAATCCACCCTCTGACTATTCCACATCCCATACCTCCTCCTCATCCCCTTGTCTCCATGAGGATTTCTCCACCCCACCAGCCCCCCACCCAACCAGACCAGTCTACTCCCTGGGGCCTCCAGTCTCTTGAGAGTTAGGTACTTCTTCTCTGATTAAAACAAGACCCAGTGGTCCTCTGCTGTATGTGTGTTGGGGACCTCATATCAGCTGGTGTATGCTGCCTGGCTAGTGGTTCAGTGTTTGAGAGATCTCGGGGGTCCAGGATAATTGAGAGAGCTGATCCTCTACAGGGTCATCTTCTTCTTCATTTTCTTCCAGCCTTTCTCTAATTTAACCACAGGGATCAGTAGCTTCTGTCCATTGGTTGGGTGCAAATATATTCCTCTGGTTTTATCAGC");
    std::string Header(">chr7|chr7:113842207-113842607");
    
    SuperDNAReader MyReader;
    DNA MyDNA = MyReader.start("/Users/FelixF/Education/EPFL/Programmation/genom-4/tests/dna_01.fasta");
    std::string MySeq = MyDNA.mFwd;
    std::string MyHeader = MyDNA.mHeader;
    
    EXPECT_EQ(MySeq, DNASeq);
    EXPECT_EQ(MyHeader, Header);
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*
//DNA file opening/integrity tests
TEST(DNAFileTest, NumbersInFile)
{
	ASSERT_DEATH(DNA("bad_dna_numbers01.fasta"), "Error: bad characters in file"); //CHANGE ERROR STRING!
	ASSERT_DEATH(DNA("bad_dna_numbers02.fasta"), "Error: bad characters in file");
	ASSERT_DEATH(DNA("bad_dna_numbers03.fasta"), "Error: bad characters in file");
}

TEST(DNAFileTest, WrongLettersInFile)
{
	ASSERT_DEATH(DNA("bad_dna_wrongLetters01.fasta"), "Error: bad characters in file");
	ASSERT_DEATH(DNA("bad_dna_wrongLetters02.fasta"), "Error: bad characters in file");
	ASSERT_DEATH(DNA("bad_dna_wrongLetters03.fasta"), "Error: bad characters in file");
}

TEST(DNAFileTest, WrongFileFormat)
{
	ASSERT_DEATH(DNA("bad_dna_wrongFormat01.jpeg"), "Error: wrong file format");
	ASSERT_DEATH(DNA("bad_dna_wrongFormat02.pdf"), "Error: wrong file format");
}

TEST(DNAFileTest, WrongFileStructure)
{
	ASSERT_DEATH(DNA("bad_dna_wrongStructure01.fasta"), "Error: bad file structure");
	ASSERT_DEATH(DNA("bad_dna_wrongStructure02.fasta"), "Error: bad file structure");
	ASSERT_DEATH(DNA("bad_dna_wrongStructure03.fasta"), "Error: bad file structure");
}

TEST(DNAFileTest, DataMetaDataMismatch)
{
	ASSERT_DEATH(DNA("bad_dna_DMDMismatch01.fasta"), "Error: unexpected number of base pairs");
}

class DNAReloadFromNewFileTest : public ::testing::Test
{
	virtual void SetUp()
	{
		DNA01.openFromFile("dna_02.fasta");
	}

	DNA DNA01("dna_01.fasta");
}

TEST_F (DNAReloadFromNewFileTest, TestOk) //better name?
{
	std::string dna_02_string("TCCAATCCACCCTCTGACTATTCCACATCCCATACCTCCTCCTCATCCCCTTGTCTCCATGAGGAT
	TTCTCCACCCCACCAGCCCCCCACCCAACCAGACCAGTCTACTCCCTGGGGCCTCCAGTCTCTTGAGAGTTAGGTACTTCTTCTCTGATTAAA
	ACAAGACCCAGTGGTCCTCTGCTGTATGTGTGTTGGGGACCTCATATCAGCTGGTGTATGCTGCCTGGCTAGTGGTTCAGTGTTTGAGAGATC
	TCGGGGGTCCAGGATAATTGAGAGAGCTGATCCTCTACAGGGTCATCTTCTTCTTCATTTTCTTCCAGCCTTTCTCTAATTTAACCACAGGGA
	TCAGTAGCTTCTGTCCATTGGTTGGGTGCAAATATATTCCTCTGGTTTTATCAGC");
	ASSERT_EQ(dna_02_string, DNA01.returnString()) // Need a return string func here!
}

//DNA returnSeg() tests
class DNAReturnSegTest : public ::testing::Test 
{
protected:
	virtual void SetUp()
	{
		DNA01.setString("ACTCAGATCGATGTTAGTATGCTGACGTAGTCAGTCTGACGTAGTCATCGATCGTAGCTAGCTAGCTATCGTT");
		DNA02.setString("AATGTCGACTGTGTCGATCGTATCGTATCTGATCAGTCATCGATCAGCTACGATCATCGTC");
		DNA03.setString("ACTGTGTGTTGGTGTTGTGCATCATGCAGTCGTACGTCGTACTGAC");
	}

	DNA DNA01();
	DNA DNA02();
	DNA DNA03();
}

TEST_F(DNAReturnSegTest, ReturnSpecificSegment)
{
	EXPECT_EQ("GATCGATGTT", DNA01.returnSeg(5,10)); //CONFIGURE THIS
	EXPECT_EQ("GACTGTGT", DNA02.returnSeg(7,8));
	EXPECT_EQ("GTGTTGTGCATC", DNA03.returnSeg(12,12));
}

//PWM 
TEST(PWMFileTest, BadlyNormalizedValues)
{
	ASSERT_DEATH(PWM("bad_pwm_badNormalization01.mat"), "Error: bad file");
	ASSERT_DEATH(PWM("bad_pwm_badNormalization02.mat"), "Error: bad file");
	ASSERT_DEATH(PWM("bad_pwm_badNormalization03.mat"), "Error: bad file");
}

TEST(PWMFileTest, badValues)
{
	ASSERT_DEATH(PWM("bad_pwm_badValues01.mat"), "Error: bad file");
	ASSERT_DEATH(PWM("bad_pwm_badValues02.mat"), "Error: bad file");
	ASSERT_DEATH(PWM("bad_pwm_badValues03.mat"), "Error: bad file");
}

TEST(PWMFileTest, badFileFormat)
{
	ASSERT_DEATH(PWM("bad_pwm_badFileFormat01.jpg"), "Error: bad file");
	ASSERT_DEATH(PWM("bad_pwm_badFileFormat02.pdf"), "Error: bad file");
}

TEST(PWMFileTest, badFileStructure)
{
	ASSERT_DEATH(PWM("bad_pwm_badFileStructure01.mat"), "Error: bad file");
	ASSERT_DEATH(PWM("bad_pwm_badFileStructure02.mat"), "Error: bad file");
	ASSERT_DEATH(PWM("bad_pwm_badFileStructure03.mat"), "Error: bad file");
}
 */






