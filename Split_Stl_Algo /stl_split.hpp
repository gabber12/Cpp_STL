#include <typeinfo>
#include <exception>

using namespace std;

template<typename itr, typename IT, typename ITR>

unsigned int split(const IT start, const IT end, ITR nex , itr val) {
	
	typename iterator_traits<ITR>::value_type temp; 
	typename iterator_traits<IT>::value_type check;
	typedef typename iterator_traits<ITR>::value_type cont_type;

	if (typeid(check) != typeid(val)){
		throw bad_typeid();
	}

	if (typeid(typename cont_type::iterator) != typeid(start) ) {
		throw bad_typeid();
	}

	unsigned int no_elem = 0;       // Check if the val is present in the sequence or not
	IT it = start;

	while (it != end) {
		if (*it != val) {

			temp.push_back(*it);
			it++;

		} else {
			
			*nex = temp;
			temp.clear();

			nex++;
			it++;
			no_elem++;
			
		}

	}
	
	*nex = temp;

	return no_elem + 1;

}
/* DISCLAIMER */
/*------------*/

/* Made by Divanshu Garg and Shubham Sharma */
/* The function may be used or modified until this disclaimer is kept intact*/

/*Documentation*/
/* -----------*/

/* The Algorithm Works on *
	* Vector
	* List
	* String
and other stl containers (although we have not tested it).
*/

/* Function return the number of segment seperated by delimiter sent as val(the last argument) *
 * A 2d Container with appropriate size has to be sent *
 * The function return bad_typeid() exception in case of unmatching iterator types sent *
*/