#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

template<typename t1, typename t2 ,typename allocator = pair<t1,t2> >

/* Node Stores Height for Constant time operations like rotation */
class node {
public:
/* Pair is used first value is  key second is Value*/
	allocator p;
	

	int height;

	node* parent;
	node* left;
	node* right;

	node() {
		left = NULL; 
		right = NULL; 
		height = 1;
		parent = NULL;
	}

	node(int k,int v){
		p.second = v;
		p.first = k;
		height = 1;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	~node(){
		delete *left;
		delete *right;
	}
	
};

/* Stream operator Overloading on Node for faster debugging */
template<class t1,class t2>
ostream& operator<<(ostream& ostr, node<t1,t2> n) {
		ostr << "("<<n.p->second<<", "<<n.p->first<<")";
		return ostr;
}

template<class t1, class t2>
class avl {
	typedef node<t1, t2> nod;
	size_t sz;
	/* Seven Typedefs for Stl Container */
	typedef t1 key_type;
	typedef t2 mapped_type;
	typedef pair<const t1, t2> value_type;
	typedef pair<const t1, t2>& reference;
	typedef const pair<const t1, t2>& const_reference;
	typedef size_t size_type;
	typedef pair<const t1, t2> allocator_type;


	nod *root;

	

	/* All Basic Avl Operations In Private 
	 * while Only the wrapper functions will be in 
	 * public.
	*/

	/* Helper Functions */
	nod* left_most(nod* r){
		if(r->left == NULL)
			return r;
		else
			return left_most(r->left);
	}
	nod* right_most(nod* r){
		if(r->right == NULL)
			return r;
		else
			return right_most(r->right);
	}

	/* Helper Functions End */

	/* Avl Helper Function Starts */

	/* Use Of These Simple Function *
	 *Saves a Lot Of Seg Faults *
	 */

	int height(nod* x){
		if( x == NULL){
			return 0;
		}
		return x->height;
	}

	/* Used To get the Balance Factor */
	int height_diff(nod* x){
		if(x == NULL){
			return 0;
		}
		return height(x->left) - height(x->right);
	}

	

	nod* right_rotate(nod * x){
#ifdef DEBUG		
		cout << "In right_rotate() function" << endl;
#endif
		nod* xleft = x->left;
		nod* xleft_right = xleft->right;
		nod* xparent = x->parent;

		xleft->right = x;
		xleft->parent = xparent;

		if(xparent != NULL){
			if(xparent-> left == x){
				xparent->left = xleft;
			} else{
				xparent->right = xleft;
			}
		

					
		}
		x->parent = xleft;
		x->left = xleft_right;

		if(xleft_right)
			xleft_right->parent = x;

		/* Height Adjustments */
		x->height = max(height(x->left), height(x->right));
		xleft->height = max(height(xleft->left), height(xleft->right));
		
		return xleft;	

	}
	nod* left_rotate(nod * x){
#ifdef DEBUG	
		cout << "In left_rotate()"<< x->p->first <<" function" << endl;
#endif
		nod* xright = x->right;
		nod* xrightleft = xright->left;

		nod* xparent = x->parent;

		xright->left = x;
		xright->parent = xparent;
		
		if(xparent != NULL){
	
			if(xparent-> left == x){
				xparent->left = xright;
			} else{
				xparent->right = xright;
			}
		

				
		}
		x->parent = xright;
		x->right = xrightleft;
		
		if(xrightleft)
			xrightleft -> parent = x;
		
		/* Height Adjustments */
		x->height = max(height(x->left), height(x->right));
		xright->height = max(height(xright->left), height(xright->right));
		
	
		return xright;

	}
	/* Avl Helper funciton Ends */

	/* Core Avl Operations */
	nod* search(nod* r, t1 k){

		if (r == NULL) {

			return NULL;

		} else if (r->p.first == k){

			return r;

		}
		else if (r->p.first >k){

			return search(r->left, k);

		} else{

			return search(r->right, k);

		}
	}

