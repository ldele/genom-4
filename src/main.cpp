#include <iostream>
#include "Interface.hpp"

int main()
{
    try {
        Interface App1("../inputFiles/promoters.fasta", "../outputFiles/output.fasta", "../inputFiles/DBP_PPM.mat");
        App1.output();
    } catch (std::runtime_error m_error) {
		std::cerr << m_error.what() << std::endl;
	}
	return 0;
}
