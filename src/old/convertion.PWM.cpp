#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void transfoPPMC() 
{
	//matrice 4 par 4 avec que des 4.2 et un 5.3
	vector<vector<double> > mPWM( 4, vector <double> (4));
	for ( int i (0) ; i < 4 ; ++i){
		for ( int j (0) ; j < 4 ; ++j){
			mPWM[i][j] = 4.2;
		}
	}
	mPWM[2][2] = 5.3;
	
	//matrice 4 par 4 pas initiallisée
	vector<vector<double> > mPPMC ( 4, vector <double> (4));
	
	double max(0.0);
		
	//recherche du maximum de la matrice PWM et on la stock
	for ( size_t i (0) ; i <  mPWM.size(); ++i){
		for ( int j (0) ; j < 4 ; ++j){
				if (max <= mPWM[i][j])
				{
					max = mPWM[i][j];
				}
			}
		}
	
	//affiche la PPM
	for (size_t i(0); i < mPWM.size(); ++i){
		for (int j(0); j < 4; ++j){
			cout << mPWM[i][j] << "  ";
			}
			cout << endl;
		}
		
	cout << endl;
	cout << "Max : " << max;
	
	//check pour ne pas avoir de division par 0.0
	if(max != 0.0){
	
	//on parcourt la matrice en la divisant par max
	for (size_t i(0); i < mPWM.size(); ++i){
		for (int j(0); j < 4 ; ++j){
				mPPMC[i][j] = mPWM[i][j]/max;
			}
		
	}
	
	cout << endl;
	cout << endl;
	cout << "Matrice PPMC : " << endl;
	
	//affiche PPMC
	for (int i(0); i < 4; ++i){
		for (int j(0); j < 4; ++j){
				cout << mPPMC[i][j] << "  ";
			}
			cout << endl;
		}
	}
}

void transfoPSSM ()
{
	
	//matrice 4 par 4 avec que des 0.2 et un 0.5
	vector<vector<double> > mPWM( 4, vector <double> (4));
	for ( int i (0) ; i < 4 ; ++i){
		for ( int j (0) ; j < 4 ; ++j){
			mPWM[i][j] = 0.2;
		}
	}
	mPWM[2][2] = 0.5;
	
	//matrice 4 par 4 pas initiallisée
	vector<vector<double> > mPSSM ( 4, vector <double> (4));
	
	//affiche la PPM
	for (size_t i(0); i < mPWM.size(); ++i){
		for (int j(0); j < 4; ++j){
			cout << mPWM[i][j] << "  ";
			}
			cout << endl;
		}
	cout << endl;
	cout << "Matrice PSSM :" << endl; 
	
	//on parcourt la matrice en prenant le logarithme
	for (size_t i (0); i < mPWM.size() ; ++i){
		for (int j (0); j < 4 ; ++j){
				mPSSM[i][j] = log(mPWM[i][j]);
				cout << mPSSM[i][j] << "  ";
			}
			cout << endl;
		}
	
}

void transfoPPM()
{
	//matrice 4 par 4 avec que des -1.5 et un -0.5
	vector<vector<double> > mPWM( 4, vector <double> (4));
	for ( int i (0) ; i < 4 ; ++i){
		for ( int j (0) ; j < 4 ; ++j){
			mPWM[i][j] = -1.5;
		}
	}
	mPWM[2][2] = -0.5;
	
	//matrice 4 par 4 pas initiallisée
	vector<vector<double> > mPPM ( 4, vector <double> (4));
	
	//affiche la PSSM
	for (size_t i(0); i < mPWM.size(); ++i){
		for (int j(0); j < 4; ++j){
			cout << mPWM[i][j] << "  ";
			}
			cout << endl;
		}
	cout << endl;
	cout << "Matrice PPM :" << endl; 
	
	//on parcourt la matrice en prenant l'exponentielle
	for (size_t i (0); i < mPWM.size() ; ++i){
		for (int j (0); j < 4 ; ++j){
				mPPM[i][j] = exp(mPWM[i][j]);
				cout << mPPM[i][j] << "  ";
			}
			cout << endl;
		}
	
}

void transfoPSSMC()
{
	//matrice 4 par 4 avec que des -1.3 et un -0.8
	vector<vector<double> > mPWM( 4, vector <double> (4));
	for ( int i (0) ; i < 4 ; ++i){
		for ( int j (0) ; j < 4 ; ++j){
			mPWM[i][j] = -1.3;
		}
	}
	mPWM[2][2] = -0.8;
	
	//matrice 4 par 4 pas initiallisée
	vector<vector<double> > mPSSMC ( 4, vector <double> (4));
	
	double max(-10);
		
	//recherche du maximum de la matrice PSSM et on la stock
	for ( size_t i (0) ; i <  mPWM.size(); ++i){
		for ( int j (0) ; j < 4 ; ++j){
				if (max <= mPWM[i][j])
				{
					max = mPWM[i][j];
				}
			}
		}
		
		//affiche la PSSM
	for (size_t i(0); i < mPWM.size(); ++i){
		for (int j(0); j < 4; ++j){
			cout << mPWM[i][j] << "  ";
			}
			cout << endl;
		}
		
	cout << endl;
	cout << "Max : " << max;
	
	//check pour ne pas avoir de division par 0.0
	if(max != 0.0){
	
	//on parcourt la matrice en la divisant par max
	for (size_t i(0); i < mPWM.size(); ++i){
		for (int j(0); j < 4 ; ++j){
				mPSSMC[i][j] = mPWM[i][j]-max;
			}
		}
	cout << endl;
	cout << endl;
	cout << "Matrice PSSMC : " << endl;
	
	//affiche PSSMC
	for (int i(0); i < 4; ++i){
		for (int j(0); j < 4; ++j){
				cout << mPSSMC[i][j] << "  ";
			}
			cout << endl;
		}
	}
}

int main (){
	
	cout << "Matrice PPM :";
	cout << endl;
	transfoPPMC();
	
	cout << endl;
	
	cout << "Matrice PPM :";
	cout << endl;
	transfoPSSM();

	cout << endl;
	
	cout << "Matrice PSSM :";
	cout << endl;
	transfoPPM();
	
	cout << endl;
	
	cout << "Matrice PSSM :";
	cout << endl;
	transfoPSSMC();
	
	
	return 0;
}
