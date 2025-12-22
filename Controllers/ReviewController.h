#ifndef REVIEWCONTROLLER_H
#define REVIEWCONTROLLER_H

#include <QObject>
#include <QVector>
#include <QString>
#include "GlobalTypes.h"

class ReviewController : public QObject
{
    Q_OBJECT
public:
    explicit ReviewController(QObject *parent = nullptr);

    // 准备错题数据
    // 返回错题数量
    int prepareReview(const QVector<Question>& allQuestions, const QVector<QString>& userAnswers);

    // 获取错题列表
    const QVector<Question>& getWrongQuestions() const;

    // 获取指定错题索引对应的用户错误答案
    QString getWrongUserAnswer(int index) const;

    // 获取错题总数
    int getWrongCount() const;

private:
    QVector<Question> m_wrongQuestions;
    QVector<QString> m_wrongUserAnswers; // 存储与 m_wrongQuestions 一一对应的用户错选答案
};

#endif // REVIEWCONTROLLER_H
