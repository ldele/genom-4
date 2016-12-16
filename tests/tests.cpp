#include <gtest/gtest.h>

#include <string>
#include <stdexcept>
#include <vector>

//#include "../src/SuperDNAReader.hpp"
#include "../src/Interface.hpp"


/* Somehow all tests get stuck in loops when trying to open a new file using the same instance of SuperDNAReader or PWM! */

/* 
 ========================
 DNA tests
 ========================
 */
/*
TEST(DNAReaderTest, CorrectOutput)
{
    std::string DNASeq("TCCAATCCACCCTCTGACTATTCCACATCCCATACCTCCTCCTCATCCCCTTGTCTCCATGAGGATTTCTCCACCCCACCAGCCCCCCACCCAACCAGACCAGTCTACTCCCTGGGGCCTCCAGTCTCTTGAGAGTTAGGTACTTCTTCTCTGATTAAAACAAGACCCAGTGGTCCTCTGCTGTATGTGTGTTGGGGACCTCATATCAGCTGGTGTATGCTGCCTGGCTAGTGGTTCAGTGTTTGAGAGATCTCGGGGGTCCAGGATAATTGAGAGAGCTGATCCTCTACAGGGTCATCTTCTTCTTCATTTTCTTCCAGCCTTTCTCTAATTTAACCACAGGGATCAGTAGCTTCTGTCCATTGGTTGGGTGCAAATATATTCCTCTGGTTTTATCAGC");
    std::string Header(">chr7|chr7:113842207-113842607");
    
    SuperDNAReader MyReader;
    DNA MyDNA = MyReader.start("dna_01.fasta");
    std::string MySeq = MyDNA.mFwd;
    std::string MyHeader = MyDNA.mHeader;
    
    EXPECT_EQ(MySeq, DNASeq);
    EXPECT_EQ(MyHeader, Header);
}

TEST(DNAReaderTest, IncorrectFile)
{
    std::string filepath1("bad_dna_wrongLetters01.fasta");
    std::string filepath2("bad_dna_wrongLetters02.fasta");
    
    SuperDNAReader MyReader1;
    SuperDNAReader MyReader2;
    
    ASSERT_ANY_THROW(MyReader1.start(filepath1));
    ASSERT_ANY_THROW(MyReader2.start(filepath2));
}
*/
/*
 ========================
 PWM tests
 ========================
 */

// PWM::openFromFile normalizes any strictly positive and negative matrices
TEST(PWMFileTest, permissiveNormalization)
{
    std::string filepath1("../tests/bad_pwm_badNormalization01.mat");
    std::string filepath2("../tests/bad_pwm_badNormalization02.mat");
    std::string filepath3("../tests/bad_pwm_badNormalization03.mat");
    std::string filepath4("../tests/pwm_ppm_permissiveNormalization01.mat");
    std::string filepath5("../tests/pwm_pssm_permissiveNormalization01.mat");
    
    PWM myPWM;
    
    ASSERT_NO_THROW(myPWM.openFromFile(filepath1));
    ASSERT_NO_THROW(myPWM.openFromFile(filepath2));
    ASSERT_NO_THROW(myPWM.openFromFile(filepath3));
    ASSERT_NO_THROW(myPWM.openFromFile(filepath4));
    ASSERT_NO_THROW(myPWM.openFromFile(filepath5));
}

TEST(PWMFileTest, wrongFileFormat)
{
    std::string filepath1("../tests/bad_pwm_zeroSumPWM.mat");
    std::string filepath2("../tests/bad_pwm_nullPWM.mat");
    std::string filepath3("../tests/pwm_ppm_badFileFormat_null_line.mat");

    PWM myPWM;

    ASSERT_ANY_THROW(myPWM.openFromFile(filepath1));
    ASSERT_ANY_THROW(myPWM.openFromFile(filepath2));
    ASSERT_NO_THROW(myPWM.openFromFile(filepath3));
}

