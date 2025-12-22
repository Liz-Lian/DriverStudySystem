#include "QuestionManager.h"
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QDebug>
#include <algorithm>
#include <algorithm>
#include <random>
#include <chrono>


QuestionManager::QuestionManager() : m_nextId(1) {
}

bool QuestionManager::loadQuestions(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading:" << filename;
        return false;
    }

    m_questions.clear();
    QTextStream in(&file);
    // 假设文件格式为每7行一道题：ID, Content, A, B, C, D, Answer
    // 或者使用简单的分隔符格式。这里采用简单的基于行的格式，更易读。
    // 格式：
    // ID
    // Content
    // OptionA
    // OptionB
    // OptionC
    // OptionD
    // Answer
    
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.isNull()) break;
        
        bool ok;
        int id = line.toInt(&ok);
        if (!ok) continue; // 跳过无效行

        Question q;
        q.id = id;
        q.content = in.readLine();
        q.optionA = in.readLine();
        q.optionB = in.readLine();
        q.optionC = in.readLine();
        q.optionD = in.readLine();
        q.answer = in.readLine();

        m_questions.append(q);
        if (id >= m_nextId) {
            m_nextId = id + 1;
        }
    }

    file.close();
    return true;
}

bool QuestionManager::saveQuestions(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filename;
        return false;
    }

    QTextStream out(&file);
    for (const Question& q : m_questions) {
        out << q.id << "\n";
        out << q.content << "\n";
        out << q.optionA << "\n";
        out << q.optionB << "\n";
        out << q.optionC << "\n";
        out << q.optionD << "\n";
        out << q.answer << "\n";
    }

    file.close();
    return true;
}

void QuestionManager::addQuestion(const Question& q) {
    Question newQ = q;
    // 自动分配ID
    newQ.id = m_nextId++;
    m_questions.append(newQ);
}

bool QuestionManager::deleteQuestion(int id) {
    for (int i = 0; i < m_questions.size(); ++i) {
        if (m_questions[i].id == id) {
            m_questions.removeAt(i);
            return true;
        }
    }
    return false;
}

bool QuestionManager::updateQuestion(int id, const Question& newQ) {
    for (int i = 0; i < m_questions.size(); ++i) {
        if (m_questions[i].id == id) {
            // 保持ID不变，更新内容
            Question updated = newQ;
            updated.id = id; 
            m_questions[i] = updated;
            return true;
        }
    }
    return false;
}

QVector<Question> QuestionManager::searchQuestions(const QString& keyword) {
    QVector<Question> result;
    for (const Question& q : m_questions) {
        if (q.content.contains(keyword, Qt::CaseInsensitive)) {
            result.append(q);
        }
    }
    return result;
}

QVector<Question> QuestionManager::generateExam(int n) {
    // 1. 如果题库是空的，直接返回空列表
    if (m_questions.isEmpty()) {
        return QVector<Question>();
    }

    // 2. 复制一份题库，用来打乱（不能打乱原题库 m_questions）
    QVector<Question> examQuestions = m_questions;

    // 3. 【核心修复】使用现代 C++ 标准方式进行随机打乱
    // 获取当前时间作为随机种子，保证每次运行结果不一样
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    // 使用默认随机引擎
    std::shuffle(examQuestions.begin(), examQuestions.end(), std::default_random_engine(seed));

    // 4. 截取前 n 道题
    if (n < examQuestions.size()) {
        examQuestions.resize(n);
    }

    return examQuestions;
}

bool QuestionManager::checkAnswer(int questionId, const QString& userAns) {
    for (const Question& q : m_questions) {
        if (q.id == questionId) {
            // 比较答案，忽略大小写和空白
            return q.answer.trimmed().toUpper() == userAns.trimmed().toUpper();
        }
    }
    return false;
}

const QVector<Question>& QuestionManager::getAllQuestions() const {
    return m_questions;
}

Question QuestionManager::getQuestionById(int id) {
    for (const Question& q : m_questions) {
        if (q.id == id) {
            return q;
        }
    }
    return Question(); // 返回空对象，ID通常为0或垃圾值，视初始化而定
}
