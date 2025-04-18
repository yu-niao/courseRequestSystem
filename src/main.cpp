#include <iostream>
#include <limits>
#include <cstdlib>
#include "system.h"

// 清屏函数
void clearScreen() {
#ifdef _WIN32
    system("cls");  // Windows系统
#else
    system("clear");  // Unix/Linux/MacOS系统
#endif
}

// 按任意键继续
void pauseScreen() {
    std::cout << "\n按回车键继续...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void clearInputBuffer() {
    std::cin.clear();   // 清除任何错误标志
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // 忽略缓冲区中直到换行符的所有内容
}

void displayMenu() {
    std::cout << "\n=== 学生代课系统 ===" << std::endl;
    std::cout << "1. 注册新学生" << std::endl;
    std::cout << "2. 添加新课程" << std::endl;
    std::cout << "3. 发布代课请求" << std::endl;
    std::cout << "4. 查看可用的代课请求" << std::endl;
    std::cout << "5. 接受代课请求" << std::endl;
    std::cout << "6. 完成代课请求" << std::endl;
    std::cout << "7. 查看所有学生信息" << std::endl;
    std::cout << "8. 查看所有课程信息" << std::endl;
    std::cout << "9. 查看学生详细信息" << std::endl;
    std::cout << "10. 查看课程详细信息" << std::endl;
    std::cout << "11. 退出" << std::endl;
    std::cout << "请选择操作 (1-11): ";
}

int main() {
    CourseRequestSystem system;
    int choice;
    std::string input;

    while (true) {
        clearScreen();  // 每次循环开始时清屏
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        clearScreen();  // 选择后清屏

        try {
            switch (choice) {
                case 1: {
                    std::cout << "=== 注册新学生 ===" << std::endl;
                    std::string id, name, major;
                    int grade;
                    
                    std::cout << "输入学生ID: ";
                    std::getline(std::cin, id);
                    std::cout << "输入姓名: ";
                    std::getline(std::cin, name);
                    std::cout << "输入专业: ";
                    std::getline(std::cin, major);
                    std::cout << "输入年级: ";
                    std::cin >> grade;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    Student student(id, name, major, grade);
                    system.addStudent(student);
                    std::cout << "\n学生注册成功！" << std::endl;
                    pauseScreen();
                    break;
                }
                case 2: {
                    std::cout << "=== 添加新课程 ===" << std::endl;
                    std::string id, name, instructor, schedule;
                    int credits;
                    
                    std::cout << "输入课程ID: ";
                    std::getline(std::cin, id);
                    std::cout << "输入课程名称: ";
                    std::getline(std::cin, name);
                    std::cout << "输入授课教师: ";
                    std::getline(std::cin, instructor);
                    std::cout << "输入课程学分: ";
                    std::cin >> credits;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "输入课程时间安排: ";
                    std::getline(std::cin, schedule);
                    
                    Course course(id, name, instructor, credits, schedule);
                    system.addCourse(course);
                    std::cout << "\n课程添加成功！" << std::endl;
                    pauseScreen();
                    break;
                }
                case 3: {
                    std::cout << "=== 发布代课请求 ===" << std::endl;
                    std::string studentId, courseId, date, reason;
                    
                    std::cout << "输入学生ID: ";
                    std::getline(std::cin, studentId);
                    std::cout << "输入课程ID: ";
                    std::getline(std::cin, courseId);
                    std::cout << "输入代课日期: ";
                    std::getline(std::cin, date);
                    std::cout << "输入代课原因: ";
                    std::getline(std::cin, reason);
                    
                    system.createRequest(studentId, courseId, date, reason);
                    std::cout << "\n代课请求发布成功！" << std::endl;
                    pauseScreen();
                    break;
                }
                case 4: {
                    std::cout << "=== 可用的代课请求 ===" << std::endl;
                    auto requests = system.getAvailableRequests();
                    if (requests.empty()) {
                        std::cout << "当前没有可用的代课请求。" << std::endl;
                    } else {
                        for (const auto& req : requests) {
                            std::cout << "\n请求ID: " << req.getRequestId() << std::endl;
                            std::cout << "请求者ID: " << req.getRequestorId() << std::endl;
                            std::cout << "课程ID: " << req.getCourseId() << std::endl;
                            std::cout << "日期: " << req.getDate() << std::endl;
                            std::cout << "原因: " << req.getReason() << std::endl;
                            std::cout << "------------------------" << std::endl;
                        }
                    }
                    pauseScreen();
                    break;
                }
                case 5: {
                    std::string requestId, substituterId;
                    
                    std::cout << "输入请求ID: ";
                    std::getline(std::cin, requestId);
                    std::cout << "输入代课学生ID: ";
                    std::getline(std::cin, substituterId);
                    
                    system.acceptRequest(requestId, substituterId);
                    std::cout << "成功接受代课请求！" << std::endl;
                    pauseScreen();
                    break;
                }
                case 6: {
                    std::string requestId;
                    
                    std::cout << "输入要完成的请求ID: ";
                    std::getline(std::cin, requestId);
                    
                    system.completeRequest(requestId);
                    std::cout << "请求已标记为完成！" << std::endl;
                    pauseScreen();
                    break;
                }
                case 7: {
                    system.displayAllStudents();
                    pauseScreen();
                    break;
                }
                case 8: {
                    system.displayAllCourses();
                    pauseScreen();
                    break;
                }
                case 9: {
                    std::string studentId;
                    std::cout << "请输入要查询的学生学号: ";
                    std::getline(std::cin, studentId);
                    system.displayStudentDetails(studentId);
                    pauseScreen();
                    break;
                }
                case 10: {
                    std::string courseId;
                    std::cout << "请输入要查询的课程ID: ";
                    std::getline(std::cin, courseId);
                    system.displayCourseDetails(courseId);
                    pauseScreen();
                    break;
                }
                case 11:
                    clearScreen();
                    std::cout << "感谢使用！再见！" << std::endl;
                    return 0;
                default:
                    std::cout << "无效的选择，请重试。" << std::endl;
                    pauseScreen();
            }
        } catch (const std::exception& e) {
            std::cout << "\n错误：" << e.what() << std::endl;
            pauseScreen();
        }
    }
    
    return 0;
}