#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QuestionManager.h"
#include "ScoreManager.h"
#include "GlobalTypes.h"
#include "ExamController.h"
#include "AdminController.h"
#include "ScoreController.h"
#include "ReviewController.h"
#include <QDebug>
#include <QDir>

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
    // 登录相关
    void on_btnUserLogin_clicked();
    void on_btnAdminLogin_clicked();
    void on_btnLogoutAdmin_clicked();

    // 页面跳转相关
    void on_btnStats_clicked();               
    void on_btnBackToAdmin_clicked();         

    // 考试模式选择
    void on_btnModeMock_clicked();
    void on_btnModeFree_clicked();
    void on_btnGenFree_clicked();
    
    // 考试过程
    void on_btnNext_clicked();
    void on_btnSubmit_clicked();
    // 【新增】返回和退出
    void on_btnReturnToMode_clicked();
    void on_btnLogout_clicked();

    // 【新增】错题回顾
    void on_btnNextWrong_clicked();
    void on_btnExitWrong_clicked();
    
    // 来自 Controller 的信号槽
    void onTimerUpdated(QString timeStr);

private:
    void showWrongQuestion(int index); // 【新增】显示错题
    void showQuestion(int index);
    void onExamFinished();

    Ui::MainWindow *ui;
    
    // Managers
    QuestionManager *m_questionManager;
    ScoreManager *m_scoreManager;
    
    // Controllers
    ExamController *m_examController;
    AdminController *m_adminController;
    ScoreController *m_scoreController;
    ReviewController *m_reviewController; // 【新增】

    // 考试状态
    QVector<Question> m_examQuestions;
    int m_currentExamIndex;
    QVector<QString> m_userAnswers;

    // 错题回顾状态
    int m_currentWrongIndex;

    QString m_currentUserID;
};
#endif // MAINWINDOW_H
