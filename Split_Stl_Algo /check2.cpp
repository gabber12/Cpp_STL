#include <iostream>
#include "stl_split.hpp"
#include <list>
#include <list>

using namespace std;
int main ()
{
	list<int> v;
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(3);
	v.push_back(4);
	list<list<int> > vv;
	vv.resize(10);

	int elem = split( v.begin(), v.end(),vv.begin(), 3);
	cout << "No of elements : " << elem << endl;
	int k =0;
	for(list<list<int> >::iterator i =vv.begin();k != elem;i++,k++){
		for(list<int> ::iterator j =i->begin(); j != i->end(); j++){
			cout << *j <<" ";
		}
		cout << endl;
	}
}