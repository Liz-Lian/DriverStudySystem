#include "ScoreManager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>

ScoreManager::ScoreManager() {
    // 自动找到构建目录下的 scores.txt
    m_filename = QCoreApplication::applicationDirPath() + "/scores.txt";
}

bool ScoreManager::saveScore(const QString& userID, int score, const QString& mode) {
    QFile file(m_filename);
    if (!file.open(QIODevice::Append | QIODevice::Text)) return false;

    QTextStream out(&file);
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH:mm:ss");

    // 格式：用户名 分数 时间 模式
    // 注意：用空格隔开，如果模式里有空格(比如"模拟 考试")会出错，所以我们要在代码里写死成 "模拟考试" 或 "自由训练"
    out << userID << " " << score << " " << currentTime << " " << mode << "\n";
    file.close();
    return true;
}

// 2. 修改读取函数 (getAllRecords)
QList<ExamRecord> ScoreManager::getAllRecords() {
    QList<ExamRecord> records;
    QFile file(m_filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return records;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" ", Qt::SkipEmptyParts);

        // 【修改】现在我们要判断是否有至少 4 部分（原来的3部分 + 模式）
        if (parts.size() >= 4) {
            ExamRecord record;
            record.userID = parts[0];
            record.score = parts[1].toInt();
            record.time = parts[2].replace("_", " "); // 把下划线换回空格
            record.mode = parts[3];                   // 【新增】读取模式
            records.append(record);
        }
    }
    file.close();
    return records;
}

ScoreStats ScoreManager::getStats() {
    // 简便写法：复用上面的 getAllRecords
    const QList<ExamRecord> all = getAllRecords();
    ScoreStats stats = {0, 0, 0.0};

    if (all.isEmpty()) return stats;

    stats.totalExams = all.size();
    long long totalScore = 0; // 防止溢出
    for(const auto& r : all) {
        if(r.score > stats.maxScore) stats.maxScore = r.score;
        totalScore += r.score;
    }
    stats.averageScore = (double)totalScore / stats.totalExams;
    return stats;
}
