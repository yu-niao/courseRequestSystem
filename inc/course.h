#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>

class Course {
private:
    std::string courseId;    // 课程ID
    std::string courseName;  // 课程名称
    std::string instructor;  // 授课教师
    int credits;            // 学分
    std::string schedule;    // 课程时间安排

public:
    // 添加默认构造函数
    Course() : credits(0) {}
    Course(const std::string& id, const std::string& name, 
          const std::string& inst, int cred, const std::string& sched);
    
    std::string getCourseId() const;
    std::string getCourseName() const;
    std::string getInstructor() const;
    int getCredits() const;
    std::string getSchedule() const;
};

#endif