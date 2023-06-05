#include "university.h"
#include "student.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

/*constructor*/
University::University(const string &name) : universityName(name) {}

/*Destructor*/
University::~University() {
  for (const auto &pair : uniStudents) {
    for (auto &enrollment : pair.second->enrollmentInfo) {
      for (Course *course : enrollment.second) {
        delete course;
      }
    }
    delete pair.second;
  }

  for (Course *course : Courses) {
    delete course;
  }
}

/* Read the student list for current active university
 return true if file successfully read*/
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
    if (uniStudents.find(stuID) == uniStudents.end()) {
      uniStudents[stuID] = new Student(stuID, lastName, firstName);
    }
  }
  loadFile.close();
  return true;
}

/* Read the course list for current active university
 return true if file successfully read*/
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

/* Read the student enrollment information for current active university
 return true if file successfully read*/
bool University::readEnrollmentInfo(const string &filename) {
  ifstream loadFile;
  loadFile.open(filename);

  if (!loadFile.is_open()) {
    cerr << "This file " << filename << " is not opened." << endl;
    return false;
  }

  string line;
  while (getline(loadFile, line)) {
    int stuID;
    string shortName;

    stringstream ssLine(line);
    ssLine >> stuID >> shortName;

    for (const auto &pair : uniStudents) {
      if (pair.second->addCourse(stuID, shortName)) {
        for (Course *val : Courses) {
          if (pair.second->studentID == stuID) {
            val->students[shortName].push_back(pair.second);
          }
        }
      }
    }
  }

  loadFile.close();
  return true;
}

/* Drop student from given course, return true if successful*/
bool University::dropCourse(int studentID, const string &courseNumber) {
  bool ans = false;
  for (const auto &pair : uniStudents) {
    for (int i = 0; i < pair.second->enrollmentInfo[studentID].size(); i++) {
      if (pair.second->enrollmentInfo[studentID][i]->courseID == courseNumber) {
        for (int j = i; j < pair.second->enrollmentInfo[studentID].size() - 1;
             j++) {
          pair.second->enrollmentInfo[studentID][j] =
              pair.second->enrollmentInfo[studentID][j + 1];
        }
        pair.second->enrollmentInfo[studentID].pop_back();
        ans = true;
        break;
      }
    }
  }

  return ans;
}

/*This is used to add a student to a course*/
bool University::addCourse(int studentID, const string &courseNumber) {
  bool ans = false;
  for (const auto &pair : uniStudents) {
    if (pair.second->addCourse(studentID, courseNumber)) {
      ans = true;
      for (Course *val : Courses) {
        if (pair.second->studentID == studentID) {
          val->students[courseNumber].push_back(pair.second);
        }
      }
    }
  }
  return ans;
}

/* Return true if student is in the given course*/
bool University::isInCourse(int studentID, const string &courseNumber) const {
  for (const auto &pair : uniStudents) {
    if (pair.second->studentID == studentID) {
      return pair.second->isInCourse(studentID, courseNumber);
    }
  }
  return false;
}

/* Return the courses student is enrolled in
The returned courses are separated by commas and sorted by course name*/
string University::getEnrolledCourses(int studentID) const {
  string ans = "[";
  Student *value;
  for (const auto pair : uniStudents) {
    value = pair.second;
  }
  ans = ans + value->enrollmentInfo[studentID][0]->courseID;
  for (int i = 1; i < value->enrollmentInfo[studentID].size(); i++) {
    ans += ", ";
    ans += value->enrollmentInfo[studentID][i]->courseID;
  }
  ans += "]";
  return ans;
}

/*Return class list sorted by last name of students*/
string University::getClassListByLastName(const string &courseNumber) {
  string answer;
  for (Course *val : Courses) {
    answer = val->getClassListByLastName(courseNumber);
  }
  return answer;
}
/*Return class list sorted by id of students*/
string University::getClassListByID(const string &courseNumber) {
  string answer;
  for (Course *val : Courses) {
    answer = val->getClassListByID(courseNumber);
  }
  return answer;
}

/*is a function used to create a comparator for students by lastName*/
bool University::cmpLastName(const Student *stu1, const Student *stu2) {
  bool answer;
  Course *val = Courses[0];
  answer = val->cmpLastName(stu1, stu2);
  return answer;
}

/*is a function used to create a comparator for students by ID*/
bool University::cmpID(const Student *stu1, const Student *stu2) {
  bool answer;
  Course *val = Courses[0];
  answer = val->cmpID(stu1, stu2);
  return answer;
}

/*Return the title for the course*/
string University::getCourseTitle(const string &courseNumber) {
  string answer;
  for (Course *val : Courses) {
    if (val->courseID == courseNumber) {
      answer = val->courseName;
    }
  }
  return answer;
}