#include <iostream>
#include <vector>
#include <conio.h>
#include "NodeStatus.h"

using namespace std;

class BinarySearchTree {
	private:
		Node* root;
	public:
		Node* getRoot(){  //getter untuk mengambil root
			return root;
		}
		void setRoot(Node* node){ //setter untuk mensetting root
			root=node;
		}
		BinarySearchTree(){
			root=nullptr;
		}
		int max(int a, int b)
		{
			return (a > b)? a : b;  //mencari nilai max dari kedua nilai
		}
		int height(Node *N) //mengambil height dari sebuah node
		{
			if (N == NULL) 
				return 0;
			return N->getHeight();
		}
		/* Method untuk mencari node parent dari sebuah nilai
		* @param start, mulai dari node start
		* @param value, nilai yang dicari di dalam Binary Search Tree 
		*/
		NodeStatus find(Node* start, long long int npm){
			NodeStatus ns;
			if (start!=nullptr){ //jika node yg dikunjungi tidak null, lanjutkan proses
				//jika npm yg dicari < npm pada node yg dikunjungi
				if (npm < start->getNPM()){ 
					if (start->getLeft()!=nullptr){ //jika anak kiri tidak null, lanjut pencarian ke anak kiri
						return find(start->getLeft(),npm);
					}
					else { 	//pencarian habis, dan nilai yang dicari tidak ada 
						ns.setNodeStatus(start,0);
						return ns;	//kembalikan node parent dari nilai yang dicari dan status=0
					}
				}
				//else jika npm yang dicari = npm pada node yang dikunjungi
				else if (npm == start->getNPM()){
					ns.setNodeStatus(start,1);
					return ns;	//kembalikan node parent dari nilai yang dicari dan status=1
				}
				//else jika npm yang dicari > npm pada node yang dikunjungi
				else if (npm > start->getNPM()){
					//jika anak kanan tidak null, lanjut pencarian ke anak kanan
					if (start->getRight()!=nullptr){
						return find(start->getRight(),npm);
					}
					else { 	//pencarian habis, dan nilai yang dicari tidak ada
						ns.setNodeStatus(start,0);
						return ns;	//kembalikan node parent dari nilai yang dicari dan status=0
					}
				}
			}
			return ns;		
		}
		/**Method untuk memasukkan node baru. 
	 	* @param newvalue, nilai dari node baru yang akan dimasukkan
	 	*/
		void insertNode(long long int npm,string nama){
			Node *newNode=new Node;  //membuat node kosong baru
			newNode->setNama(nama);
			newNode->setNPM(npm);
			newNode->setLeft(nullptr);
			newNode->setRight(nullptr);
			
			if (root==nullptr){ //jika root kosong
				root=newNode;
			}
			else {
				Node* curr;
				curr=root;
				NodeStatus ns=find(curr,newNode->getNPM());
				Node* parNode=ns.getNode();
				int nodeExist=ns.getStatus();  //mencari lokasi parent node
				
				if (parNode!=nullptr && nodeExist==0){
					if (newNode->getNPM() < parNode->getNPM()){ //node lebih kecil dari paernt diletakkan di kiri
						parNode->setLeft(newNode);
						parNode->getLeft()->setHeight(1 + max(height(parNode->getLeft()->getLeft()), //update height node
								height(parNode->getLeft()->getRight())));
					}
					else if (newNode->getNPM() > parNode->getNPM()){ //node lebih kecil dari paernt diletakkan di kanan
						parNode->setRight(newNode);
						parNode->getRight()->setHeight(1 + max(height(parNode->getRight()->getLeft()),  //update height node
								height(parNode->getRight()->getRight())));
					}
				}
				//jika node sudah ada
				else if (parNode!=nullptr && nodeExist==1){
					cout << "Node " << newNode->getNPM() << " exists. Cannot insert another node with the same value" <<"\n";
				}
				//jika node sudah ada khusus node root
				else if (parNode==nullptr && root->getNPM()==newNode->getNPM() && nodeExist==1){
					cout << "Node " << newNode->getNPM() << " exists. Cannot insert another node with the same value"<<"\n";
				}
			}
		}
		/**
 		* Method untuk menelusuri/membaca dan mencetak isi Binary Search Tree 
 		* secara Depth-First dimulai dari node ptr.
 		* Depth-First Traversal yang digunakan adalah Pre-order
 		* @param ptr: node awal penelusuran/pembacaan tree
 		*/
		void printBinarySearchTree(Node* ptr){ //mencetak tree secara preorder dengan fungsi rekursif
			if (ptr!=nullptr){
				cout<< ptr->getNPM()<<" "<<ptr->getNama()<<endl; 
				printBinarySearchTree(ptr->getLeft());
        		printBinarySearchTree(ptr->getRight());
			}
		}
		Node *deleteNode(Node* ptr,long long int npm){
			//untuk mengecek tree sudah ada isinya atau kosong
			if (ptr==nullptr){
				return nullptr;
			}
			//memperkecil pencarian node ke kiri dari node yang dikunjungi
			else if(npm<ptr->getNPM()){
				ptr->setLeft(deleteNode(ptr->getLeft(),npm));
			}
			//memperkecil pencarian node ke kanan dari node yang dikunjungi
			else if(npm>ptr->getNPM()){
				ptr->setRight(deleteNode(ptr->getRight(),npm));
			}
			//menghapus node yang dikunjungi
			else{
				//delete leaf atau no child untuk root
				if(root->getLeft()==nullptr && root->getRight()==nullptr){
					root=nullptr;
				}
				//delete leaf atau no child selain root
				else if(ptr->getLeft()==nullptr && ptr->getRight()==nullptr){
					return nullptr;
				}
				//delete node dengan dua child untuk root
				else if(root->getLeft() && root->getRight() && root->getNPM()==npm){
					Node* child = findMax(root->getLeft()); //mencari nilai maksimal dikiri root untuk ditukar dengan root lalu dimasukkan ke node child
					root->setNPM(child->getNPM());
					root->setNama(child->getNama()); 
					root->setLeft(deleteNode(root->getLeft(),child->getNPM()));

				}
				//delete node dengan dua child selain root
				else if(ptr->getLeft() && ptr->getRight()){
					Node* child = findMax(ptr->getLeft()); //mencari nilai maksimal dikiri ptr untuk ditukar dengan root lalu dimasukkan ke node child
					ptr->setNPM(child->getNPM());
					ptr->setNama(child->getNama()); 
					ptr->setLeft(deleteNode(ptr->getLeft(),child->getNPM()));
				}
				//delete node dengan satu child
				else{
					//delete node untuk root
					if(root->getNPM()==npm){
						//memeriksa posisi cabang node berada di kiri atau kanan root lalu menampung isi cabang kedalam node children
						Node* children = (root->getLeft())? root->getLeft(): root->getRight(); 
						Node* curr = root; //memindahkan isi root kedalam node curr
						root=children; //mengganti isi root dengan children
						curr=nullptr; //menghapus node curr
					}
					//delete node untuk selain root
					else{
						//memeriksa posisi cabang node berada di kiri atau kanan ptr lalu menampung isi cabang kedalam node children
						Node* children = (ptr->getLeft())? ptr->getLeft(): ptr->getRight();
						Node* curr = ptr; //memindahkan isi ptr kedalam node curr
						ptr=children; //mengganti isi ptr dengan children
						curr=nullptr; //menghapus node curr
					}
				}
				return ptr;
			}
		}
		Node* findMax(Node* ptr){//mencari npm tertinggi dari anak suatu node
			//jika ada anak di kanan lakukan pengecekan 
			if(ptr->getRight()!=nullptr){
				while(ptr->getRight()!=nullptr){
					ptr=ptr->getRight();
				}
			}
			return ptr;
		}
		void displayBinarySearchTree(){
			printBinarySearchTree(root);
		}
		void destroyTree(Node* leaf){
			if (leaf!=nullptr){
				destroyTree(leaf->getLeft());
				destroyTree(leaf->getRight());
				delete leaf;
			}
		}
		
