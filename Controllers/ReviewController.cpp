#include "ReviewController.h"

ReviewController::ReviewController(QObject *parent)
    : QObject(parent)
{
}

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

const QVector<Question>& ReviewController::getWrongQuestions() const
{
    return m_wrongQuestions;
}

QString ReviewController::getWrongUserAnswer(int index) const
{
    if (index >= 0 && index < m_wrongUserAnswers.size()) {
        return m_wrongUserAnswers[index];
    }
    return QString();
}

int ReviewController::getWrongCount() const
{
    return m_wrongQuestions.size();
}
