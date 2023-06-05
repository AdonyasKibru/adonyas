#include "course.h"
#include "student.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

Course::Course(const string &courseID) : courseID(courseID) {}

Course::Course(const string &courseID, const string &courseName)
    : courseID(courseID), courseName(courseName) {}

void Course::addStudent(Student *student) {
  Student *answer = students[courseID][0];
  answer->addCourse(student->studentID, courseID);
}

void Course::removeStudent(Student *student) {
  Student *answer = students[courseID][0];
  answer->dropCourse(student->studentID, courseID);
}

string Course::getClassListByLastName(const string &courseNumber) {
  string ans = "1";
  vector<Student *> value;

  // for (Student *stu : students) {
  //   if (stu->isInCourse(stu->studentID, courseNumber)) {
  //     value.push_back(stu);
  //     ans = "here";
  //   }
  // }

  sort(value.begin(), value.end(), cmpLastName);
  // ans = students[courseNumber][0]->studentLastName;
  //  ans += ", ";
  //  ans += students[courseNumber][0]->studentfirstName;
  //  ans += " (";
  //  ans += students[courseNumber][0]->studentID;
  //  ans += ")";

  // for (int i = 1; i < students[courseNumber].size(); i++) {
  //   ans += ", ";
  //   ans += students[courseNumber][i]->studentLastName;
  //   ans += ", ";
  //   ans += students[courseNumber][i]->studentfirstName;
  //   ans += " (";
  //   ans += students[courseNumber][i]->studentID;
  //   ans += ")";
  // }
  // ans += "]";
  return ans;
}

// Return class list sorted by id of students
string Course::getClassListByID(const string &courseNumber) const {
  return courseNumber;
}

bool Course::cmpLastName(const Student *stu1, const Student *stu2) {
  return stu1->studentLastName > stu2->studentLastName;
}

bool Course::cmpID(const Student *stu1, const Student *stu2) {
  return (stu1->studentID < stu2->studentID);
}
