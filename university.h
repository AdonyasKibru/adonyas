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
  explicit University(const string &name);
  virtual ~University();

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

  // Return the courses student is enrolled in
  // The returned courses are separated by commas and sorted by course name
  string getEnrolledCourses(int studentID) const;

  // vector<Student *> getClassListByLastName();
  // vector<Student *> getClassListByID();
  bool cmpLastName(const Student *stu1, const Student *stu2);
  bool cmpID(const Student *stu1, const Student *stu2);
  // Return the title for the course
  string getCourseTitle(const string &courseNumber);

private:
  string universityName;
  vector<Student *> uniStudents;
  vector<Course *> Courses;
};

#endif