	nod* insertion(t1 k,t2 m, nod* r){

		if(r == NULL){
			/* Main Code Goes Here */
#ifdef DEBUG
			cout <<"Returned New Node";
#endif
			nod * n = new nod(k,m);
			
#ifdef DEBUG
			cout << "At node : "<< n->p->first << endl;
#endif
			return n;

		} else if( r->p.first == k) {

			r->p.second = m;

		} else if ( r->p.first >k){
#ifdef DEBUG
			cout << "Going Left : "<<r->p.first << endl;
#endif		
			nod * temp = insertion (k, m, r->left);

			r->left = temp;
			temp->parent = r;


		} else {
#ifdef DEBUG
			cout << "Going Right: "<<r->p->first<< endl;
#endif
			nod* temp = insertion (k, m, r->right);
			r->right = temp;
			temp->parent = r;

		}
		/* Height Adjustment */
		r->height = max(height(r->left), height(r->right)) + 1;
#ifdef DEBUG
		cout <<"r->height : "<< r->height << endl;
#endif

		int bal_factor = height_diff(r);
#ifdef DEBUG
		cout << "Balance Factor At p->first : "<< r->p->first <<">>>>"<<bal_factor<<"height("<<height(r->left)<<", " << height(r->right) <<")"<< endl;
#endif
		/* The Four Cases 
		 * left_right
		 * leftleft
		 * rightleft
		 * right_right
		 */

		/* LEFT LEFT CASE */
		/* Means Insertion is done in left left side 
		 * as height(left)> height(right) and left->p->first >p->first 
		 */
		if(bal_factor > 1 && k < r->left->p.first){
			return right_rotate(r);
		}
		/* RIGHT RIGHT CASE */
		if(bal_factor < -1 && k > r->right->p.first){
			return left_rotate(r);
		}
		/* LEFT RIGHT CASE */
		if(bal_factor > 1 && k > r->left->p.first){
			r->left = left_rotate(r->left);
			return right_rotate(r);
		}
		/* RIGHT LEFT CASE */
		if(bal_factor < -1 && k < r->right->p.first){
			r->right = right_rotate(r->right);
			return left_rotate(r);
		}
		return r;
	}

	nod * minimum_val(nod* node) {

    	nod* temp = node;
 
	    
	    while (temp->left != NULL)
	        temp = temp->left;
	 
	    return temp;
	}

	nod* delet(nod* r, t1 k) {
     
	    if (r == NULL)
	        return r;
	 
	    if ( k < r->p->first ){
	    	nod * temp = delet (r->left, k);
	        r->left = temp;
	        temp->parent = r;

	    } else if( k > r->p->first ) {
	    	nod* temp = delet (r->right, k);
	        r->right = temp;
	        temp ->parent = r;

	    }
	 
	    // if p->first is same as root's p->first, then This is the node
	    // to be deleted
	    else
	    {
	        // node with only one child or no child
	        if( (r->left == NULL) || (r->right == NULL) )
	        {
	            nod * temp;

	            if(r->left)
	            	temp = r->left;
	            else
	            	temp = r->right;
	 
	            
	            if(temp == NULL)
	            {

	                temp = r;
	                r = NULL;

	            } else {

	             *r = *temp; 

	         	}
	 
	            free(temp);
	        }

	        else
	        {
	            
	            nod* temp = minimum_val(r->right);
	            r->p->first = temp->p->first;
	            r->right = delet(r->right, temp->p->first);
	        }
	    }
	 
	    
	    if (r == NULL)
	      return r;
	 
	    
	    r->height = max(height(r->left), height(r->right)) + 1;
	 
	    
	    int balance = height_diff(r);
	 
	    // If this node becomes unbalanced, then there are 4 cases
	 
	    // Left Left Case
	    if (balance > 1 && height_diff(r->left) >= 0){
	        return right_rotate(r);
	    }
	 
	    // Left Right Case
	    if (balance > 1 && height_diff(r->left) < 0)
	    {
	        root->left =  left_rotate(r->left);
	        return right_rotate(r);
	    }
	 
	    // Right Right Case
	    if (balance < -1 && height_diff(r->right) <= 0){

	        return left_rotate(r);
	 	}
	    // Right Left Case
	    if (balance < -1 && height_diff(r->right) > 0)
	    {

	        r->right = right_rotate(r->right);
	        return left_rotate(r);
	    }
	 
	    return r;
	}
	/* Core Avl Operations End */
	/* utility  stl function*/
	
public:
	/* STL Functions */

	

	
	class iterator {
	public:

