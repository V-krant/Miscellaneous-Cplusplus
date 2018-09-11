//Database operations on a Nested Map  

#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

class course {
public:
	string name;
	int section;
	int credits;
	course() {}
	course(string n, int s, int c) { name = n; section = s; credits = c; }
	bool operator<(course c) { return (name < c.name); }
	bool operator==(course c) { return (name == c.name); }
};

void add_student(map<int, map<int, list<course> * >> &DB, int id);
void remove_student(map<int, map<int, list<course> * >> &DB, int id);
void add_course(map<int, map<int, list<course> * >> &DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
																						  //All courses in the list should be sorted according to name (increasing order)
void drop_course(map<int, map<int, list<course> * >> &DB, int semester, int id, course c);
void print_student_semester_courses(map<int, map<int, list<course> * >> &DB, int semester, int id);
void print_student_all_courses(map<int, map<int, list<course> * >> &DB, int id);
void print_DB(map<int, map<int, list<course> * >> &DB);

int main() {
	map<int, map<int, list<course> *>> DB;
	add_student(DB, 11111);
	course C1("CIS554", 1, 3), C2("CSE674", 1, 3), C3("MAT296", 8, 4), C4("WRT205", 5, 3);

	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	print_student_semester_courses(DB, 20171, 11111);

	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111);

	add_course(DB, 20172, 11111, C2);
	add_course(DB, 20172, 11111, C4);
	add_course(DB, 20172, 11111, C3);
	add_course(DB, 20172, 11111, C1);
	print_student_all_courses(DB, 11111);

	add_student(DB, 11112);
	add_course(DB, 20171, 11112, C2);
	add_course(DB, 20171, 11112, C4);
	add_course(DB, 20171, 11112, C3);
	add_course(DB, 20171, 11112, C1);
	print_student_semester_courses(DB, 20171, 11112);

	add_course(DB, 20172, 11112, C2);
	add_course(DB, 20172, 11112, C4);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C1);
	print_student_semester_courses(DB, 20172, 11112);

	print_student_all_courses(DB, 11112);

	print_DB(DB);
	remove_student(DB, 11111);
	print_DB(DB);
	getchar();
	getchar();
	return 0;
}

void add_student(map<int, map<int, list<course> * >> &DB, int id) {	
	if (DB.find(id) != DB.end()) return;
	map<int, list<course> *> M1;
	DB[id] = M1;
}
void remove_student(map<int, map<int, list<course> * >> &DB, int id) {
	if (DB.find(id) != DB.end()) {
		DB.erase(id);
	}
}


void add_course(map<int, map<int, list<course> * >> &DB, int semester, int id, course c) {
	if (DB.find(id) != DB.end()) {
		if (DB[id][semester] != nullptr) {
			list<course>*cor = DB[id][semester];
			cor->push_back(c);
			cor->sort();
			DB[id][semester] = cor;
		}
		else {
			list<course>*cor = new list<course>;
			cor->push_back(c);
			cor->sort();
			DB[id][semester] = cor;
		}
	}
}

void drop_course(map<int, map<int, list<course> * >> &DB, int semester, int id, course c) {
	if (DB.find(id) != DB.end()) {
		if (DB[id][semester] != nullptr) {
			list<course>*cor = DB[id][semester];
			cor->remove(c);
			cor->sort();
			DB[id][semester] = cor;
		}
	}
}

void print_student_semester_courses(map<int, map<int, list<course> * >> &DB, int semester, int id) {
	if (DB.find(id) != DB.end()) {
		if (DB[id][semester] != nullptr) {
			cout << endl << "student id = " << id << endl;
			map < int, list<course>*>::iterator c1 = DB[id].find(semester);
			cout << "semester = " << c1->first << endl;
			while (c1 == DB[id].find(semester)) {
				list<course>::iterator c2 = c1->second->begin();
				while (c2 != c1->second->end()) {
					cout << c2->name << " " << c2->section << " " << c2->credits << " ";
					c2++;
				}
				c1++;
				cout << endl;
			}
		}
	}	
}

void print_student_all_courses(map<int, map<int, list<course> * >> &DB, int id) {
	if (DB.find(id) != DB.end()) {		
			cout << endl << "student id = " << id << endl;
			map<int, map < int, list<course>*>>::iterator b1 = DB.find(id);
			while (b1 == DB.find(id)) {
				map < int, list<course>*>::iterator b2 = (b1->second).begin();
				if (b1->second.begin() != (b1->second).end()) {
					while (b2 != (b1->second).end()) {
						if (b2->second != nullptr) {
							list<course>::iterator b3 = b2->second->begin();
							cout << "semester = " << b2->first << endl;
							while (b3 != b2->second->end()) {
								cout << b3->name << " " << b3->section << " " << b3->credits << " ";
								b3++;
							}
							
							cout << endl;
						}
						b2++;
					}
						b1++;
					
			}
		}
	}
}

void print_DB(map<int, map<int, list<course> * >> &DB) {
	if (DB.begin() != DB.end()) {
		map<int, map<int, list<course> * >>::iterator lt = DB.begin();
		while (lt != DB.end()) {
			cout << endl << "student id = " << lt->first;
			if (lt->second.begin() != (lt->second).end()) {
				map < int, list<course>*>::iterator lt1 = (lt->second).begin();
				while (lt1 != (lt->second).end()) {
					cout << endl << "semester = " << lt1->first << endl;
					if (lt1->second != nullptr) {
						list<course>::iterator lt2 = lt1->second->begin();
						while (lt2 != lt1->second->end()) {
							cout << lt2->name << " " << lt2->section << " " << lt2->credits << " ";
							lt2++;
						}
					}
					lt1++;
				}
				lt++;
			}
		}
		cout << endl;
	}
}