TEST(PWMFileTest, containsUnallowedCharacters)
{
    std::string filepath1("../tests/bad_pwm_badValues01.mat");
    std::string filepath2("../tests/bad_pwm_badValues02.mat");
    std::string filepath3("../tests/bad_pwm_badValues03.mat");
    std::string filepath4("../tests/bad_pwm_badFileStructure03.mat");
    
    PWM myPWM;
    
    ASSERT_ANY_THROW(myPWM.openFromFile(filepath1));
    ASSERT_ANY_THROW(myPWM.openFromFile(filepath2));
    ASSERT_ANY_THROW(myPWM.openFromFile(filepath3));
    ASSERT_ANY_THROW(myPWM.openFromFile(filepath4));
}

TEST(PWMFileTest, permissiveFileStructure)
{
    std::string filepath1("../tests/pwm_FileStructure01.mat");
    std::string filepath2("../tests/pwm_FileStructure02.mat");
    
    PWM myPWM;
    
    ASSERT_NO_THROW(myPWM.openFromFile(filepath1));
    ASSERT_NO_THROW(myPWM.openFromFile(filepath2));
}

TEST(PWMConstructorTest, vectorOfDoubles)
{
    std::vector<double> tab1({ 1, 1, 1, 1 });
    std::vector<double> tab2({ 1, 2, 3, 4, 1, 2, 3, 4});
    std::vector<double> tab3;
    std::vector<double> tab4({ 1 });
    std::vector<double> tab5({ -1, 1, 1, 1});
    std::vector<double> tab6({0 ,0 ,0 ,0});
    std::vector<double> tab7({0 , 0, 0, 0, 1, 2, 1, 1});
    std::vector<double> tab8({-1, -1, -1, -1});

    ASSERT_NO_THROW(auto pwm = PWM(tab1));
    ASSERT_NO_THROW(auto pwm = PWM(tab2));
    ASSERT_ANY_THROW(auto pwm = PWM(tab3));
    ASSERT_ANY_THROW(auto pwm = PWM(tab4));
    ASSERT_ANY_THROW(auto pwm = PWM(tab5));
    ASSERT_ANY_THROW(auto pwm = PWM(tab6));
    ASSERT_NO_THROW(auto pwm = PWM(tab7));
    ASSERT_NO_THROW(auto pwm = PWM(tab8));
}

/* 
 ========================
 Interface tests
 ========================
 */

TEST(InterfaceSetFileTest, checkFileFormatPWM)
{
    std::string filepath1("../tests/bad_pwm_badFileFormat01.jpg");
    std::string filepath2("../tests/bad_pwm_badFileFormat02.pdf");
    std::string filepath3("../tests/i_do_not_exist.mat");
    std::string filepath4("../tests/i_do_not_exist.not");
    std::string filepath5("../tests/i_do_exist.mat");
    
    Interface app;
    
    ASSERT_ANY_THROW(app.setPWM(filepath1));
    ASSERT_ANY_THROW(app.setPWM(filepath2));
    ASSERT_ANY_THROW(app.setPWM(filepath3));
    ASSERT_ANY_THROW(app.setPWM(filepath4));
    ASSERT_NO_THROW(app.setPWM(filepath5));
}

TEST(InterfaceSetFileTest, checkFileFormatDNA)
{
    std::string filepath1("../tests/bad_dna_wrongFormat01.jpg");
    std::string filepath2("../tests/bad_dna_wrongFormat02.pdf");
    std::string filepath3("../tests/i_do_not_exist.fasta");
    std::string filepath4("../tests/i_do_not_exist.not");
    std::string filepath5("../tests/dna_01.fasta");
    
    Interface app;
    
    ASSERT_ANY_THROW(app.setDNA(filepath1));
    ASSERT_ANY_THROW(app.setDNA(filepath2));
    ASSERT_ANY_THROW(app.setDNA(filepath3));
    ASSERT_ANY_THROW(app.setDNA(filepath4));
    ASSERT_NO_THROW(app.setDNA(filepath5));
}

TEST(InterfaceSetFileTest, checkFileFormatOut)
{
    //create file if right extension
    std::string filepath1("../tests/i_do_exist_now.fasta");
    std::string filepath2("../tests/i_will_never_exist.not");

    Interface app;

    ASSERT_NO_THROW(app.setOut(filepath1));
    ASSERT_ANY_THROW(app.setOut(filepath2));
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}







