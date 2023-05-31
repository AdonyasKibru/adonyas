#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include "course.h"
#include "student.h"
#include <string>
#include <unordered_map>

using namespace std;

class University {
  friend class EnrollmentSystem;

public:
  University(const string &name);
  virtual ~University();

  // // parses a student list from a .txt file
  // void readStudentList(const string &filename);

  // // parses course list from a .txt file
  // void readCourseList(const string &filename);

  // // parses enrollment info from a .txt file
  // void readEnrollmentInfo(const string &filename);

  // // adds a course to this enrollment system.
  // void addCourse(Course *course);

  // // removes a course from this enrollment system.
  // void dropCourse(Course *course);

  // // checks if a student is in a given course.
  // bool isInCourse(Student *student, Course *course);

  // // returns a list of courses this student is enrolled in.
  // vector<Course *> getEnrolledCourses(Student *student);
  // // returns class list sorted by last name of the students
  // vector<Student *> getClassListByLastName(const string &lastName);

  // // return class list sorted by ID of the students
  // vector<Student *> getClassListByID(const string &studentID);

  // // returns the title for the course
  // string getCourseTitle(Course *course);

private:
  string universityName;
  unordered_map<string, Course *> courses;
};

#endif