#include "course.h"
#include "student.h"
#include <algorithm>
#include <cassert>
#include <sstream>

using namespace std;

//ostream &operator<<(ostream &out, const Course &course) { return out; }

// Course::Course(const string &courseID, const string &courseName):
// courseID(courseID), courseName(courseName){} Course::~Course(){

// }
//   void Course::addStudent(Student *student){
//     students[student.studentID] = student
//   }
//   void Course::removeStudent(Student *student){

//   }
//   vector<Student *> Course::getClassListByLastName(){}
//   vector<Student *> Course::getClassListByID(){}
//   bool Course::cmpLastName(const Student *s1, const Student *s2){}
//   bool Course::cmpID(const Student *s1, const Student *s2){}