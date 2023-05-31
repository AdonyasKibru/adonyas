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
  //friend ostream &operator<<(ostream &out, const Course &course);

public:
  // Course(const string &courseID, const string &courseName);
  // virtual ~Course();
  // void addStudent(Student *student);
  // void removeStudent(Student *student);
  // vector<Student *> getClassListByLastName();
  // vector<Student *> getClassListByID();
  // bool cmpLastName(const Student *s1, const Student *s2);
  // bool cmpID(const Student *s1, const Student *s2);

private:
  // string courseID;
  // string courseName;
  // unordered_map<int, Student *> students;
};

#endif