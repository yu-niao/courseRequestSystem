#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include "student.h"
#include "course.h"

enum class RequestStatus {
    PENDING,    // 待处理
    ACCEPTED,   // 已接受
    REJECTED,   // 已拒绝
    COMPLETED   // 已完成
};

class Request {
private:
    std::string requestId;   // 请求ID
    std::string requestorId; // 请求代课的学生ID
    std::string substituterId; // 代课学生ID
    std::string courseId;    // 课程ID
    std::string date;        // 请求日期
    std::string reason;      // 请求原因
    RequestStatus status;    // 请求状态

public:
    Request(const std::string& reqId, const std::string& reqrId,
            const std::string& courseId, const std::string& date,
            const std::string& reason);
    
    std::string getRequestId() const;
    std::string getRequestorId() const;
    std::string getSubstituterId() const;
    void setSubstituterId(const std::string& id);
    RequestStatus getStatus() const;
    void setStatus(RequestStatus newStatus);
    std::string getCourseId() const;
    std::string getDate() const;
    std::string getReason() const;
};

#endif