#ifndef SYSTEM_H
#define SYSTEM_H

#include "database.h"  // 确保包含数据库头文件
#include <vector>
#include <map>
#include "student.h"
#include "course.h"
#include "request.h"

class CourseRequestSystem {
private:
    Database db;  // 声明数据库成员变量
    std::map<std::string, Student> students;
    std::map<std::string, Course> courses;
    std::vector<Request> requests;

public:
    CourseRequestSystem();
    ~CourseRequestSystem();
    
    // 学生管理
    void addStudent(const Student& student);
    void removeStudent(const std::string& studentId);
    Student* getStudent(const std::string& studentId);
    
    // 课程管理
    void addCourse(const Course& course);
    void removeCourse(const std::string& courseId);
    Course* getCourse(const std::string& courseId);
    
    // 请求管理
    void createRequest(const std::string& requestorId, 
                      const std::string& courseId,
                      const std::string& date,
                      const std::string& reason);
    void acceptRequest(const std::string& requestId, 
                      const std::string& substituterId);
    void completeRequest(const std::string& requestId);
    
    // 查询功能
    std::vector<Request> getAvailableRequests() const;
    std::vector<Request> getStudentRequests(const std::string& studentId) const;
    void displayAllStudents() const;  // 显示所有学生信息
    void displayAllCourses() const;   // 显示所有课程信息
    void displayStudentDetails(const std::string& studentId) const; // 显示特定学生详细信息
    void displayCourseDetails(const std::string& courseId) const;   // 显示特定课程详细信息
    
    // 获取数据大小
    size_t getStudentCount() const;
    size_t getCourseCount() const;
};

#endif