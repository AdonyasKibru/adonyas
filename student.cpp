#include "student.h"
#include "course.h"
#include <iostream>
#include <memory>
#include <sstream>

using namespace std;

// this function is used to print student
ostream &operator<<(ostream &out, const Student &student) {
  out << student.studentLastName << ", " << student.studentfirstName << " ("
      << student.studentID << ")";
  return out;
}

// constructor
Student::Student(const int &idNumber, const string &lastname,
                 const string &firstname)
    : studentLastName(lastname), studentfirstName(firstname),
      studentID(idNumber) {}
// this function is used to remove a student from a course
bool Student::dropCourse(int studentID, const string &courseNumber) {
  bool ans = false;
  vector<Course *> &courses = enrollmentInfo[studentID];
  for (int i = 0; i < courses.size(); i++) {
    if (courses[i]->courseID == courseNumber) {
      delete courses[i]; // Deallocate memory for the Course object
      courses.erase(courses.begin() + i);
      ans = true;
      break;
    }
  }
  return ans;
}
// this function is used to add a student to a course
bool Student::addCourse(int studentID, const string &courseNumber) {
  if (Student::isInCourse(studentID, courseNumber) ||
      ((studentID / 1000) == 0) || (courseNumber.length() != 6)) {
    return false;
  }

  enrollmentInfo[studentID].push_back(new Course(courseNumber));

  return true;
}

// Return true if student is in the given course
bool Student::isInCourse(int studentID, const string &courseNumber) const {
  const auto &enrolledCourses = enrollmentInfo.find(studentID);
  if (enrolledCourses != enrollmentInfo.end()) {
    for (const auto &course : enrolledCourses->second) {
      if (course->courseID == courseNumber) {
        return true;
      }
    }
  }
  return false;
}