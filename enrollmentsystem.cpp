#include "enrollmentsystem.h"
#include "university.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

// Add university to the enrollments system
bool EnrollmentSystem::addUniversity(const string &name) {
  if (universities[name] != nullptr) {
    return false;
  } else {
    universities[name] = new University(name);
    return true;
  }
}

// Set this university as the active university for other functions
bool EnrollmentSystem::setCurrentUniversity(const string &name) {
  if (universities[name] == nullptr) {
    return false;
  } else {
    *currentUniversity = University(name);
    return true;
  }
}

// Return the current active university name
string EnrollmentSystem::getUniversityName() const {
  return currentUniversity->universityName;
}

// Read the student list for current active university
// return true if file successfully read
bool EnrollmentSystem::readStudentList(const string &filename) {
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

    students[id].push_back(firstName);
    students[id].push_back(lastName);
  }

  loadFile.close();
  return true;
}

// Read the course list for current active university
// return true if file successfully read
bool EnrollmentSystem::readCourseList(const string &filename) {
  ifstream loadFile;
  loadFile.open(filename);

  if (!loadFile.is_open()) {
    cerr << "The file " << filename << "  is not open";
    return false;
  }

  string line;
  while (getline(loadFile, line)) {
    string shortName;
    string longName;

    stringstream ss(line);
    ss >> shortName >> longName;

    courseList[shortName] = longName;
  }
  loadFile.close();
  return true;
}

// Read the student enrollment information for current active university
// return true if file successfully read
bool EnrollmentSystem::readEnrollmentInfo(const string &filename) {
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
bool EnrollmentSystem::dropCourse(int studentID, const string &courseNumber) {
  for (int i = 0; i < enrollmentInfo[studentID].size(); i++) {
    if (enrollmentInfo[studentID][i] == courseNumber) {
      for (int j = i; j < enrollmentInfo[studentID].size() - 1; j++) {
        enrollmentInfo[studentID][j] = enrollmentInfo[studentID][j + 1];
      }
      enrollmentInfo[studentID].pop_back();
      return true;
    }
  }
  return false;
}

// Add student to the given course, return true if successful
bool EnrollmentSystem::addCourse(int studentID, const string &courseNumber) {
  enrollmentInfo[studentID].push_back(courseNumber);
  return true;
}

// Return true if student is in the given course
bool EnrollmentSystem::isInCourse(int studentID, const string &courseNumber) {
  for (int i = 0; i < enrollmentInfo[studentID].size(); i++) {
    if (enrollmentInfo[studentID][i] == courseNumber) {
      return true;
    }
  }
  return false;
}

// Return the courses student is enrolled in
// The returned courses are separated by commas and sorted by course name
string EnrollmentSystem::getEnrolledCourses(int studentID) {
  string ans = enrollmentInfo[studentID][0];
  for (int i = 1; i < enrollmentInfo[studentID].size(); i++) {
    sort(enrollmentInfo[studentID].begin(), enrollmentInfo[studentID].end());
    ans += ", ";
    ans += enrollmentInfo[studentID][i];
  }
  return ans;
}

// Return the title for the course
string EnrollmentSystem::getCourseTitle(const string &courseNumber) {
  return courseList[courseNumber];
}

// // Return class list sorted by last name of students
// string
// EnrollmentSystem::getClassListByLastName(const string &courseNumber) const {}

// // Return class list sorted by id of students
// string EnrollmentSystem::getClassListByID(const string &courseNumber) const
// {}
