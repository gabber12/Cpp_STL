#include <iostream>
#include "stl_split.hpp"
#include <vector>
#include <list>

using namespace std;
int main ()
{
	string v("abccbcbbcbbbjjjjc");
	vector<string> vv;
	vv.resize(10);
	int elem = split( v.begin(), v.end(),vv.begin(), 'c');
	cout << "No of elements : " << elem << endl;

	for(int i =0;i < elem;i++){
		for(int j =0;j < vv[i].size(); j++){
			cout << vv[i][j] <<" ";
		}
		cout << endl;
	}
}