		void delNode(long long int npm){
			deleteNode(root,npm);
		}

    	~BinarySearchTree(){
			destroyTree(root);
		}
};

class avl{
	public:
		Node *root;

		Node* getRoot(){  //getter root
			return root;
		}
		void setRoot(Node* node){ //setter root
			root=node;
		}

		avl(){
			this->root=nullptr; //mengosongkan isi root
		};
		
		
		int height(Node *N)  //mengambil nilai height dari node
		{
			if (N == NULL)
				return 0;
			return N->getHeight();
		}

		int max(int a, int b)  //mengambil nilai max dari dua integer
		{
			return (a > b)? a : b;
		}
		
		Node* newNode(long long int npm,string nama)  //fungsi untuk membuat node kosong baru dengan input nama dan npm
		{
			Node* node = new Node();
			node->setNPM(npm);
			node->setNama(nama);
			node->setLeft(NULL);
			node->setRight(NULL);
			node->setHeight(1); 
			return(node);
		}
		
		Node *rightRotate(Node *y)  //fungsi untuk merotasi node ke kanan
		{
			//mendeklarasikan node baru untuk menampung sementara sebelum dilakukan rotasi
			Node *x = y->getLeft();
			Node *z = x->getRight();
		
			//merotasi node x,y dan z ke arah kanan 
			x->setRight(y);
			y->setLeft(z);
		
			// Update nilai heights node setelah dirotasi
			y->setHeight(max(height(y->getLeft()),
							height(y->getRight())) + 1);
			x->setHeight(max(height(x->getLeft()),
							height(x->getRight())) + 1);
		
			// Return root baru
			return x;
		}
		
