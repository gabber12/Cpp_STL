#include <iostream>
#include "stl_split.hpp"
#include <vector>
#include <list>

using namespace std;
int main ()
{
	vector<int> v;
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(3);
	v.push_back(4);
	vector<vector<int> > vv;
	vv.resize(10);

	int elem = split( v.begin(), v.end(),vv.begin(), 3);
	cout << "No of elements : " << elem << endl;

	for(int i =0;i < elem;i++){
		for(int j =0;j < vv[i].size(); j++){
			cout << vv[i][j] <<" ";
		}
		cout << endl;
	}
}