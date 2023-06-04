#ifndef ENROLLMENTSYSTEM_H
#define ENROLLMENTSYSTEM_H

#include "university.h"
#include <map>
#include <string>

using namespace std;

class EnrollmentSystem {

public:
  ~EnrollmentSystem();

  // Add university to the enrollments system
  bool addUniversity(const string &name);

  // Set this university as the active university for other functions
  bool setCurrentUniversity(const string &name);

  // Return the current active university name
  string getUniversityName() const;

  // Return the courses student is enrolled in
  // The returned courses are separated by commas and sorted by course name
  string getEnrolledCourses(int studentID);

  // Read the student list for current active university
  // return true if file successfully read
  bool readStudentList(const string &filename);

  // Read the course list for current active university
  // return true if file successfully read
  bool readCourseList(const string &filename);

  // Read the student enrollment information for current active university
  // return true if file successfully read
  bool readEnrollmentInfo(const string &filename);

  bool dropCourse(int studentID, const string &courseNumber);
  bool addCourse(int studentID, const string &courseNumber);
  bool isInCourse(int studentID, const string &courseNumber) const;

    // Return class list sorted by last name of students
  string getClassListByLastName(const string &courseNumber);

  // Return class list sorted by id of students
  string getClassListByID(const string &courseNumber) const;

  bool cmpLastName(const Student *stu1, const Student *stu2);
  bool cmpID(const Student *stu1, const Student *stu2);
  // Return the title for the course
  string getCourseTitle(const string &courseNumber);

private:
  // current active university
  University *currentUniversity;

  vector<University *> universties;
};

#endif