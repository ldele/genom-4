# include <iostream>
# include "header.h"
# include "PWM.hpp"

// ------------- Declarations -------------

// ------------- Main -------------
int main(){
	using namespace std;
	
	PWM pwm("../inputFiles/DBP_PPM.mat");

	pwm.PWMToConsensus(pwm.getmPWM ());

	std::cout << "Hello World" << std::endl;

	return 0;
}

// ------------- Functions -------------
