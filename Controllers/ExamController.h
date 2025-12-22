#ifndef EXAMCONTROLLER_H
#define EXAMCONTROLLER_H

#include <QObject>
#include <QTimer>
#include "GlobalTypes.h"
#include "QuestionManager.h"

// 考试控制器，负责考试流程和计时
class ExamController : public QObject
{
    Q_OBJECT
public:
    explicit ExamController(QuestionManager* qm, QObject *parent = nullptr);

    // 开始考试
    void startExam(int count, ExamMode mode);
    
    // 停止考试
    void stopExam();

    // 获取当前生成的题目
    QVector<Question> getExamQuestions() const;

    // 获取当前模式
    ExamMode getCurrentMode() const;

signals:
    // 通知UI更新倒计时显示
    void sigTimerUpdated(QString timeStr);
    
    // 通知UI考试时间到
    void sigExamFinished();

private slots:
    // 计时器超时处理
    void onTimerTimeout();

private:
    // 
    QuestionManager* m_questionManager;
    QTimer* m_timer;
    int m_remainingSeconds;
    ExamMode m_currentMode;
    QVector<Question> m_currentQuestions;
};

#endif
