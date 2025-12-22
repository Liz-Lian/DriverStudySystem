#pragma once

#include <QString>

// 题目结构体
struct Question {
    int id;
    QString content;
    QString optionA;
    QString optionB;
    QString optionC;
    QString optionD;
    QString answer; // A, B, C, or D
};

// 考试记录结构体
struct ExamRecord {
    QString userID;
    int score;
    QString time; // 考试时间
    QString mode; // 考试模式
};

// 考试模式枚举
enum ExamMode {
    MockExam,    // 模拟考试
    FreeTraining // 自由训练
};
