#pragma once

#include <QString>

// 题目结构体
struct Question {
    int id; // 题目ID
    QString content; // 题干
    QString optionA; // 选项A
    QString optionB; // 选项B
    QString optionC; // 选项C
    QString optionD; // 选项D
    QString answer; // A, B, C, or D
};

// 考试记录结构体
struct ExamRecord {
    QString userID; // 用户名
    int score; // 分数
    QString time; // 考试时间
    QString mode; // 考试模式
};

// 考试模式枚举
enum ExamMode {
    MockExam,    // 模拟考试
    FreeTraining // 自由训练
};

// 全局配置常量
constexpr int EXAM_TIME_LIMIT_SECONDS = 2700; // 45分钟
constexpr int EXAM_QUESTIONS_NUM = 5;
constexpr const char* ADMIN_PASSWORD = "123456"; // 管理员密码
