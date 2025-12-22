#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QuestionManager.h"
#include "ScoreManager.h"
#include <QDebug>
#include <QDir>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnUserLogin_clicked();
    void on_btnAdminLogin_clicked();
    void on_btnAdd_clicked();
    void on_btnDelete_clicked();
    void on_btnUpdate_clicked();
    void on_btnNext_clicked();
    void on_btnSubmit_clicked();
    void on_btnSearch_clicked();
    void on_listQuestions_currentRowChanged(int currentRow);
    void on_btnLogoutAdmin_clicked();
    void on_btnStats_clicked();               // 1. 从管理员页 -> 进成绩页
    void on_btnBackToAdmin_clicked();         // 2. 从成绩页 -> 回管理员页
    void on_btnRefresh_clicked();             // 3. 刷新表格数据
    void on_comboFilter_currentTextChanged(const QString &arg1); // 4. 下拉框筛选
    void on_btnModeMock_clicked();
    void on_btnModeFree_clicked();
    // 【新增】每秒更新时间的函数
    void updateTimer();
    void on_btnGenFree_clicked();

    // 【新增】模式下拉框变了，也要触发筛选
    void on_comboModeFilter_currentTextChanged(const QString &arg1);

    // 【新增】一个专门干活的函数，负责综合判断（既看人，又看模式）
    void filterTable();
private:
    void showQuestion(int index);
    void refreshQuestionList();

    Ui::MainWindow *ui;
    QuestionManager *m_questionManager;
    ScoreManager *m_scoreManager;

    // 考试状态
    QVector<Question> m_examQuestions;
    int m_currentExamIndex;
    QVector<QString> m_userAnswers;

    QTimer *m_timer;          // 计时器
    int m_remainingSeconds;   // 剩余秒数
    QString m_currentMode;    // 当前模式 ("模拟考试" 或 "自由训练")
    QString m_currentUserID;  // 记录当前登录的用户名 (saveScore时要用)
};
#endif // MAINWINDOW_H
