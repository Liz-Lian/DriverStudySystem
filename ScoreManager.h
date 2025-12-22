#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <QString>
#include <QList>
#include <QDateTime>

// 定义一个结构体，用来存每一条“成绩单”
struct ExamRecord {
    QString userID;
    int score;
    QString time; // 新增：考试时间
    QString mode; // 【新增】考试模式
};

struct ScoreStats {
    int totalExams;
    int maxScore;
    double averageScore;
};

class ScoreManager {
public:
    ScoreManager();

    // 保存考试记录到文件
    bool saveScore(const QString& userID, int score, const QString& mode);

    // 【新增】获取所有的详细记录，给表格用
    QList<ExamRecord> getAllRecords();

    // 读取所有成绩，计算平均分、最高分，返回统计结果
    ScoreStats getStats();

private:
    QString m_filename;
};

#endif // SCOREMANAGER_H
