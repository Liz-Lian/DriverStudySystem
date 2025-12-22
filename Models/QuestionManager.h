#ifndef QUESTIONMANAGER_H
#define QUESTIONMANAGER_H

#include <QString>
#include <QVector>
#include <QList>
#include "GlobalTypes.h"

class QuestionManager {
public:
    QuestionManager();

    // 用文本文件读写试题库
    bool loadQuestions(const QString& filename);
    bool saveQuestions(const QString& filename);

    // 增删改试题
    void addQuestion(const Question& q);
    bool deleteQuestion(int id);
    bool updateQuestion(int id, const Question& newQ);

    // 根据关键词模糊搜索题目
    QVector<Question> searchQuestions(const QString& keyword);

    // 随机抽取 N 道不重复题目
    QVector<Question> generateExam(int n);

    // 对比答案并判分 (这里假设 qIndex 是题目的 ID)
    bool checkAnswer(int questionId, const QString& userAns);

    // 获取所有题目（用于显示列表等）
    const QVector<Question>& getAllQuestions() const;

    // 根据ID获取题目
    Question getQuestionById(int id);

private:
    QVector<Question> m_questions;
    int m_nextId; // 用于生成新题目的ID
};

#endif // QUESTIONMANAGER_H
