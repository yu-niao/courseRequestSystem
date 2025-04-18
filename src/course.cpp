#include "course.h"

Course::Course(const std::string& id, const std::string& name, 
              const std::string& inst, int cred, const std::string& sched)
    : courseId(id), courseName(name), instructor(inst), 
      credits(cred), schedule(sched) {}

std::string Course::getCourseId() const {
    return courseId;
}

std::string Course::getCourseName() const {
    return courseName;
}

std::string Course::getInstructor() const {
    return instructor;
}

int Course::getCredits() const {
    return credits;
}

std::string Course::getSchedule() const {
    return schedule;
}