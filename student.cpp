#include "student.h"
#include "course.h"

#include <sstream>

using namespace std;

ostream &operator<<(ostream &out, const Student &student) {
  out << student.studentLastName << ", " << student.studentfirstName << " ("
      << student.studentID << ")";
  return out;
}

Student::Student(const int &idNumber, const string &lastname,
                 const string &firstname)
    : studentLastName(lastname), studentfirstName(firstname),
      studentID(idNumber) {}

// Drop student from given course, return true if successful
bool Student::dropCourse(int studentID, const string &courseNumber) {
  if (enrollmentInfo.find(studentID) != enrollmentInfo.end()) {
    vector<Course *> &courses = enrollmentInfo[studentID];

    for (auto it = courses.begin(); it != courses.end(); ++it) {
      if ((*it)->courseID == courseNumber) {
        delete *it;
        courses.erase(it);
        return true;
      }
    }
  }

  return false;
}

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