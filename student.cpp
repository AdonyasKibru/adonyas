#include "student.h"
#include "course.h"

#include <sstream>

using namespace std;

//ostream &operator<<(ostream &out, const Student &student) { return out; }

Student::Student(const int &idNumber, const string &name)
    : studentName(name), studentID(idNumber) {}
// Student::~Student(){}
//   bool Student::dropCourse(int studentID, const string &courseNumber){}
//   bool Student::addCourse(int studentID, const string &courseNumber){}
//   bool Student::isInCourse(int studentID, const string &courseNumber) const{}