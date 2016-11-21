#include <iostream>
#include "Interface.hpp"

int main()
{
    Interface App1("../inputFiles/promoters.fasta", "../outputFiles/output.fasta", "../inputFiles/DBP_PPM.mat");
    App1.output();
	return 0;
}
