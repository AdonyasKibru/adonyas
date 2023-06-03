#include "course.h"
#include "student.h"
#include <algorithm>
#include <cassert>
#include <sstream>

using namespace std;

ostream &operator<<(ostream &out, const Course &course) {
  out << course.courseID << " " << course.courseName;
  return out;
}

Course::Course(const string &courseID) : courseID(courseID) {}

Course::Course(const string &courseID, const string &courseName)
    : courseID(courseID), courseName(courseName) {}

Course::~Course() {}

void Course::addStudent(Student *student) {
  students[courseID].push_back(student);
}

void Course::removeStudent(Student *student) {
  for (int i = 0; i < students[courseID].size(); i++) {
    if (students[courseID][i] == student) {
      for (int j = i; j < students[courseID].size() - 1; j++) {
        students[courseID][j] = students[courseID][j + 1];
      }
      students[courseID].pop_back();
      break;
    }
  }
}

// // Return class list sorted by last name of students
// string getClassListByLastName(const string &courseNumber) const {

//   return "abc";
// }

// // Return class list sorted by id of students
// string getClassListByID(const string &courseNumber) const {}

bool Course::cmpLastName(const Student *s1, const Student *s2) {
  return (s1->studentLastName > s2->studentLastName);
}

bool Course::cmpID(const Student *s1, const Student *s2) {
  return (s1->studentID < s2->studentID);
}
