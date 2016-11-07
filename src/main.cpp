# include <iostream>
# include "header.h"
# include "PWM.hpp"

// ------------- Declarations -------------

// ------------- Main -------------
int main(){
	using namespace std;
	
	PWM pwm("/home/INTRANET/mmach/myfiles/genom-4/inputFiles/DBP_PPM.mat");

	std::cout << "Hello World" << std::endl;

	return 0;
}

// ------------- Functions -------------
