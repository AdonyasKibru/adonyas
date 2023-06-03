#ifndef COURSE_H
#define COURSE_H

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// forward declaration
class Student;

class Course {
  friend class Student;
  friend class University;
  friend class EnrollmentSystem;
  friend ostream &operator<<(ostream &out, const Course &course);

public:
  Course(const string &courseID);
  Course(const string &courseID, const string &courseName);
  virtual ~Course();
  void addStudent(Student *student);
  void removeStudent(Student *student);
  // // Return class list sorted by last name of students
  // string getClassListByLastName(const string &courseNumber) const;
  // // Return class list sorted by id of students
  // string getClassListByID(const string &courseNumber) const;
  bool cmpLastName(const Student *s1, const Student *s2);
  bool cmpID(const Student *s1, const Student *s2);

private:
  string courseID;
  string courseName;

  // store the student ID and their names from the text
  unordered_map<string, vector<Student*>> students;
};

#endif