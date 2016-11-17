 #include <iostream>
#include <string>

using namespace std;

string returnSeg(unsigned int, unsigned int);

//main bidon

int main () {
	
	int x;
	int y;
	cout << "A quelle nuclotide aimeriez vous commencer? :" << endl;
	cin >> x;
	cout << " combien de nucleotide " << endl;
	cin >> y;
	cout << "le segment est :" << returnSeg(x, y);
	
	return 0;
}

//fonction qui nous retourne une sous chaine qui commence a starpos et de longueur lenght
//Elle nous retourne un DNA qui est un string

string returnSeg(unsigned int startpos, unsigned int lenght ){

string DNA ("ATCGCGTTAGCTAGTCGAT");
return DNA.substr( startpos, lenght);

} 

