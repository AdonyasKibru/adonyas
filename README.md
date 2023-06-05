# 2023win342d-p5-AdonyasKibru
2023win342d-p5-AdonyasKibru created by GitHub Classroom
Project done by: Adonyas Kibru

The program successfully passes all the test cases, demonstrating correct functionality
and meeting the expected requirements. However, it is important to note that there is a
memory leak in the program. The memory leak is detected as a "Direct leak of 16440 byte(s)
in 137 object(s)" and is traced back to the addCourse function in the Student class.

The memory leak occurs when dynamically allocating memory for Course objects using the 
new keyword and storing them in the enrollmentInfo container. Although their is a destructor in University class
and deleting the pointer result in double free error leaving it cause leaked memory. 

It is also important to know that the test doess not cover all possible cases so thier are misses.

There are also some clang tidy warnings that can not be solved because of the structure of the functions
and the requirments 

**Here are the specific errors and their explanations:**

bugprone-easily-swappable-parameters: This warning suggests that two adjacent parameters of a function have
similar types and could be easily swapped by mistake.

readability-use-anyofallof: This warning suggests replacing a loop with std::any_of() for better readability.
It points out a for-loop in the EnrollmentSystem class.

readability-identifier-length: This warning indicates that variable or function names are too short and suggests 
using longer names. It appears for variables like es in main.cpp, ss in university.cpp, and some others.

readability-redundant-string-init: This warning indicates redundant initialization of a string variable. 
It points out the longName variable in the University class. 

readability-static-accessed-through-instance: This warning indicates that a static member is accessed 
through an instance instead of using the class name. 
