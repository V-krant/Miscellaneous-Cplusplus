//Template Programming

#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;


template <class T> class ThreeD {
public:
	T ht;
	T wid;
	T dep;
	ThreeD() { ht = wid = dep = 0; }
	ThreeD(T i) { ht = wid = dep = i; }
	ThreeD(T a, T b, T c) { ht = a; wid = b; dep = c; }

	template <class T> friend	ostream & operator<<(ostream &s, const ThreeD<T> &t);
};


template <class T> class node {
public:
	T value;
	node<T> * next;
	node<T>() { next = nullptr; }
	node<T>(T v) { value = v; next = nullptr; }
};

template <class T> class linked_list {
public:
	int num_nodes, sorted = 0;
	node<T> * head;
	linked_list() {
		num_nodes = 0;
		head = nullptr;
	}

	linked_list(const linked_list<T> &L) {
		num_nodes = L.num_nodes;
		head = nullptr;
		for (int i = 0; i < num_nodes; i++) {
			node<T> * p = new node<T>();
			p->next = head;
			head = p;
		}
		node<T> * p1 = head;
		node<T> * p2 = L.head;
		while (p2 != nullptr) {
			p1->value = p2->value;
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	linked_list(linked_list<T> &&L) {
		num_nodes = L.num_nodes;
		head = L.head;
		L.head = nullptr;
	}

	void operator=(linked_list<T> &L) {
		num_nodes = L.num_nodes;
		head = nullptr;
		for (int i = 0; i < num_nodes; i++) {
			node<T> * p = new node<T>();
			p->next = head;
			head = p;
		}
		node<T> * p1 = head;
		node<T> * p2 = L.head;
		while (p2 != nullptr) {
			p1->value = p2->value;
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	void operator=(linked_list<T> &&L) {
		num_nodes = L.num_nodes;
		head = L.head;
		L.head = nullptr;
	}

	~linked_list() {
		node<T> * p1;
		while (head != nullptr) {
			p1 = head->next;
			delete head;
			head = p1;
		}
	}

	void push_back(T v) {
		node<T> * nnb = new node<T>(v);
		num_nodes++;
		if (head == nullptr) {
			head = nnb;
		}
		else {
			node<T> * temp1, *temp2;
			temp1 = head;
			while (temp1 != nullptr) {
				temp2 = temp1;
				temp1 = temp1->next;
			}
			temp2->next = nnb;
		}
	}

	void push_front(T v) {
		node<T> * nnf = new node<T>(v);
		num_nodes++;
		if (head == nullptr) {
			head = nnf;
		}
		else {
			nnf->next = head;
			head = nnf;
		}
	}

	void pop_back() {
		if (num_nodes == 0) {
			return;
		}
		node<T> * temp1;
		temp1 = head;
		for (size_t i = 0; i < num_nodes - 2; i++) {
			temp1 = temp1->next;
		}
		temp1->next = nullptr;
		num_nodes--;
	}

	void pop_front() {
		if (num_nodes == 0) {
			return;
		}
		head = head->next;
		num_nodes--;
	}
};

template <class X>
class item {
public:
	X value;
	item<X> *next;
	item<X> *previous;
	item(X v) { value = v; next = nullptr; previous = nullptr; }
};

template <class X>
class bag {
public:
	item<X> *last;
	item<X> *first;
	int num_items;
	int size() { return num_items; }
	void show_bag();//Print all items in the bag
	bag() { last = nullptr; first = nullptr; num_items = 0; } //default constructor for bag class
	
	bag(const bag<X> &B) {
		num_items = B.num_items;
		first = nullptr;
		last = nullptr;
		for (int i = 0; i < num_items; i++) {
			item<X> * n = new item<X>();
			n->next = first;
			first = n;
		}
		for (int j = 0; j < num_items; j++) {
			n->previous = last;
			last = n;
			n = n->next;
		}
		item<X> * i1 = first;
		item<X> * i2 = B.first;
		while (i2 != nullptr) {
			i1->value = i2->value;
			i1 = i1->next;
			i2 = i2->next;
		}
	}

	bag(bag<X> &&B) {
		num_items = B.num_items;
		first = B.first;
		B.first = nullptr;
		last = B.last;
		B.last = nullptr;
	}

	void operator=(bag<X> &B) {
		num_items = B.num_items;
		first = nullptr;
		for (int i = 0; i < num_items; i++) {
			item<X> * n = new item<X>();
			n->next = first;
			first = n;
		}
		for (int j = 0; j < num_items; j++) {
			n->previous = last;
			last = n;
			n = n->next;
		}
		item<X> * i1 = first;
		item<X> * i2 = B.first;
		while (i2 != nullptr) {
			i1->value = i2->value;
			i1 = i1->next;
			i2 = i2->next;
		}
	}

	void operator=(bag<X> &&B) {
		num_items = B.num_items;
		first = B.first;
		B.first = nullptr;
		last = B.last;
		B.last = nullptr;
	}

	~bag() {
		item<X> * i1;
		while (first != nullptr) {
			i1 = first->next;
			delete first;
			first = i1;
		}
		last = nullptr;
	}

	void push_back(X v);  //insert an item with value v to the back of the bag
	void push_front(X v); //insert an item with value v to the front of the bag
	void pop_back(); //delete the last item in the bag
	void pop_front(); //delete the first item in the bag
	X &operator[](int i); //Access bag item with index. 
	X front() {  //it returns the value of the first item in the bag.
				 //In real applicaitons, we need to check if the bag is empty.  We are skipping this here.
		return first->value;
	}
	X back() { //it returns the value of the last item in the bag
			   //In real applicaitons, we need to check if the bag is empty.  We are skipping this here.
		return last->value;
	}
	void clear(); //Delete all items in the bag
};

template<class X> void bag<X>::push_front(X v) {
	item<X> *nf = new item<X>(v);
	num_items++;
	if (first == nullptr) {
		first = nf;
		last = nf;
	}
	else {
		nf->next = first;
		first->previous = nf;
		first = nf;
	}
}

template<class X> void bag<X>::push_back(X v) {
	item<X> *nb = new item<X>(v);
	num_items++;
	if (first == nullptr) {
		first = nb;
		last = nb;
	}
	else {
		last->next = nb;
		nb->previous = last;
		last = nb;
	}
}

template<class X> void bag<X>::pop_back() {
	if (num_items == 0) {
		return;
	}
	last = last->previous;
	last->next=nullptr;
	num_items--;
}

template<class X> void bag<X>::pop_front() {
	if (num_items == 0) {
		return;
	}
	first = first->next;
	first->previous = nullptr;
	num_items--;
}

template<class X> void bag<X>::show_bag() {
	item<X> *pt1 = first;
	while (pt1 != nullptr) {
		cout << pt1->value<<" ";
		pt1 = pt1->next;
	}
}

template<class X> X& bag<X>::operator[](int i) {
	item<X> *temp = first;
	for (size_t j = 0; j < i; j++) {
		temp = temp->next;
	}
	return temp->value;
}

template<class X> void bag<X>::clear() {
	item<X> *ci;
	while (first != nullptr) {
		ci = first->next;
		delete first;
		first = ci;
	}
	last = nullptr;
	num_items = 0;
}

template <class T> ostream & operator<<(ostream &s, const ThreeD<T> &t) {//ostream & operator<<(ostream &s, ThreeD t) will also work.
	s << "( " << t.ht << ", " << t.wid << ", " << t.dep << " )";
	return s;
}

template <class T> ostream & operator<<(ostream &s, const linked_list<T> &L) {
	node<T> * li = L.head;
	while (li != nullptr) {
		s << li->value << " ";
		li = li->next;
	}
	return s;
}

int main() {
	bag<double> bag_d;
	bag_d.push_back(5.5);
	bag_d.push_back(6.6);
	bag_d.push_front(4.4);
	bag_d.push_front(3.3);
	bag_d.pop_front();
	bag_d.pop_back();
	bag_d.show_bag();
	cout << endl;


	bag<int> bag_i;
	bag_i.push_back(5);
	bag_i.push_back(6);
	bag_i.push_front(4);
	bag_i.push_front(3);
	bag_i.pop_front();
	bag_i.pop_back();
	bag_i.show_bag();

	ThreeD<int> td3(3), td4(4), td5(5), td6(6), td7(100, 200, 300);
	bag<ThreeD<int>> bag_3D;
	bag_3D.push_back(td5);
	bag_3D.push_back(td6);
	bag_3D.push_front(td4);
	bag_3D.push_front(td3);
	bag_3D.pop_front();
	bag_3D.pop_back();
	bag_3D.show_bag();
	cout << "\nfront = " << bag_3D.front() << "  back = " << bag_3D.back();
	cout << "\n" << bag_3D[0] << " " << bag_3D[1] << "\n";
	bag_3D[1] = td7;
	cout << "\n" << bag_3D[0] << " " << bag_3D[1] << "\n";
	bag_3D.clear();
	bag_3D.show_bag();
	cout << "\nsize = " << bag_3D.size();


	linked_list<string>ls_1;
	ls_1.push_front("David");
	ls_1.push_front("John");
	ls_1.push_front("Pat");
	ls_1.push_front("Ben");
	ls_1.push_front("Jeff");
	cout << endl;
	cout << ls_1 << endl;

	linked_list<string>ls_2;
	ls_2.push_front("Wendy");
	ls_2.push_front("Mary");
	ls_2.push_front("Nancy");
	ls_2.push_front("Jennifer");
	cout << endl;
	cout << ls_2 << endl;

	bag<linked_list<string>> bag_string;
	bag_string.push_back(ls_1);
	bag_string.push_back(ls_2);
	bag_string.show_bag();
	cout << endl;
	cout << bag_string[1];

	ThreeD<double> t10(3.2, 7.4, 8.9), t11(5.6, 7.7, 2.987), t12(4.6, 7.5, 3.1416), t13(55.6, 66.8, 333.45);
	linked_list<ThreeD<double>> LTD1;
	LTD1.push_front(t10);
	LTD1.push_front(t11);
	linked_list<ThreeD<double>> LTD2;
	LTD2.push_front(t13);
	LTD2.push_front(t12);
	LTD2.push_front(t10);
	LTD2.push_front(t11);

	bag<linked_list<ThreeD<double> > > BLTD;
	BLTD.push_back(LTD1);
	BLTD.push_back(LTD2);
	cout << endl;
	BLTD.show_bag();

	getchar();
	getchar();
}