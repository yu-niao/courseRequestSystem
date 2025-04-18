#include "student.h"

Student::Student(const std::string& id, const std::string& n, const std::string& m, int g)
    : studentId(id), name(n), major(m), grade(g) {}

std::string Student::getStudentId() const {
    return studentId;
}

std::string Student::getName() const {
    return name;
}

std::string Student::getMajor() const {
    return major;
}

int Student::getGrade() const {
    return grade;
}

const std::vector<std::string>& Student::getCoursesEnrolled() const {
    return coursesEnrolled;
}

void Student::addCourse(const std::string& courseId) {
    // 检查课程是否已经存在
    for (const auto& course : coursesEnrolled) {
        if (course == courseId) return;
    }
    coursesEnrolled.push_back(courseId);
}

void Student::removeCourse(const std::string& courseId) {
    auto it = std::find(coursesEnrolled.begin(), coursesEnrolled.end(), courseId);
    if (it != coursesEnrolled.end()) {
        coursesEnrolled.erase(it);
    }
}