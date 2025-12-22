#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QuestionManager.h"
#include "ScoreManager.h"
#include "GlobalTypes.h"
#include "ExamController.h"
#include "AdminController.h"
#include "ScoreController.h"
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
    
    // 来自 Controller 的信号槽
    void onTimerUpdated(QString timeStr);
    void onExamFinished();

private:
    void showQuestion(int index);
    // refreshQuestionList 移到了 AdminController
    // filterTable 移到了 ScoreController

    Ui::MainWindow *ui;
    
    // Managers
    QuestionManager *m_questionManager;
    ScoreManager *m_scoreManager;
    
    // Controllers
    ExamController *m_examController;
    AdminController *m_adminController; // 新增
    ScoreController *m_scoreController; // 新增

    // 考试状态
    QVector<Question> m_examQuestions;
    int m_currentExamIndex;
    QVector<QString> m_userAnswers;

    QString m_currentUserID;
};
#endif // MAINWINDOW_H
