#include "university.h"
#include "student.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

University::University(const string &name) : universityName(name) {}

University::~University() {
  for (Student *student : uniStudents) {
    for (auto &enrollment : student->enrollmentInfo) {
      for (Course *course : enrollment.second) {
        delete course;
      }
    }
    delete student;
  }

  for (Course *course : Courses) {
    delete course;
  }
}

// Read the student list for current active university
// return true if file successfully read
bool University::readStudentList(const string &filename) {
  ifstream loadFile;
  loadFile.open(filename);

  if (!loadFile.is_open()) {
    cerr << "The file " << filename << "  can not be opend!" << endl;
    return false;
  }

  string line;
  while (getline(loadFile, line)) {
    int stuID;
    string firstName;
    string lastName;

    stringstream studentData(line);
    studentData >> stuID >> firstName >> lastName;
    uniStudents.push_back(new Student(stuID, lastName, firstName));
  }
  loadFile.close();
  return true;
}

// Read the course list for current active university
// return true if file successfully read
bool University::readCourseList(const string &filename) {
  ifstream loadFile;
  loadFile.open(filename);

  if (!loadFile.is_open()) {
    cerr << "The file " << filename << "  is not open";
    return false;
  }

  string line;

  while (getline(loadFile, line)) {
    string shortName;
    string longName = "";

    stringstream ssLine(line);
    ssLine >> shortName;
    string val;
    ssLine >> val;
    longName += val;

    while (ssLine >> val) {
      longName += " ";
      longName += val;
    }
    Courses.push_back(new Course(shortName, longName));
  }

  loadFile.close();
  return true;
}

// Read the student enrollment information for current active university
// return true if file successfully read
bool University::readEnrollmentInfo(const string &filename) {
  ifstream loadFile;
  loadFile.open(filename);

  if (!loadFile.is_open()) {
    cerr << "This file " << filename << " is not opened." << endl;
    return false;
  }

  string line;
  while (getline(loadFile, line)) {
    int id;
    string shortName;

    stringstream ss(line);
    ss >> id >> shortName;

    for (Student *value : uniStudents) {
      value->addCourse(id, shortName);
    }
  }

  loadFile.close();
  return true;
}

// Drop student from given course, return true if successful
bool University::dropCourse(int studentID, const string &courseNumber) {
  for (Student *student : uniStudents) {
    if (student->dropCourse(studentID, courseNumber))
      return true;
  }
  return false;
}

bool University::addCourse(int studentID, const string &courseNumber) {
  bool ans = false;
  for (Student *student : uniStudents) {
    if (student->addCourse(studentID, courseNumber)) {
      ans = true;
    }
  }
  return ans;
}

// Return true if student is in the given course
bool University::isInCourse(int studentID, const string &courseNumber) const {
  for (const Student *student : uniStudents) {
    if (student->studentID == studentID) {
      return student->isInCourse(studentID, courseNumber);
    }
  }
  return false;
}

// Return the courses student is enrolled in
// The returned courses are separated by commas and sorted by course name
string University::getEnrolledCourses(int studentID) const {
  string ans = "[";
  Student *value = uniStudents[0];
  ans = ans + value->enrollmentInfo[studentID][0]->courseID;
  for (int i = 1; i < value->enrollmentInfo[studentID].size(); i++) {
    ans += ", ";
    ans += value->enrollmentInfo[studentID][i]->courseID;
  }
  ans += "]";
  return ans;
}

// vector<Student *> University::getClassListByLastName() {
//   // sort(students.begin(), students.end(), cmpLastName);
//   return students;
// }

// vector<Student *> University::getClassListByID() {
//   // sort(students.begin(), students.end(), cmpID);
//   return students;
// }

bool University::cmpLastName(const Student *stu1, const Student *stu2) {
  return (stu1->studentLastName > stu2->studentLastName);
}

bool University::cmpID(const Student *stu1, const Student *stu2) {
  return (stu1->studentID > stu2->studentID);
}

// Return the title for the course
string University::getCourseTitle(const string &courseNumber) {
  string answer;
  for (Course *val : Courses) {
    if (val->courseID == courseNumber) {
      answer = val->courseName;
    }
  }
  return answer;
}