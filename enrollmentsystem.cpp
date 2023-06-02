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
    currentUniversity = universities[name];
    return true;
  }
}

// Return the current active university name
string EnrollmentSystem::getUniversityName() const {
  return currentUniversity->universityName;
}

// Return the courses student is enrolled in
// The returned courses are separated by commas and sorted by course name
string EnrollmentSystem::getEnrolledCourses(int studentID) {
  string ans = "[";
  const auto &enrolledCourses = enrollmentInfo[studentID];
  if (!enrolledCourses.empty()) {
    ans += enrolledCourses[0];
    for (int i = 1; i < enrolledCourses.size(); i++) {
      ans += ", ";
      ans += enrolledCourses[i];
    }
  }
  ans += "]";
  return ans;
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

    students.push_back(new Student(id, lastName, firstName));
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

bool EnrollmentSystem::addCourse(int studentID, const string &courseNumber) {
  if (EnrollmentSystem::isInCourse(studentID, courseNumber) ||
      ((studentID / 1000) == 0) || (courseNumber.length() != 6)) {
    return false;
  }
  enrollmentInfo[studentID].push_back(courseNumber);
  return true;
}

// Return true if student is in the given course
bool EnrollmentSystem::isInCourse(int studentID,
                                  const string &courseNumber) const {
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
string EnrollmentSystem::getEnrolledCourses(int studentID) const {
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

// string
// EnrollmentSystem::getClassListByLastName(const string &courseNumber) const {
//   vector<Student *> classList = courses[courseNumber]->getClassListByLastName();
//   sort(classList.begin(), classList.end(), cmpLastName);
//   // Format the class list into a string separated by commas
//   string result;
//   for (const auto student : classList) {
//     result += student->getFullName() + ", ";
//   }
//   // Remove the trailing comma and space
//   if (!result.empty()) {
//     result = result.substr(0, result.length() - 2);
//   }
//   return result;
// }

// string EnrollmentSystem::getClassListByID(const string &courseNumber) const {
//   vector<Student *> classList = stu;
//   sort(classList.begin(), classList.end(), cmpID);
//   // Format the class list into a string separated by commas
//   string result;
//   for (const auto student : classList) {
//     result += student->studentLastName + ", ";
//   }
//   // Remove the trailing comma and space
//   if (!result.empty()) {
//     result = result.substr(0, result.length() - 2);
//   }
//   return result;
// }

bool EnrollmentSystem::cmpLastName(const Student *s1, const Student *s2) {
  return (s1->studentLastName < s2->studentLastName);
}

bool EnrollmentSystem::cmpID(const Student *s1, const Student *s2) {
  return (s1->studentID < s2->studentID);
}

// Return the title for the course
string EnrollmentSystem::getCourseTitle(const string &courseNumber) {
  return courses[courseNumber]->courseName;
}
