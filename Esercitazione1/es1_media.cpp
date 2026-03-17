#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char* argv[]) { // argc e argv permettono di passare parametri dal terminale al main
	if (argc < 2) {
		cerr << "Errore: specificare il parametro\n";
		return 1;
	}
	
	string filename = argv[1];
	ifstream ifs(filename); // apre il file passato come primo argomento
	
	if (!ifs.is_open() ) {
		cerr << "Errore: impossibile aprire il file\n";
		return 1;
	}
	string citta;
	double temp1, temp2, temp3, temp4;
	while (ifs >> citta >> temp1 >> temp2 >> temp3 >> temp4) {
		double media = (temp1 + temp2 + temp3 + temp4)/4;
		cout << citta << " " << media << "\n";
	}
	
	return 0;
}
			
	