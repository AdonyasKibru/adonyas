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
/*Destructor*/
EnrollmentSystem::~EnrollmentSystem() {
  for (University *university : universties) {
    delete university;
  }
}

/*Add university to the enrollments system*/
bool EnrollmentSystem::addUniversity(const string &name) {
  for (University *val : universties) {
    if (val->universityName == name) {
      return false;
    }
  }
  universties.push_back(new University(name));
  return true;
}

/*Set this university as the active university for other functions*/
bool EnrollmentSystem::setCurrentUniversity(const string &name) {
  for (University *val : universties) {
    if (val->universityName == name) {
      currentUniversity = val;
      return true;
    }
  }
  return false;
}

/*Return the current active university name*/
string EnrollmentSystem::getUniversityName() const {
  return currentUniversity->universityName;
}

/*Return the courses student is enrolled in
 The returned courses are separated by commas and sorted by course name*/
string EnrollmentSystem::getEnrolledCourses(int studentID) {
  University *answer = universties[0];
  string value = answer->getEnrolledCourses(studentID);
  return value;
}

/* Read the student list for current active university
return true if file successfully read*/
bool EnrollmentSystem::readStudentList(const string &filename) {
  University *answer = universties[0];
  bool value = answer->readStudentList(filename);
  return value;
}

/* Read the course list for current active university
 return true if file successfully read*/
bool EnrollmentSystem::readCourseList(const string &filename) {
  University *answer = universties[0];
  bool value = answer->readCourseList(filename);
  return value;
}

/* Read the student enrollment information for current active university
 return true if file successfully read*/
bool EnrollmentSystem::readEnrollmentInfo(const string &filename) {
  University *answer = universties[0];
  bool value = answer->readEnrollmentInfo(filename);
  return value;
}

/*Drop student from given course, return true if successful*/
bool EnrollmentSystem::dropCourse(int studentID, const string &courseNumber) {
  University *answer = universties[0];
  bool value = answer->dropCourse(studentID, courseNumber);
  return value;
}
/*This is used to add a student to a course*/
bool EnrollmentSystem::addCourse(int studentID, const string &courseNumber) {
  University *answer = universties[0];
  bool value = answer->addCourse(studentID, courseNumber);
  return value;
}
/*Return true if student is in the given course*/
bool EnrollmentSystem::isInCourse(int studentID,
                                  const string &courseNumber) const {
  University *answer = universties[0];
  bool value = answer->isInCourse(studentID, courseNumber);
  return value;
}
/*return class of students sorted by thier lastname*/
string EnrollmentSystem::getClassListByLastName(const string &courseNumber) {
  University *answer = universties[0];
  string value = answer->getClassListByLastName(courseNumber);
  return value;
}

/*return class of students sorted by thier ID*/
string EnrollmentSystem::getClassListByID(const string &courseNumber) {
  University *answer = universties[0];
  string value = answer->getClassListByID(courseNumber);
  return value;
}

/*Return the title for the course*/
string EnrollmentSystem::getCourseTitle(const string &courseNumber) {
  University *answer = universties[0];
  string value = answer->getCourseTitle(courseNumber);
  return value;
}
