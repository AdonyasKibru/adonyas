#include "university.h"
#include "student.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

University::University(const string &name) : universityName(name) {}

University::~University() {}

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
    int id;
    string firstName;
    string lastName;

    stringstream studentData(line);
    studentData >> id >> firstName >> lastName;

    students.push_back(new Student(id, lastName, firstName));
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

    stringstream ss(line);
    ss >> shortName;
    string val;
    ss >> val;
    longName += val;
    while (ss >> val) {
      longName += " ";
      longName += val;
    }

    courses[shortName] = new Course(shortName, longName);
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

    enrollmentInfo[id].push_back(shortName);
  }

  loadFile.close();
  return true;
}

// Drop student from given course, return true if successful
bool University::dropCourse(int studentID, const string &courseNumber) {
  auto &enrolledCourses = enrollmentInfo[studentID];
  auto it = find(enrolledCourses.begin(), enrolledCourses.end(), courseNumber);
  if (it != enrolledCourses.end()) {
    enrolledCourses.erase(it);
    return true;
  }
  return false;
}

bool University::addCourse(int studentID, const string &courseNumber) {
  if (University::isInCourse(studentID, courseNumber) ||
      ((studentID / 1000) == 0) || (courseNumber.length() != 6)) {
    return false;
  }
  enrollmentInfo[studentID].push_back(courseNumber);
  return true;
}

// Return true if student is in the given course
bool University::isInCourse(int studentID, const string &courseNumber) const {
  const auto &enrolledCourses = enrollmentInfo.find(studentID);
  if (enrolledCourses != enrollmentInfo.end()) {
    for (const string &course : enrolledCourses->second) {
      if (course == courseNumber) {
        return true;
      }
    }
  }
  return false;
}

// Return the courses student is enrolled in
// The returned courses are separated by commas and sorted by course name
string University::getEnrolledCourses(int studentID) const {
  if (enrollmentInfo.find(studentID) == enrollmentInfo.end()) {
    return "[]";
  }
  vector<string> enrolledCourses = enrollmentInfo.at(studentID);
  sort(enrolledCourses.begin(), enrolledCourses.end());

  string ans = "[";
  ans += enrolledCourses[0];
  for (int i = 1; i < enrolledCourses.size(); i++) {
    ans += ", ";
    ans += enrolledCourses[i];
  }
  ans += "]";
  return ans;
}

vector<Student *> University::getClassListByLastName() {
  // sort(students.begin(), students.end(), cmpLastName);
  return students;
}

vector<Student *> University::getClassListByID() {
  // sort(students.begin(), students.end(), cmpID);
  return students;
}

bool University::cmpLastName(const Student *s1, const Student *s2) {
  return (s1->studentLastName > s2->studentLastName);
}

bool University::cmpID(const Student *s1, const Student *s2) {
  return (s1->studentID > s2->studentID);
}

// Return the title for the course
string University::getCourseTitle(const string &courseNumber) {
  return courses[courseNumber]->courseName;
}