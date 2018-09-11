//Linked List insertion, sorting and removal

#include<iostream>

using namespace std;

class node
{
public:
	int value;
	node *next;
	node()
	{
		next = nullptr;
	}
	node(int k)
	{
value = k; next = nullptr;
	}
};

class  linked_list
{
public:
	int num_nodes, sorted = 0;
	node*head;
	linked_list() {
		num_nodes = 0;
		head = nullptr;
	}
	void make_random_list(int k);//create a linked list of k nodes with values in 0..99 ramdomly
	void new_make_random_list(int k, int m);
	void print();
	void reverse();
	void sort();
	void insert(int k);
	void remove_all(int k);
};

void linked_list::make_random_list(int k) {
	node *p;
	cout << "Random Linked List" << endl;
	for (int i = 0; i < k; i++)
	{
		p = new node(rand() % 100);//create random no between 0 and 99
		p->next = head;
		head = p;
		num_nodes++;
	}
}

void linked_list::print() {
	node *p = head;
	cout << endl;
	while (p != nullptr) {
		cout << p->value << " ";
		p = p->next;
	}
	cout << endl << endl;
}

void linked_list::reverse() {
	cout << "Reverse Linked List" << endl;
	if (num_nodes <= 1)return;
	node*p1 = head, *p2 = head->next, *p3;
	while (p2 != nullptr) {
		p3 = p2->next;
		p2->next = p1;
		if (p1 == head)
		{
			p1->next = nullptr;
		}
		p1 = p2;
		p2 = p3;

	}
	head = p1;
}

void linked_list::sort() {
	sorted = 1;
	cout << "Sorted Linked List" << endl;
	node *p1 = head, *p2, *p3 = nullptr;
	int temp;
	while (p1 != nullptr)
	{
		p2 = p1->next;
		temp = p1->value;
		while (p2 != nullptr) {
			if (temp > p2->value) {
				temp = p2->value;
				p3 = p2;
			}
			p2 = p2->next;
		}
		if (p3 != nullptr) {
			p3->value = p1->value;
			p1->value = temp;
		}
		p1 = p1->next;
		p3 = nullptr;
	}
}

void linked_list::remove_all(int k) {
	cout << "Linked List with " << k << " removed" << endl;
	node *p1, *p2, *p3,*p4;
	p1 = head;
	p3 = p4=p1;
	p2 = head->next;
	int temp = k;
	while (p2 != nullptr)
	{
		p2 = p1->next;
		if (temp == p1->value) {
			if (p1 == head)
			{
				head = p2;
			}
			else if (p4->next == p1) {
				p4->next = p2;
			}
			else {
				p3->next = p2;
				p4 = p3;
			}
		}
		p3 = p1;
		p1 = p1->next;
	}

}

void linked_list::insert(int k) {
	if(sorted == 1) {
		cout << "Linked List with " << k << " inserted"<<endl;
		node *p1, *p2, *p3, *p4 = nullptr;
		int temp = k, inserted = 0;
		p1 = head;
		p2 = head->next;
		p3 = new node(temp);
		while (p1 != nullptr) {
			p2 = p1->next;
			if (temp < p1->value) {
				inserted = 1;
				p3->next = p1;
				if (p1 == head)
				{
					head = p3;
				}
				else
				{
					p4->next = p3;
				}
				break;
			}
			p4 = p1;
			p1 = p1->next;
		}
		if(inserted == 0) {
			p3->next = nullptr;
			p4->next = p3;
		}
	}
	else {
		cout << "The list is not sorted so a value can't be inserted" << endl<<endl;
	}
}

void linked_list::new_make_random_list(int k, int m) {
	node * p;
	cout << "Random Linked List" << endl;
	for (int i = 0; i < k; i++) {
		p = new node(rand() % m);
		p->next = head;
		head = p;
		num_nodes++;
	}

}


int main() {

	linked_list L1;
	L1.new_make_random_list(50, 7);
	L1.print();
	L1.remove_all(1);
	L1.print();
	L1.remove_all(6);
	L1.print();

	linked_list L2;
	L2.new_make_random_list(60, 20);
	L2.print();
	L2.sort();
	L2.print();
	L2.insert(-1);
	L2.print();
	L2.insert(20);
	L2.print();
	L2.insert(15);
	L2.print();
	L2.insert(10);
	L2.print();
	getchar();
	getchar();
	return 0;
}