		Node *leftRotate(Node *x)  //fungsi untuk merotasi node ke kiri
		{
			//mendeklarasikan node baru untuk menampung sementara sebelum dilakukan rotasi
			Node *y = x->getRight();
			Node *T2 = y->getLeft();
		
			//merotasi node x,y dan z ke arah kiri 
			y->setLeft(x);
			x->setRight(T2);
		
			// Update nilai heights node setelah dirotasi
			x->setHeight(max(height(x->getLeft()),
							height(x->getRight())) + 1);
			y->setHeight(max(height(y->getLeft()),
							height(y->getRight())) + 1);
		
			// Return root baru
			return y;
		}
		
		// mengambil node balance
		int getBalance(Node *N)
		{
			if (N == NULL)
				return 0;
			return height(N->getLeft()) - height(N->getRight());
		}
		
		//fungsi untuk menambah node kedalam tree
		void tambah(long long int npm, string nama){
			root = insert(root,npm,nama);
		}

		Node* insert(Node* node, long long int npm, string nama)
		{
			//fungsi BST untuk menambah node
			if (node == NULL)
				return(newNode(npm,nama));
			if (npm < node->getNPM())
				node->setLeft(insert(node->getLeft() , npm, nama));
			else if (npm > node->getNPM())
				node->setRight(insert(node->getRight(), npm, nama));
			else 
				return node;
		
			/* 2. Update height node */
			node->setHeight(1 + max(height(node->getLeft()),
								height(node->getRight())));
		
			/* 3. mengambil nilai balance node*/
				
			int balance = getBalance(node);
		
			// jika node tidak seimbang heightnya terdapat 4 kasus penyelesaian
		
			// kasus kiri-kiri
			if (balance > 1 && npm < node->getLeft()->getNPM())
				return rightRotate(node);  //lakukan rotasi ke kanan pada node
		
			// kasus kanan-kanan
			if (balance < -1 && npm > node->getRight()->getNPM())
				return leftRotate(node);  //lakukan rotasi ke kiri pada node
		
			// kasus kiri-kanan
			if (balance > 1 && npm > node->getLeft()->getNPM())
			{
				node->setLeft(leftRotate(node->getLeft()));  //lakukan rotasi ke kiri pada child sebelah kiri node
				return rightRotate(node); //lakukan rotasi ke kanan pada node
			}
		
			// kasus kanan-kiri
			if (balance < -1 && npm < node->getRight()->getNPM())
			{
				node->setRight(rightRotate(node->getRight()));  //lakukan rotasi ke kanan pada child sebelah kanan node
				return leftRotate(node);  //lakukan rotasi ke kiri pada node
			}
			
			return node;
		}
		
