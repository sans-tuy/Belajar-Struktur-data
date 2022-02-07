#include <iostream>
using namespace std;

class Node {
	private:
		string Nama;
		long long int NPM;
		int height;
		Node* left;
		Node* right;
	public:
		Node(long int npm,string nama){
			Nama=nama;
			NPM=npm;
			left=NULL;
			right=NULL;
			height=1;
		}
		Node(){
			Nama="";
			NPM=0;
			left=NULL;
			right=NULL;
			height=1;
		}
		
		int max(int a, int b) {
		  return (a > b) ? a : b;
		}
		long long int getNPM(){
			return NPM;
		}
		string getNama(){
			return Nama;
		}
		int getHeight(){
			return height;
		}
		void setHeight(int tinggi){
			height=tinggi;
		}
		void setNPM(long long int newNPM){
			NPM=newNPM;
		}
		void setNama(string newNama){
			Nama=newNama;
		}
		void setLeft(Node* newLeft){
			left=newLeft;
		}
		Node* getLeft(){
			return left;
		}
		void setRight(Node* newRight){
			right=newRight;
		}
		Node* getRight(){
			return right;
		}
};


