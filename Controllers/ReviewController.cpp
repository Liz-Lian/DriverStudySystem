#include "ReviewController.h"

ReviewController::ReviewController(QObject *parent)
    : QObject(parent)
{
}

// 准备错题数据(返回错题数量)
int ReviewController::prepareReview(const QVector<Question>& allQuestions, const QVector<QString>& userAnswers)
{
    m_wrongQuestions.clear();
    m_wrongUserAnswers.clear();

    if (allQuestions.size() != userAnswers.size()) {
        return 0;
    }

    for (int i = 0; i < allQuestions.size(); ++i) {
        QString correct = allQuestions[i].answer.trimmed().toUpper();
        QString user = userAnswers[i].trimmed().toUpper();

        // 如果没答或者答错，都算错题
        if (user.isEmpty() || user != correct) {
            m_wrongQuestions.append(allQuestions[i]);
            m_wrongUserAnswers.append(user);
        }
    }

    return m_wrongQuestions.size();
}

// 获取错题列表
const QVector<Question>& ReviewController::getWrongQuestions() const
{
    return m_wrongQuestions;
}

// 获取指定错题索引对应的用户错误答案
QString ReviewController::getWrongUserAnswer(int index) const
{
    if (index >= 0 && index < m_wrongUserAnswers.size()) {
        return m_wrongUserAnswers[index];
    }
    return QString();
}

// 获取错题总数
int ReviewController::getWrongCount() const
{
    return m_wrongQuestions.size();
}