		void displayAvl(){  //fungsi untuk mencetak tree secara preorder
			printAvl(root);
		}
		
		void printAvl(Node *root)
		{
			if(root != NULL)
			{
				cout << root->getNPM() << " " << root->getNama() <<endl;
				printAvl(root->getLeft());
				printAvl(root->getRight());
			}
		}
		
		// Driver Code
};


int main(){
	int menu;
	long long int a;
	string b;

	//membuat objek dari class avl dan bst
	avl v1;
	BinarySearchTree bst;

	//insert node secara bst
	bst.insertNode(19081010050,"ani");
	bst.insertNode(19081010025,"nico");
	bst.insertNode(19081010078,"agus");
	bst.insertNode(19081010015,"rico");
	bst.insertNode(19081010040,"ayu");
	bst.insertNode(19081010065,"anggun");
	bst.insertNode(19081010085,"mia");
	bst.insertNode(19081010020,"ando");
	bst.insertNode(19081010070,"dava");
	
	while(true){
		cout << "----------Menu Pilihan----------" << endl;
		cout << "1.Delete Node pada Binary Search Tree" << endl;
		cout << "2.Insert Node pada AVL Tree" << endl;
		cout << "3.Selesai" << endl;
		cout << "masukkan pilihan menu : ";cin>>menu;
		
		
		if(menu==1){
			system("cls");
			long long int npm;
			
			cout << "----------Daftar Mahasiswa----------" << endl;
			bst.displayBinarySearchTree();  //mencetak isi tree
			cout << "------------------------------------" << endl;
			cout << "masukkan npm yang akan dihapus : ";cin>>npm;
			bst.delNode(npm);  //menghapus node secara bst
			v1.setRoot(bst.getRoot());  //lakukan update isi root pada objek avl
			cout << endl << endl;
			cout << "------Isi tree setelah dihapus-------" <<endl;
			bst.displayBinarySearchTree();  //mencetak isi tree
			cout << "------------------------------------" << endl;
			
			getch();
			system("cls");
			cout << endl;
			
		}
		else if(menu==2){
			system("cls");
			cout << "----------Daftar Mahasiswa----------" << endl;
			v1.setRoot(bst.getRoot());  //lakukan update isi root pada objek avl
			v1.displayAvl();  //mencetak isi tree
			cout << "------------------------------------" << endl;
			cout<<"NPM : ";cin>>a;  //input npm yang akan dimasukkan tree
			fflush(stdin);
			cout<<"nama : ";getline(cin,b);  //input nama yang akan dimasukkan tree
			v1.tambah(a,b);  //menambah node baru kedalam tree secara avl
			bst.setRoot(v1.getRoot());  //lakukan update isi root pada objek bst
			
			cout << "------Isi tree setelah ditambah-----" <<endl;
			v1.displayAvl();  //mencetak isi tree
			cout << "------------------------------------" << endl;
			
			getch();
			system("cls");
			
		}
		else{
			system("cls");
			cout << "keluar dari program" << endl;
			
			return false;
		}
	}
	
	
	return 0;
}
