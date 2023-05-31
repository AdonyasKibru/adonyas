#include "university.h"
#include "student.h"

#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

University::University(const string &name) : universityName(name) {}

University::~University() {}

// // parses a student list from a .txt file
// void University::readStudentList(const string &filename) {}

// // parses course list from a .txt file
// void University::readCourseList(const string &filename) {}

// // parses enrollment info from a .txt file
// void University::readEnrollmentInfo(const string &filename) {}

// // adds a course to this enrollment system.
// void University::addCourse(Course *course) {}

// // removes a course from this enrollment system.
// void University::dropCourse(Course *course) {}

// // checks if a student is in a given course.
// bool University::isInCourse(Student *student, Course *course) {}

// // returns a list of courses this student is enrolled in.
// vector<Course *> University::getEnrolledCourses(Student *student) {}
// // returns class list sorted by last name of the students
// vector<Student *> University::getClassListByLastName(const string &lastName) {}

// // return class list sorted by ID of the students
// vector<Student *> University::getClassListByID(const string &studentID) {}

// // returns the title for the course
// string University::getCourseTitle(Course *course) {}
