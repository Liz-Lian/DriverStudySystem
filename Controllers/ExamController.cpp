#include "ExamController.h"
#include <QDebug>

ExamController::ExamController(QuestionManager* qm, QObject *parent)
    : QObject(parent)
    , m_questionManager(qm)
    , m_remainingSeconds(0)
    , m_currentMode(ExamMode::MockExam)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ExamController::onTimerTimeout);
}

void ExamController::startExam(int count, ExamMode mode)
{
    m_currentMode = mode;
    
    // 生成题目
    m_currentQuestions = m_questionManager->generateExam(count);

    // 如果是模拟考试，启动倒计时 (例如45分钟 = 2700秒)
    if (m_currentMode == ExamMode::MockExam) {
        m_remainingSeconds = 45 * 60; 
        m_timer->start(1000); // 每秒触发一次
        
        // 立即更新一次UI
        onTimerTimeout();
    } else {
        // 自由训练模式不计时
        m_timer->stop();
        emit sigTimerUpdated("自由训练模式");
    }
}

void ExamController::stopExam()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }
}

QVector<Question> ExamController::getExamQuestions() const
{
    return m_currentQuestions;
}

ExamMode ExamController::getCurrentMode() const
{
    return m_currentMode;
}

void ExamController::onTimerTimeout()
{
    if (m_remainingSeconds > 0) {
        m_remainingSeconds--;
        
        int minutes = m_remainingSeconds / 60;
        int seconds = m_remainingSeconds % 60;
        QString timeStr = QString("%1:%2")
                            .arg(minutes, 2, 10, QChar('0'))
                            .arg(seconds, 2, 10, QChar('0'));
        
        emit sigTimerUpdated(timeStr);
    } else {
        m_timer->stop();
        emit sigExamFinished();
    }
}
