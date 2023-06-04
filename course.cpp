#include "course.h"
#include "student.h"
#include <algorithm>
#include <cassert>
#include <sstream>

using namespace std;

Course::Course(const string &courseID) : courseID(courseID) {}

Course::Course(const string &courseID, const string &courseName)
    : courseID(courseID), courseName(courseName) {}

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

bool Course::cmpLastName(const Student *stu1, const Student *stu2) {
  return (stu1->studentLastName > stu2->studentLastName);
}

bool Course::cmpID(const Student *stu1, const Student *stu2) {
  return (stu1->studentID < stu2->studentID);
}
