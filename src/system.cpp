#include "system.h"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>

CourseRequestSystem::CourseRequestSystem() {}

void CourseRequestSystem::addStudent(const Student& student) {
    if (students.find(student.getStudentId()) != students.end()) {
        throw std::runtime_error("学生ID已存在！");
    }
    students[student.getStudentId()] = student;
}

void CourseRequestSystem::removeStudent(const std::string& studentId) {
    auto it = students.find(studentId);
    if (it == students.end()) {
        throw std::runtime_error("找不到该学生！");
    }
    students.erase(it);
}

Student* CourseRequestSystem::getStudent(const std::string& studentId) {
    auto it = students.find(studentId);
    if (it == students.end()) {
        return nullptr;
    }
    return &(it->second);
}

void CourseRequestSystem::addCourse(const Course& course) {
    if (courses.find(course.getCourseId()) != courses.end()) {
        throw std::runtime_error("课程ID已存在！");
    }
    courses[course.getCourseId()] = course;
}

void CourseRequestSystem::removeCourse(const std::string& courseId) {
    auto it = courses.find(courseId);
    if (it == courses.end()) {
        throw std::runtime_error("找不到该课程！");
    }
    courses.erase(it);
}

Course* CourseRequestSystem::getCourse(const std::string& courseId) {
    auto it = courses.find(courseId);
    if (it == courses.end()) {
        return nullptr;
    }
    return &(it->second);
}

void CourseRequestSystem::createRequest(const std::string& requestorId, 
                                      const std::string& courseId,
                                      const std::string& date,
                                      const std::string& reason) {
    // 验证学生和课程是否存在
    if (!getStudent(requestorId)) {
        throw std::runtime_error("请求学生不存在！");
    }
    if (!getCourse(courseId)) {
        throw std::runtime_error("请求课程不存在！");
    }

    // 生成请求ID
    std::stringstream ss;
    ss << "REQ" << requests.size() + 1;
    std::string requestId = ss.str();

    Request request(requestId, requestorId, courseId, date, reason);
    requests.push_back(request);
}

void CourseRequestSystem::acceptRequest(const std::string& requestId, 
                                      const std::string& substituterId) {
    // 查找请求
    for (auto& request : requests) {
        if (request.getRequestId() == requestId) {
            if (request.getStatus() != RequestStatus::PENDING) {
                throw std::runtime_error("该请求已不可接受！");
            }
            if (!getStudent(substituterId)) {
                throw std::runtime_error("代课学生不存在！");
            }
            request.setSubstituterId(substituterId);
            request.setStatus(RequestStatus::ACCEPTED);
            return;
        }
    }
    throw std::runtime_error("找不到该请求！");
}

void CourseRequestSystem::completeRequest(const std::string& requestId) {
    for (auto& request : requests) {
        if (request.getRequestId() == requestId) {
            if (request.getStatus() != RequestStatus::ACCEPTED) {
                throw std::runtime_error("该请求尚未被接受，无法完成！");
            }
            request.setStatus(RequestStatus::COMPLETED);
            return;
        }
    }
    throw std::runtime_error("找不到该请求！");
}

std::vector<Request> CourseRequestSystem::getAvailableRequests() const {
    std::vector<Request> availableRequests;
    for (const auto& request : requests) {
        if (request.getStatus() == RequestStatus::PENDING) {
            availableRequests.push_back(request);
        }
    }
    return availableRequests;
}

std::vector<Request> CourseRequestSystem::getStudentRequests(const std::string& studentId) const {
    std::vector<Request> studentRequests;
    for (const auto& request : requests) {
        if (request.getRequestorId() == studentId || 
            request.getSubstituterId() == studentId) {
            studentRequests.push_back(request);
        }
    }
    return studentRequests;
}

void CourseRequestSystem::displayAllStudents() const {
    std::cout << "\n=== 学生列表 ===" << std::endl;
    std::cout << "总共有 " << students.size() << " 名学生" << std::endl;
    std::cout << std::setw(10) << "学号" << std::setw(15) << "姓名" 
              << std::setw(20) << "专业" << std::setw(10) << "年级" << std::endl;
    std::cout << std::string(55, '-') << std::endl;
    
    for (const auto& pair : students) {
        const Student& student = pair.second;
        std::cout << std::setw(10) << student.getStudentId()
                  << std::setw(15) << student.getName()
                  << std::setw(20) << student.getMajor()
                  << std::setw(10) << student.getGrade() << std::endl;
    }
    std::cout << std::endl;
}

void CourseRequestSystem::displayAllCourses() const {
    std::cout << "\n=== 课程列表 ===" << std::endl;
    std::cout << "总共有 " << courses.size() << " 门课程" << std::endl;
    std::cout << std::setw(10) << "课程ID" << std::setw(20) << "课程名称" 
              << std::setw(15) << "教师" << std::setw(10) << "学分" 
              << std::setw(20) << "上课时间" << std::endl;
    std::cout << std::string(75, '-') << std::endl;
    
    for (const auto& pair : courses) {
        const Course& course = pair.second;
        std::cout << std::setw(10) << course.getCourseId()
                  << std::setw(20) << course.getCourseName()
                  << std::setw(15) << course.getInstructor()
                  << std::setw(10) << course.getCredits()
                  << std::setw(20) << course.getSchedule() << std::endl;
    }
    std::cout << std::endl;
}

void CourseRequestSystem::displayStudentDetails(const std::string& studentId) const {
    auto it = students.find(studentId);
    if (it == students.end()) {
        std::cout << "未找到学号为 " << studentId << " 的学生" << std::endl;
        return;
    }
    
    const Student& student = it->second;
    std::cout << "\n=== 学生详细信息 ===" << std::endl;
    std::cout << "学号: " << student.getStudentId() << std::endl;
    std::cout << "姓名: " << student.getName() << std::endl;
    std::cout << "专业: " << student.getMajor() << std::endl;
    std::cout << "年级: " << student.getGrade() << std::endl;
    
    std::cout << "\n已选课程:" << std::endl;
    const auto& enrolledCourses = student.getCoursesEnrolled();
    if (enrolledCourses.empty()) {
        std::cout << "暂无选课记录" << std::endl;
    } else {
        for (const auto& courseId : enrolledCourses) {
            auto courseIt = courses.find(courseId);
            if (courseIt != courses.end()) {
                const Course& course = courseIt->second;
                std::cout << "- " << course.getCourseId() << ": " 
                         << course.getCourseName() << std::endl;
            }
        }
    }
    std::cout << std::endl;
}

void CourseRequestSystem::displayCourseDetails(const std::string& courseId) const {
    auto it = courses.find(courseId);
    if (it == courses.end()) {
        std::cout << "未找到课程ID为 " << courseId << " 的课程" << std::endl;
        return;
    }
    
    const Course& course = it->second;
    std::cout << "\n=== 课程详细信息 ===" << std::endl;
    std::cout << "课程ID: " << course.getCourseId() << std::endl;
    std::cout << "课程名称: " << course.getCourseName() << std::endl;
    std::cout << "授课教师: " << course.getInstructor() << std::endl;
    std::cout << "学分: " << course.getCredits() << std::endl;
    std::cout << "上课时间: " << course.getSchedule() << std::endl;
    std::cout << std::endl;
}

size_t CourseRequestSystem::getStudentCount() const {
    return students.size();
}

size_t CourseRequestSystem::getCourseCount() const {
    return courses.size();
}