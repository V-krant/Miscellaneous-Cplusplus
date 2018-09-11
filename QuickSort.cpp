//Multi-threaded Quicksort

#include <iostream>
#include <vector>
#include<thread>
#include <fstream>
using namespace std;

//The following funciton will be the work for each thread
void quick_sort(vector<int> &V, int i, int j) {
	if (i >= j)
		return;
	vector<int> W(j-i+1);
	int temp = V[i], n1 = 0, n2 = W.size() - 1;
	for (int n = i+1; n <= j; n++) {
		if (temp > V[n]) {
			W[n1] = V[n];
			n1++;
		}
		else {
			W[n2] = V[n];
			n2--;
		}
	}
	if(W.size()!=0)
	W[n1] = temp;
	int k = 0;
	for (int n = i; n <= j; n++) {
		V[n] = W[k];
		k++;
	}
	quick_sort(V, i, n1 + i - 1);
	quick_sort(V, n1 + i+ 1, j);
	
}

void initialize_threads(vector<int> &V, int i, int j, int iteration,vector<int> &division) {
	if (iteration == 2) {
		division.push_back(j);
		return;
	}
	vector<int> W(j - i + 1);
	int temp = V[i], n1 = 0, n2 = W.size() - 1;
	for (int n = i + 1; n <= j; n++) {
		if (temp > V[n]) {
			W[n1] = V[n];
			n1++;
		}
		else {
			W[n2] = V[n];
			n2--;
		}
	}
	if (W.size() != 0)
		W[n1] = temp;
	int k = 0;
	for (int n = i; n <= j; n++) {
		V[n] = W[k];
		k++;
	}
	initialize_threads(V, i, n1 + i - 1,iteration+1,division);
	initialize_threads(V, n1 + i + 1, j,iteration+1,division);
}

int main() {
	ofstream out("output.txt");
	int n = 100000;
	vector<int> V(n);//V has n elements.
	for (int i = 0; i < 100000; i++) V[i] = rand() % 5000;
	vector<int> division;
	initialize_threads(V, 0, n - 1, 0,division);
	thread t[4];
	int start = 0;
	for (int i = 0; i < 4; i++) {
		t[i]=thread(quick_sort,ref(V), start, division[i]);
		start = division[i] + 2;
	}
	for (int i = 0; i < 4; i++)
		t[i].join();
	for (int i = 0; i < n; i++)
		out << V[i] << " ";
	out.close();
}

