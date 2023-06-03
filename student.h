#ifndef STUDENT_H
#define STUDENT_H

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// forward declaration
class Course;

class Student {
  friend class Course;
  friend class University;
  friend class EnrollmentSystem;
  friend ostream &operator<<(ostream &out, const Student &student);

public:
  Student(const int &idNumber, const string &lastName, const string &firstName);
  bool dropCourse(int studentID, const string &courseNumber);
  bool addCourse(int studentID, const string &courseNumber);
  bool isInCourse(int studentID, const string &courseNumber) const;

private:
  string studentLastName;
  string studentfirstName;
  int studentID;

  unordered_map<int, vector<Course *>> enrollmentInfo;
};

#endif