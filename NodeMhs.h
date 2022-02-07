#include <iostream>
using namespace std;

class NodeMhs {
	private:
		string Nama;
		int NPM;
	public:
		NodeMhs(long long int npm,string nama){
			Nama=nama;
			NPM=npm;
		}
		int getNPM(){
			return NPM;
		}
		string getNama(){
			return Nama;
		}
		void setNPM(int newNPM){
			NPM=newNPM;
		}
		void setNama(string newNama){
			Nama=newNama;
		}
};
