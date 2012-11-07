#include <iostream>
#include "avl_coorr.cpp"

using namespace std;

int main(){
	pair<int,int> p(1,2);
	avl<int,int> n(p);
	n.insert(pair<int, int> (2,7));
	n.insert(pair<int, int> (6,7));
	n.insert(pair<int, int> (9,7));
	n.insert(pair<int, int> (3,4));
	n.insert(pair<int, int> (8,10));
	n.insert(pair<int, int> (7,11));
	avl<int, int> ne ;
	ne = n;
	ne[9] = 24;
	cout << n[9]<< ne[9]<< endl;
	// n.check_tree();
	avl<int, int> ::const_iterator it = n.begin();
	for(avl<int, int>::iterator it = n.begin(); it != n.end(); it++){
		cout << (*it).first << " >> "<< (*it).second<<endl;
	}
	
	for(avl<int, int>::reverse_iterator it = n.rbegin(); it != n.rend(); it++){
		cout << (*it).first << " >> "<< (*it).second<<endl;
	}
	
	return 0;
}