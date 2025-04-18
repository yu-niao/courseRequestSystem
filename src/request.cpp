#include "request.h"
#include <ctime>

Request::Request(const std::string& reqId, const std::string& reqrId,
                const std::string& cId, const std::string& d,
                const std::string& r)
    : requestId(reqId), requestorId(reqrId), courseId(cId),
      date(d), reason(r), status(RequestStatus::PENDING) {}

std::string Request::getRequestId() const {
    return requestId;
}

std::string Request::getRequestorId() const {
    return requestorId;
}

std::string Request::getSubstituterId() const {
    return substituterId;
}

void Request::setSubstituterId(const std::string& id) {
    substituterId = id;
}

RequestStatus Request::getStatus() const {
    return status;
}

void Request::setStatus(RequestStatus newStatus) {
    status = newStatus;
}

std::string Request::getCourseId() const {
    return courseId;
}

std::string Request::getDate() const {
    return date;
}

std::string Request::getReason() const {
    return reason;
}