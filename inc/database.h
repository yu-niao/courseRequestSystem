#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>
#include <string>
#include <vector>
#include "student.h"
#include "course.h"
#include "request.h"

// 数据库管理类
class Database {
private:
    MYSQL* conn;          // MySQL连接句柄
    const char* host;     // 数据库地址
    const char* user;     // 用户名
    const char* password; // 密码
    const char* database; // 数据库名
    unsigned int port;    // 端口号

public:
    Database();
    ~Database();
    
    // 数据库连接管理
    bool connect();
    void disconnect();
    
    // 学生相关操作
    bool addStudent(const Student& student);
    bool updateStudent(const Student& student);
    Student* getStudent(const std::string& studentId);
    std::vector<Student> getAllStudents();
    
    // 课程相关操作
    bool addCourse(const Course& course);
    bool updateCourse(const Course& course);
    Course* getCourse(const std::string& courseId);
    std::vector<Course> getAllCourses();
    
    // 代课请求相关操作
    bool addRequest(const Request& request);
    bool updateRequest(const Request& request);
    Request* getRequest(const std::string& requestId);
    std::vector<Request> getAllRequests();
    std::vector<Request> getAvailableRequests();
};

#endif 