		nod* itr;
		nod* left_most(nod* r) {

			if (r == NULL) {

				return NULL;

			} else if (r->left == NULL) {

				return r;
			} else {
				return left_most(r->left);
			}
		}	
		nod* right_most(nod* r){
			if(r == NULL){
				return NULL;
			} else if (r->right == NULL) {
				return r;
			} else {
				return right_most(r->right);
			}
		}

		iterator(){}
		iterator(nod* def){
			itr = def;
		}
		
		
		void operator++(){
			
			
			if(itr->right != NULL){
				
				itr = left_most(itr->right);
			} else {
			

				while(true){
					if(itr->parent == NULL){
						itr = NULL;
						return ;

					}else if(itr->parent->p.first > itr->p.first){
						
						itr = itr->parent;
						return ;
					}
					itr = itr->parent;
				}
					
			}
		}
		void operator--(){
			
			
			if(itr->left != NULL){
				
				itr = right_most(itr->left);
			} else {
			
				while(true){
					if(itr->parent == NULL){
						itr = NULL;
						return ;

					}else if(itr->parent->p.first < itr->p.first){
						
						itr = itr->parent;
						return ;
					}
					itr = itr->parent;
				}
				
			}
		}
		void operator++(int){
			
			
			if(itr->right != NULL){
				
				itr = left_most(itr->right);
			} else {
			
				while(true){
					if(itr->parent == NULL){
						itr = NULL;
						return ;

					}else if(itr->parent->p.first > itr->p.first){
						
						itr = itr->parent;
						return ;
					}
					itr = itr->parent;
				}
					
			}
		}
		void operator--(int){
			
			
			if(itr->left != NULL){
				
				itr = right_most(itr->left);
			} else {
			
				while(true){
					if(itr->parent == NULL){
						itr = NULL;
						return ;

					}else if(itr->parent->p.first < itr->p.first){
						
						itr = itr->parent;
						return ;
					}
					itr = itr->parent;
				}
				
			}
		}
		void set(nod* pointer){
			itr = pointer;
		}
		pair<t1,t2>& operator*(){

			return itr->p;
		}
		bool operator!=(const iterator &it){
			return it.itr != itr;
		}
		

	};
	class const_iterator :public iterator{
	public:
		nod* itr;
		
		const_iterator(){}
		const_iterator(nod* def){
			itr = def;
		}
		
		
		const pair<t1,t2> operator*(){

			return itr->p;
		}
		bool operator!=(const iterator &it){
			return it.itr != itr;
		}
		

	};
	class reverse_iterator :public iterator {
	public:

		nod* itr;
		

		reverse_iterator(){}
		reverse_iterator(nod* def){
			itr = def;
		}
		
		
		
		void operator++(){
			
			
			if(itr->left != NULL){
				
				itr = right_most(itr->left);
			} else {
			
				while(true){
					if(itr->parent == NULL){
						itr = NULL;
						return ;

					}else if(itr->parent->p.first < itr->p.first){
						
						itr = itr->parent;
						return ;
					}
					itr = itr->parent;
				}
				
			}
		}
		void operator++(int){
			
			
			if(itr->left != NULL){
				
				itr = right_most(itr->left);
			} else {
			
				while(true){
					if(itr->parent == NULL){
						itr = NULL;
						return ;

					}else if(itr->parent->p.first < itr->p.first){
						
						itr = itr->parent;
						return ;
					}
					itr = itr->parent;
				}
				
			}
		}

