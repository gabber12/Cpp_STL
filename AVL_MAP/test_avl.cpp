#include <iostream>
#include "avl_coorr.hpp"

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
	/* made another avl and copying older to new */
	avl<int, int> ne ;
	ne = n;
	ne[9] = 24;
	

	/* Printing The items */
	cout <<"Printing items of map using Forward iterator" << endl;
	for(avl<int, int>::iterator it = n.begin(); it != n.end(); it++){
		cout << (*it).first << " >> "<< (*it).second<<endl;
	}

	cout <<"Printing items of map using Reverse iterator" << endl;
	for(avl<int, int>::reverse_iterator it = n.rbegin(); it != n.rend(); it++){
		cout << (*it).first << " >> "<< (*it).second<<endl;
	}
	
	return 0;
}