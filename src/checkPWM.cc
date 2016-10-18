#include <iostream>
#include <cassert> 
#include <vector>

using namespace std;

//check si les nombres sont bien compris entre 0 et 1 
//va etre appelée dans le constructeur de PWM
void checkPWM1(){
	//vector <double> mPWM (4.0,0.2);
	for (auto prob : mPWM){
		//abort is called
		assert (prob >= 0.0 and prob <= 1.0);
	}
}

bool checkPWM2(){
	//vector <double> mPWM (4.0,0.2);
	
	for (auto prob : mPWM){
		if (prob >= 0.0 and prob <= 1.0){
			return true;
		}
		else{
			return false;
			}
		}
}

int main (){
	
	return 0;
}
