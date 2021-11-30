//HW5 by Vipul Sawant		
//SU ID 347120278
//vasawant

//HW5  AVL Tree
//Due: Saturday (Nov. 20) at 11:59PM
//This homework requires more efforts. You should get started as soon as possible.

#include <iostream> //to use cout
#include <algorithm> //to use max function such as  i = max(a, b);

using namespace std;

class node {
public:
	int value;
	int height;//this is tree height. Leaf node is 1; empty node (i.e., NIL) is 0
	node* parent;//nullptr for root
	node* l_child;
	node* r_child;
	bool is_left_child; //true if this node is the left child of its parent node; else false;
	bool is_right_child; //true if this node is the right child of its parent node; else false;
	node() {}
	node(int i) { value = i; height = 1; parent = l_child = r_child = nullptr; is_left_child = is_right_child = false; }
};

class avl_tree {
public:
	node* root;
	avl_tree() {
		root = nullptr;
	}
	void add_node(int i);

	void delete_node(int i);
	
	void in_order_traversal(node* p); //such as (2 5) (3 3) (5 2) (6 1) .....  (value height)
					  //Height of leaf node is 1.

	pair<node*, int> height_update(node* p);

	void L_Rotate(node* p);


	void R_Rotate(node* p);
};


int main() {
	avl_tree t1;
	t1.add_node(100);
	t1.add_node(80);
	t1.add_node(110);
	t1.add_node(200);
	t1.in_order_traversal(t1.root);
	t1.delete_node(100);
	t1.in_order_traversal(t1.root);
	return 0;
}
void avl_tree::add_node(int i) {
	//cout << "adding node :" << i << endl;
	node* n1{ new node(i) };
	if (root == nullptr) {
		root = n1;
	}
	else {
		int side = 0;
		node* temp{ root };
		node* n2{ root };
		while (temp != nullptr) {
			if (i >= temp->value) {
				n2 = temp;
				temp = temp->r_child;
				side = 1;
			}
			else {
				n2 = temp;
				temp = temp->l_child;
				side = 0;
			}
		}
		if (side == 0) {
			n2->l_child = n1;
			n1->parent = n2;
			n1->is_left_child = true;
		}
		else {
			n2->r_child = n1;
			n1->parent = n2;
			n1->is_right_child = true;
		}
	}
	pair<node*, int>p1;
	p1= height_update(n1);
	//if(p1.first ==nullptr)
	//cout <<p1.first<<" " << "height Difference: " << p1.second << endl;
	//else
		//cout << p1.first->value << " " << "height Difference: " << p1.second << endl;
	switch (p1.second) 
	{
	case 1: R_Rotate(p1.first);
		height_update(p1.first);
		break;
	case 2: L_Rotate(p1.first->l_child);
		height_update(p1.first->l_child->l_child);
		    R_Rotate(p1.first);
			height_update(p1.first);
		break;
	case 3: L_Rotate(p1.first);
		height_update(p1.first);
		break;
	case 4: R_Rotate(p1.first->r_child);
			height_update(p1.first->r_child->r_child);
			L_Rotate(p1.first);
			height_update(p1.first);////change later to p.first
		break;
	default:
		break;
	}

}
void avl_tree::in_order_traversal(node* p) {
	if (p == nullptr) { return; }
	in_order_traversal(p->l_child);
	if(p->parent==nullptr)
	cout <<"( " << p->value <<" " << p->height <<" )" << endl;
	else
		cout<<"( " << p->value <<" " << p->height << " )" << endl;
	in_order_traversal(p->r_child);
}
pair<node*, int> avl_tree::height_update(node* p) {
	int lchild=0, rchild = 0;
	node* p1{ p };
	node* p2{ p };
	while(p1!=nullptr){
		if (p1->l_child == nullptr) {
			lchild = 0;
		}
		else
			lchild = p1->l_child->height;
		if (p1->r_child == nullptr) {
			rchild = 0;
		}
		else
			rchild = p1->r_child->height;
		p1->height = max(lchild,rchild) + 1;
		p1 = p1->parent;
	}
	lchild = rchild = 0;
	while (p2 != nullptr) {
		if (p2->parent == nullptr) { return{ nullptr,0 }; }
		if (p2->parent->l_child == nullptr) {
			lchild = 0;
		}
		else
			lchild = p2->parent->l_child->height;
		if (p2->parent->r_child == nullptr) {
			rchild = 0;
		}
		else
			rchild = p2->parent->r_child->height;
		//cout << "height minus: " << abs(lchild - rchild) << endl;
		if (abs(lchild - rchild) > 1) {
			int val = 0;
			node* p3{ p2->parent };
			node* p4{ p2->parent };
				lchild = rchild = 0;
				if (p3->l_child == nullptr) {
					lchild = 0;
				}
				else
					lchild = p3->l_child->height;
				if (p3->r_child == nullptr) {
					rchild = 0;
				}
				else
					rchild = p3->r_child->height;
				if (lchild > rchild) {
					p3 = p3->l_child;
				}
				else {
					p3 = p3->r_child;
				}
				p4 = p3;
				lchild = rchild = 0;
				if (p4->l_child == nullptr) {
					lchild = 0;
				}
				else
					lchild = p4->l_child->height;
				if (p4->r_child == nullptr) {
					rchild = 0;
				}
				else
					rchild = p4->r_child->height;
				if (lchild > rchild) {
					p4 = p4->l_child;
				}
				else {
					p4 = p4->r_child;
				}
			if (p3->is_left_child == true && p4->is_left_child == true)
				val = 1;
			if (p3->is_left_child == true && p4->is_right_child == true)
				val = 2;
			if (p3->is_right_child == true && p4->is_right_child == true)
				val = 3;
			if (p3->is_right_child == true && p4->is_left_child == true)
				val = 4;
			return{ p2->parent,val };
		}
		else {
			p2 = p2->parent;
		}
	}
	
}
void avl_tree::L_Rotate(node* p) {
	//cout << "Entered L rotate" << endl;
	node* prlight{ p->r_child->l_child };
	node* temp{ p->r_child };
	if (p->parent == nullptr) {
		p->r_child == nullptr;
		temp->l_child = p;
		p->r_child = prlight;
		if (prlight != nullptr) {
			prlight->parent = p;
			prlight->is_left_child = false;
			prlight->is_right_child = true;
		}
		temp->parent = p->parent;
		temp->is_right_child = false;
		temp->is_left_child = false;
		p->parent = temp;
		p->is_right_child = false;
		p->is_left_child = true;
		root = temp;
	}
	else {
		p->r_child == nullptr;
		if (p->is_left_child == true) {
			p->parent->l_child = temp;
			temp->is_right_child = false;
			temp->is_left_child = true;
		}
		else { p->parent->r_child = temp;
		temp->is_left_child = false;
		temp->is_right_child = true;
		}
		temp->l_child = p;
		p->r_child = prlight;
		if (prlight != nullptr) {
			prlight->parent = p;
			prlight->is_left_child = false;
			prlight->is_right_child = true;
		}
		temp->parent = p->parent;
		p->parent = temp;
		p->is_right_child = false;
		p->is_left_child = true;
	}
}
void avl_tree::R_Rotate(node* p) {
	//cout << "entered R rotate" << endl;
	node* plright{ p->l_child->r_child };
	node* temp{ p->l_child };
	if (p->parent == nullptr) {
		p->l_child == nullptr;
		temp->r_child = p;
		p->l_child = plright;
		if (plright != nullptr) {
			plright->parent = p;
			plright->is_left_child = true;
			plright->is_right_child = false;
		}
		temp->parent = p->parent;
		temp->is_right_child = false;
		temp->is_left_child = false;
		p->parent = temp;
		p->is_right_child = true;
		p->is_left_child = false;
		root = temp;
	}
	else {
		p->l_child == nullptr;
		if (p->is_right_child == true) {
			p->parent->r_child = temp;
			temp->is_right_child = true;
			temp->is_left_child = false;
		}
		else { p->parent->l_child = temp;
		temp->is_left_child = true;
		temp->is_right_child = false;
		}
		temp->r_child = p;
		p->l_child = plright;
		if (plright != nullptr) {
			plright->parent = p;
			plright->is_right_child = false;
			plright->is_left_child = true;
		}
		temp->parent = p->parent;
		p->parent = temp;
		p->is_right_child = true;
		p->is_left_child = false;
	}
}
void avl_tree::delete_node(int i) {
	
	node* p1{ root };
	node* p2{ root };
	while (p1->value != i) {
		if (i < p1->value) { p1 = p1->l_child; }
		else { p1 = p1->r_child; }
		if (p1 == nullptr) {
			cout << "Node "<<i<<" is not present in tree" << endl;
			return;
		}
	}
	if (p1->l_child == nullptr && p1->r_child == nullptr) {
		p2 = p1->parent;
		if (p1->is_left_child == true) {
			p1->parent->l_child = nullptr;
		}
		else {
			p1->parent->r_child = nullptr;
		}
	}
	else {
		//cout << "entered else" << endl;
		if (p1->l_child != nullptr && p1->l_child->l_child == nullptr && p1->l_child->r_child == nullptr) {
			if (p1->is_left_child == true ) {
				node* p3{ p1->r_child };
				node* p4{ p1->l_child };
				p1->parent->l_child = p4;
				p4->is_left_child = true;
				p4->is_right_child = false;
				p4->parent = p1->parent;
				p4->r_child = p3;
				p3->parent = p4;
				p2 = p1->parent->l_child;

			}
			else {
				node* p3{ p1->r_child };
				node* p4{ p1->l_child };
				p1->parent->r_child = p4;
				p4->is_left_child = false;
				p4->is_right_child = true;
				p4->parent = p1->parent;
				p4->r_child = p3;
				p3->parent = p4;
				p2 = p1->parent->r_child;
			}
		}
		else {
			if (p1->r_child != nullptr && p1->r_child->l_child == nullptr && p1->r_child->r_child == nullptr) {
				if (p1->is_left_child == true) {
					node* p3{ p1->r_child };
					node* p4{ p1->l_child };
					p1->parent->l_child = p3;
					p3->is_left_child = true;
					p3->is_right_child = false;
					p3->parent = p1->parent;
					p3->l_child = p4;
					if (p4 != nullptr)
						p4->parent = p3;
					p2 = p1->parent->l_child;
				}
				else {
					if (p1->is_right_child == true) {
						node* p3{ p1->r_child };
						node* p4{ p1->l_child };
						p1->parent->r_child = p3;
						p3->is_left_child = false;
						p3->is_right_child = true;
						p3->parent = p1->parent;
						p3->l_child = p4;
						if (p4 != nullptr)
							p4->parent = p3;
						p2 = p1->parent->r_child;

					}
				}
			}
			else {
				//cout << "entered last loop" << endl;
				if (p1->l_child->r_child != nullptr) {
					node* p5{ p1->l_child };
					//cout << "value of p5" << p5->value << endl;

					while (p5->r_child) {
						p5 = p5->r_child;
					}
					//cout << "node to change with" << p5->value << endl;
					node* temp{ p5->l_child };
					node* parent{ p5->parent };
					//cout << "value before deletion " << p1->value << endl;
					p1->value = p5->value;
					p5->parent->r_child = nullptr;
					if (temp != nullptr) {
						parent->r_child = temp;
						temp->parent = parent;
						temp->is_right_child = true;
						temp->is_left_child = false;
					}
					p2 = parent;
				}
				else {
					node* p6{ p1->r_child };
					//cout << "value of p5" << p5->value << endl;

					while (p6->l_child) {
						p6 = p6->l_child;
					}
					//cout << "node to change with" << p5->value << endl;
					node* temp{ p6->r_child };
					node* parent{ p6->parent };
					//cout << "value before deletion " << p1->value << endl;
					p1->value = p6->value;
					p6->parent->l_child = nullptr;
					if (temp != nullptr) {
						parent->l_child = temp;
						temp->parent = parent;
						temp->is_right_child = false;
						temp->is_left_child = true;
					}
					p2 = parent;
				}
			}
		}
	}
	pair<node*, int>n1;

	//cout << "************************************************************************************************************" << endl;
	while (p2 != nullptr) {
		//cout << "value of p2: " << p2->value << endl;
		if (p2->l_child == nullptr && p2->r_child == nullptr) {
			n1=height_update(p2);
		}
		else {
			if (p2->l_child != nullptr) {
				n1=height_update(p2->l_child);
			}
			else {
				n1=height_update(p2->r_child);
			}
		}
		//if (n1.first == nullptr)
			//cout << n1.first << " " << "height Difference: " << n1.second << endl;
		//else
			//cout << n1.first->value << " " << "height Difference: " << n1.second << endl;
		switch (n1.second)
		{
		case 1: R_Rotate(n1.first);
			height_update(n1.first);
			break;
		case 2: L_Rotate(n1.first->l_child);
			height_update(n1.first->l_child->l_child);
			R_Rotate(n1.first);
			height_update(n1.first);
			break;
		case 3: L_Rotate(n1.first);
			height_update(n1.first);
			break;
		case 4: R_Rotate(n1.first->r_child);
			height_update(n1.first->r_child->r_child);
			L_Rotate(n1.first);
			height_update(n1.first);////change later to p.first
			break;
		default:
			break;
		}
		p2 = p2->parent;
	}
}