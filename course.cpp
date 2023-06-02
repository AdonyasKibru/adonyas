#include "course.h"
#include "student.h"
#include <algorithm>
#include <cassert>
#include <sstream>

using namespace std;

ostream &operator<<(ostream &out, const Course &course) {
  out << course.courseID << " : " << course.courseName;
  return out;
}

Course::Course(const string &courseID, const string &courseName)
    : courseID(courseID), courseName(courseName) {}

Course::~Course() {}

void Course::addStudent(Student *student) {
  student->enrollmentInfo[student->studentID].push_back(courseID);
}

void Course::removeStudent(Student *student) {
  // Find the student in the enrollmentInfo
  auto it = student->enrollmentInfo.find(student->studentID);
  if (it != student->enrollmentInfo.end()) {
    // Remove the course from the student's enrollmentInfo
    auto &courses = it->second;
    courses.erase(std::remove(courses.begin(), courses.end(), courseID),
                  courses.end());
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
