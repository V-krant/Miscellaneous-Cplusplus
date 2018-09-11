//Sparse vector operations

#include <iostream>
#include <fstream>

using namespace std;

ofstream out("data1.txt");

class node {
public:
	int value;
	int position;
	node * next;
	node() { value = -9999; position = -1; next = nullptr; }
	node(int i, int j) { value = i; position = j; next = nullptr; }
};

class my_vector {
public:
	int size;
	int num_nodes; //number of non-zero elements
	node * head;
	my_vector() { size = num_nodes = 0; head = nullptr; }

	void add_node(int v, int p); //add a new node with value v and position p;
								 //if a node at position p already exists, update its value to v

	void make_random_vector(int s, int n, int k);
	//set the value of size  to s;
	//randomly create n nodes in -(k-1) to k-1

	my_vector operator+(my_vector V); //vector addition

	int operator*(my_vector V);//inner product

	void print();
};

void my_vector::make_random_vector(int s, int n, int k) {
	size = s;
	for (int i = 0; i < n; i++) {
		int p = rand() % s;
		int v = rand() % (2 * k - 1) - (k - 1);
		add_node(v, p);
	}
}

void my_vector::print() {
	out << endl;
	node * p = head;
	while (p != nullptr) {
		out << p->value << " " << p->position << "  ";
		p = p->next;
	}
}

void my_vector::add_node(int v, int p) {
	node *p1 = head,*prevp1=nullptr;
	int added = 0;
	if (v == 0) {
		while (p1 != nullptr) {
			if (p1->position == p) {
				p1->value = 0;
				if (p1 == head)head = p1->next;
				else if (p1->next == nullptr)prevp1->next = nullptr;
				else prevp1->next = p1->next;
				num_nodes--;
			}
			prevp1 = p1;
			p1 = p1->next;
		}
	}
	else {
		while (p1 != nullptr) {
			if (p1->position == p) {
				p1->value = v;
				added = 1;
			}
			p1 = p1->next;
		}
		if (added == 0) {
			node *n1,*n2=head,*n2prev=nullptr,*temp=nullptr;
			int a = 0;
			n1 = new node(v, p);
			while (n2 != nullptr) {
				if (p < n2->position) {
					temp = n2;
					break;
				}
				a = 1;
				n2prev = n2;
				n2 = n2->next;
			}
			if (temp == nullptr) {
				if (a == 1) {
					n1 ->next = nullptr;
					n2prev->next = n1;					
				}
				else {
					n1->next = head;
					head = n1;				
				}
			}
			else if(temp==head) {
				n1->next = temp;
				head = n1;
			}
			else {
				n1->next = temp;
				n2prev->next = n1;			
			}
			num_nodes++;
		}
	}
}

my_vector my_vector::operator+(my_vector V) {
	my_vector temp;
	if (size == V.size) {
		node *p1 = head, *p2 = V.head, *a1 = temp.head, *a1prev = nullptr;
		while (p1 != nullptr || p2 != nullptr) {
			if (p1 == nullptr) {
				a1 = new node(p2->value, p2->position);
				if (p2 == V.head) {
					temp.head = a1;
				}
				else {
					a1prev->next = a1;
				}
				a1prev = a1;
				p2 = p2->next;
			}
			else if (p2 == nullptr) {
				a1 = new node(p1->value, p1->position);
				if (p1 == head) {
					temp.head = a1;
				}
				else {
					a1prev->next = a1;
				}
				a1prev = a1;
				p1 = p1->next;
			}
			else {
				if (p1->position < p2->position) {
					a1 = new node(p1->value, p1->position);
					if (temp.head == nullptr) {
						temp.head = a1;
					}
					else {
						a1prev->next = a1;
					}
					a1prev = a1;
					p1 = p1->next;
				}
				else if (p2->position < p1->position) {
					a1 = new node(p2->value, p2->position);
					if (temp.head == nullptr) {
						temp.head = a1;
					}
					else {
						a1prev->next = a1;
					}
					a1prev = a1;
					p2 = p2->next;
				}
				else {
					a1 = new node(p1->value + p2->value, p2->position);
					if (p1 == head && p2 == V.head) {
						temp.head = a1;
					}
					else {
						a1prev->next = a1;
					}
					a1prev = a1;
					p1 = p1->next;
					p2 = p2->next;
				}
			}
			temp.num_nodes++;
		}
		return temp;
	}
	else {
		out << endl << "Cannot add vectors of two different sizes" << endl;
		return temp;
	}
}

int my_vector::operator*(my_vector V){
	int prod = 0;
	if (size == V.size) {
		node *v1 = head, *v2 = V.head;
		while (v1 != nullptr) {
			while (v2 != nullptr) {
				if (v1->position == v2->position) {
					prod = prod + (v1->value*v2->value);
					break;
				}
				v2 = v2->next;
			}
			v1 = v1->next;
			v2 = V.head;
		}
		return prod;
	}
	else {
		out << endl << "Cannot add vectors of two different sizes" << endl;
		return prod;
	}
}

int main() {

	my_vector V1, V2, V3;
	V1.make_random_vector(30, 8, 10);
	V1.print();
	V2.make_random_vector(30, 6, 10);
	V2.print();
	V3 = V1 + V2;
	V3.print();
	int inner_product = V1 * V2;
	out << inner_product << endl;

	out.close();
	return 0;

}