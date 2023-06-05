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

public:
  explicit Course(const string &courseID);
  Course(const string &courseID, const string &courseName);
  void addStudent(Student *student);
  void removeStudent(Student *student);
  // Return class list sorted by last name of students
  string getClassListByLastName(const string &courseNumber);
  // Return class list sorted by id of students
  string getClassListByID(const string &courseNumber);
  static bool cmpLastName(const Student *stu1, const Student *stu2);
  static bool cmpID(const Student *stu1, const Student *stu2);

private:
  string courseID;
  string courseName;

  // store the course ID and their names from the text
  unordered_map<string, vector<Student *>> students;
};

#endif