		pair<t1,t2> operator*(){

			return pair<t1,t2>(itr->p.first, itr->p.second);
		}
		bool operator!=(const reverse_iterator &it){
			return it.itr != itr;
		}
		

	};

						/* STL FUNCTIONS START */
///////////////////////////////////////////////////////////////////////////////////////////////////


	/* 1.) DeFAult Constructor */
	avl(){
		root = NULL;
		sz = 0;
	}

	avl(pair<t1, t2> p){
		root = new nod(p.first, p.second);
		sz = 1;
	}

	/* 2.)Copy Constructor */
	avl(avl<t1,t2>& nex){
		root = NULL;
		sz = 0;
		avl<t1,t2>::iterator it;
		for(it = nex.begin();it!=nex.end();++it){
			
			insert(pair<int , int >((*it).first, (*it).second));
		}
		
	}

	/* 3.)Operator = */
	avl<t1,t2> operator=(avl<t1,t2>& nex){
		avl<t1,t2> tmp;
		avl<t1,t2>::iterator it;
		for(it = nex.begin();it!=nex.end();++it){
			tmp.insert((*it));
		}
		return tmp;
	}
	
	/* 4.) */
	const_iterator begin() const{
		return const_iterator(left_most(root));
		
	}
	iterator begin(){
		return iterator(left_most(root));
		
	}

	
	/* 5.) */
	iterator end(){
		return iterator(NULL);
	}
	/* 6.) */
	void insert(pair<t1,t2> p){
		root = insertion(p.first, p.second, root);
		root->parent = NULL;
		sz++;
	}

	/* 7.) */
	void erase(t1 k){
		root = delet(root, k);
		root->parent = NULL;
		sz--;
	}

	/* 8.) */
	size_t size(){
		return sz;
	}

	/* 9.) */
	void clear(){
		delete root;
		root = NULL;

	}

	/* 10.) */
	bool empty(){
		return sz == 0;
	}

	/* 11.) */
	bool count(t1 k){
		return search(root, k) != -1;
	}

	/* 12.) */
	size_t max_size(){
		return INT_MAX;
	}

	/* 13.) */
	/* Takes Log(n) Complexiety searchs for the p->first and returns the reference to the node */
	t2& operator[](t1 k){
		nod * snode = search(root, k);
	
		if(snode == NULL){
			insert(pair<t1,t2> (k,0));
			snode = search(root, k);

		}
		return (snode)->p.second;
	}

	/* 14.) */
	iterator upper_bound(t1 k){
		iterator it(search(root, k));
		++it;
		return it;

	}

	/* 15.) */
	iterator lower_bound(t1 k){
		iterator it(search(root, k));
		
		return it;

	}

	/* 16.) */
	pair<iterator, iterator> equal_range(t1 k){
		return pair<iterator ,iterator>(lower_bound(k), upper_bound(k));
	}

	/* 17.) */
	reverse_iterator rbegin(){
		return reverse_iterator(right_most(root));
	}

	/* 18.) */
	reverse_iterator rend(){
		return reverse_iterator(NULL);
	}

	/* 19.) */
	iterator find(t1 k){
		return iterator(search(root, k));
	}

	/* 20.) */
	~avl(){
		free(root);
	}

	/* 21.) */
	const_iterator cbegin(){
		return const_iterator(left_most(root));
		
	}

	/* 22.) */
	const_iterator cend(){
		return const_iterator(NULL);
	}

	/* Bonus Function to Check Functionality of AVL TREE */
	/* Checks for balance factor in Pre Order Fashion */

	void check_balance_factor(nod* r){
		if(r == NULL)
			return;
		check_balance_factor(r->left);
		cout <<"Parent"<<r->parent<< "p->first : " << r->p->first<< " height_diff : "<<height_diff(r) <<endl;
		if(r->left)
			cout <<"Left : "<<r->left->p->first << endl;
		if(r->right)
			cout <<"Right : " <<r->right->p->first<< endl;
		check_balance_factor(r->right);
	}

	void check_tree(){
		check_balance_factor(root);
	}
};



