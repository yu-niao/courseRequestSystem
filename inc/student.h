#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <vector>
#include <algorithm>

class Student {
private:
    std::string studentId;  // 学生ID
    std::string name;       // 学生姓名
    std::string major;      // 学生专业
    int grade;             // 学生年级
    std::vector<std::string> coursesEnrolled; // 学生已选课程列表

public:
    Student() : grade(0) {}

    Student(const std::string& id, const std::string& n, const std::string& m, int g);
    
    std::string getStudentId() const;
    std::string getName() const;
    std::string getMajor() const;
    int getGrade() const;
    const std::vector<std::string>& getCoursesEnrolled() const;
    
    // 添加或删除已选课程
    void addCourse(const std::string& courseId);
    void removeCourse(const std::string& courseId);
};

#endif