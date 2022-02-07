#include <iostream>
#include "Node.h"
using namespace std;

class NodeStatus {
	private:
		Node* node;
		int status;
	public:
		NodeStatus(){
			node=nullptr;
			status=0;
		}
		void setNodeStatus(Node* start, int s){
			node=start;
			status=s;
		}
		Node* getNode(){
			return node;
		}
		int getStatus(){
			return status;
		}
};

