//Multithreading using unique_lock and mutex

#include <iostream>           
#include <thread>             
#include <mutex>              
#include <condition_variable> 
#include <time.h>

std::mutex mtx;
std::condition_variable cv1;
std::condition_variable cv2;
int seed = 100;

class Parts {
public:
	int partA;
	int partB;
	int partC;
	Parts() {
		partA = 0;
		partB = 0;
		partC = 0;
	}
};

Parts partsBuffer;

void partEnqBuffer(Parts &P, int id) {
	std::unique_lock<std::mutex> lck(mtx);

	while (P.partA != 0 || P.partB != 0 || P.partC != 0) {
		int a = P.partA, b = P.partB, c = P.partC;
	std::cout << std::endl << "PartWorker ID: " << id << std::endl;
	std::cout << "Buffer State: (" << partsBuffer.partA << "," << partsBuffer.partB << "," << partsBuffer.partC << ")" << std::endl;
	std::cout << "Place Request: (" << P.partA << "," << P.partB << "," << P.partC << ")" << std::endl;
	
		while (partsBuffer.partA != 6 && P.partA != 0) {
			partsBuffer.partA++;
			P.partA--;
		}
		while (partsBuffer.partB != 5 && P.partB != 0) {
			partsBuffer.partB++;
			P.partB--;
		}
		while (partsBuffer.partC != 4 && P.partC != 0) {
			partsBuffer.partC++;
			P.partC--;
		}
		std::cout << "Updated Buffer State: (" << partsBuffer.partA << "," << partsBuffer.partB << "," << partsBuffer.partC << ")" << std::endl;
		std::cout << "Updated Place Request: (" << P.partA << "," << P.partB << "," << P.partC << ")" << std::endl;
		if(P.partA!=a || P.partB!=b || P.partC!=c)
		cv2.notify_one();
		if(P.partA != 0 || P.partB != 0 || P.partC != 0)
		cv1.wait(lck);
	}
	if (partsBuffer.partA != 6 || partsBuffer.partB !=5 || partsBuffer.partC != 4)
		cv1.notify_one();
}
	

void partDeqBuffer(Parts &P, int id) {
	std::unique_lock<std::mutex> lck(mtx);

	int a1, b1, c1,a2,b2,c2;
	while (P.partA != 0 || P.partB != 0 || P.partC != 0) {
		a1 = P.partA; b1 = P.partB; c1 = P.partC;
		a2 = partsBuffer.partA; b2 = partsBuffer.partB; c2 = partsBuffer.partC;
	std::cout << std::endl << "ProductWorker ID: " << id << std::endl;
	std::cout << "Buffer State: (" << partsBuffer.partA << "," << partsBuffer.partB << "," << partsBuffer.partC << ")" << std::endl;
	std::cout << "Pickup Request: (" << P.partA << "," << P.partB << "," << P.partC << ")" << std::endl;
	
	while (partsBuffer.partA != 0 && P.partA != 0) {
		partsBuffer.partA--;
		P.partA--;
	}
	while (partsBuffer.partB != 0 && P.partB != 0) {
		partsBuffer.partB--;
		P.partB--;
	}
	while (partsBuffer.partC != 0 && P.partC != 0) {
		partsBuffer.partC--;
		P.partC--;
	}
	std::cout << "Updated Buffer State: (" << partsBuffer.partA << "," << partsBuffer.partB << "," << partsBuffer.partC << ")" << std::endl;
	std::cout << "Updated Pickup Request: (" << P.partA << "," << P.partB << "," << P.partC << ")" << std::endl;
	if (P.partA != a1 || P.partB != b1 || P.partC != c1)
	cv1.notify_one();
	if(P.partA != 0 || P.partB != 0 || P.partC != 0)
		cv2.wait(lck);
	}
	if (partsBuffer.partA != 0 || partsBuffer.partB != 0 || partsBuffer.partC != 0)
		cv2.notify_one();
}


void startPartWorker(int id) {
	int i = 7;
	while (i > 0) {
		srand(seed++);
		int a, b, c;
		int pair = rand() % 3;
		switch (pair) {
		case 0: {
			a = rand() % 4;
			b = rand() % (4 - a);
			c = 3 - a - b;
			break;
		}
		case 1: {
			b = rand() % 4;
			c = rand() % (4 - b);
			a = 3 - b - c;
			break;
		}
		case 2: {
			c = rand() % 4;
			a = rand() % (4 - c);
			b = 3 - c - a;
			break;
		}
		}
		Parts p;
		p.partA = a;
		p.partB = b;
		p.partC = c;
		partEnqBuffer(p, id);

		i--;
	}	
}
	
	
void startProductWorker(int id) {
	int i = 7;
	while (i > 0) {
		srand (++seed);
		int a, b, c;
		int pair = rand() % 3;
		switch (pair) {
		case 0: {
			a = (rand() % 3) + 1;
			b = 4 - a;
			c = 0;
			break;
		}
		case 1: {
			a = 0;
			b = (rand() % 3) + 1;
			c = 4 - b;
			break;
		}
		case 2: {
			b = 0;
			c = (rand() % 3) + 1;
			a = 4 - c;
			break;
		}
		}
		Parts p;
		p.partA = a;
		p.partB = b;
		p.partC = c;
		partDeqBuffer(p, id);

		i--;
	}
}

int main() {
	std::thread partWorker[10];
	std::thread productWorker[7];
	for (int id = 0; id < 7; id++) {
		partWorker[id] = std::thread(startPartWorker, id);
		productWorker[id] = std::thread(startProductWorker, id);
	}
	for (int id = 7; id<10; id++) {
		partWorker[id] = std::thread(startPartWorker, id);
	}
	for (int id = 0; id < 7; id++) {
		partWorker[id].join();
		productWorker[id].join();
	}
	for (int id = 7; id < 10; id++)
		partWorker[id].join();
	std::cout << "Finish!" << std::endl;
	getchar();
	return 0;
}