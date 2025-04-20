#include "database.h"
#include <sstream>
#include <iostream>

Database::Database() {
    // 初始化数据库连接参数
    host = "localhost";
    user = "root";  
    password = "654826hxj..";  
    database = "course_request_system";
    port = 3306;
    
    // 初始化MySQL
    conn = mysql_init(NULL);
    if (conn == NULL) {
        std::cout << "MySQL 初始化失败" << std::endl;
        exit(1);
    }
}

Database::~Database() {
    disconnect();
}

bool Database::connect() {
    // 连接到数据库
    if (mysql_real_connect(conn, host, user, password, 
                          database, port, NULL, 0) == NULL) {
        std::cout << "数据库连接失败: 111" << mysql_error(conn) <<  " 222" << std::endl;
        return false;
    }
    // 设置字符集
    mysql_set_character_set(conn, "utf8");
    return true;
}

void Database::disconnect() {
    // 关闭数据库连接
    if (conn != NULL) {
        mysql_close(conn);
        conn = NULL;
    }
}

bool Database::addStudent(const Student& student) {
    // 构建插入学生的SQL语句
    std::stringstream ss;
    ss << "INSERT INTO students (student_id, name, major, grade) VALUES ('"
       << student.getStudentId() << "', '"
       << student.getName() << "', '"
       << student.getMajor() << "', "
       << student.getGrade() << ")";
       
    // 执行SQL语句
    if (mysql_query(conn, ss.str().c_str())) {
        std::cout << "添加学生失败: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

Student* Database::getStudent(const std::string& studentId) {
    // 查询学生信息
    std::string query = "SELECT * FROM students WHERE student_id = '" + studentId + "'";
    
    if (mysql_query(conn, query.c_str())) {
        std::cout << "查询学生失败: " << mysql_error(conn) << std::endl;
        return nullptr;
    }
    
    // 获取查询结果
    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL) {
        return nullptr;
    }
    
    // 获取学生数据
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        mysql_free_result(result);
        return nullptr;
    }
    
    // 创建学生对象
    Student* student = new Student(row[0], row[1], row[2], std::stoi(row[3]));
    mysql_free_result(result);
    return student;
}

std::vector<Student> Database::getAllStudents() {
    std::vector<Student> students;
    // 查询所有学生
    std::string query = "SELECT * FROM students";
    
    if (mysql_query(conn, query.c_str())) {
        std::cout << "查询所有学生失败: " << mysql_error(conn) << std::endl;
        return students;
    }
    
    // 获取结果集
    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL) {
        return students;
    }
    
    // 遍历所有学生数据
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        students.emplace_back(row[0], row[1], row[2], std::stoi(row[3]));
    }
    
    mysql_free_result(result);
    return students;
}
