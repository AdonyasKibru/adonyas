
#include "enrollmentsystem.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

// check enrollment system
void test1() {
  EnrollmentSystem eas;
  assert(eas.addUniversity("UWB"));
  assert(!eas.addUniversity("UWB"));
  assert(eas.addUniversity("UW Seattle"));
  assert(eas.addUniversity("UW Tacoma"));
  assert(!eas.setCurrentUniversity("UWx"));
  assert(eas.setCurrentUniversity("UWB"));
  assert(eas.getUniversityName() == "UWB");
  // // read data
  assert(eas.readCourseList("data-courses.txt"));
  assert(eas.readStudentList("data-students.txt"));
  assert(eas.readEnrollmentInfo("data-enrollments.txt"));
  // // check courses
  assert(!eas.addCourse(999, "CSS342"));
  assert(!eas.addCourse(1070, "CSS3422"));
  assert(!eas.isInCourse(1070, "CSS342"));
  assert(eas.addCourse(1070, "CSS342"));
  assert(eas.dropCourse(1070, "CSS343"));
  assert(eas.getCourseTitle("CSS342") ==
         "Data Structures, Algorithms, and Discrete Mathematics I");
  // // check enrollments
  assert(eas.getEnrolledCourses(1070) == "[CSS110, CSS173, CSS342]");
  string c342byLastName =
      "[Collins, Cassandra (1070), Evans, Juan (1401), Gonzalez, Holly (1223), "
      "Henderson, Daniel (1364), Taylor, Alexander (1986), Thompson, Christine "
      "(1386), Watson, Alex (1211)]";
  assert(eas.getClassListByLastName("CSS342") == c342byLastName);
  string c342byID =
      "[Collins, Cassandra (1070), Watson, Alex (1211), Gonzalez, Holly "
      "(1223), Henderson, Daniel (1364), Thompson, Christine (1386), Evans, "
      "Juan (1401), Taylor, Alexander (1986)]";
  assert(eas.getClassListByID("CSS342") == c342byID);
}

// run all tests
int main() {
  test1();

  cout << "Done." << endl;
}
