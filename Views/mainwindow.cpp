#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QButtonGroup>
#include <QTableWidgetItem>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_questionManager(new QuestionManager())
    , m_scoreManager(new ScoreManager())
    , m_examController(new ExamController(m_questionManager, this))
    , m_adminController(new AdminController(m_questionManager, this))
    , m_scoreController(new ScoreController(m_scoreManager, this))
    , m_reviewController(new ReviewController(this))
    , m_currentExamIndex(0)
    , m_currentWrongIndex(0)
{
    ui->setupUi(this);

    // 1. 初始化 AdminController
    m_adminController->setUiComponents(
        ui->listQuestions, 
        ui->editQuestion, ui->editA, ui->editB, 
        ui->editC, ui->editD, ui->editAnswer,
        ui->inputSearch, ui->textResult
    );

    // 连接 Admin 信号槽
    connect(ui->btnAdd, &QPushButton::clicked, m_adminController, &AdminController::onAddClicked);
    connect(ui->btnDelete, &QPushButton::clicked, m_adminController, &AdminController::onDeleteClicked);
    connect(ui->btnUpdate, &QPushButton::clicked, m_adminController, &AdminController::onUpdateClicked);
    connect(ui->btnSearch, &QPushButton::clicked, m_adminController, &AdminController::onSearchClicked);
    connect(ui->listQuestions, &QListWidget::currentRowChanged, m_adminController, &AdminController::onListRowChanged);

    // 2. 初始化 ScoreController
    m_scoreController->setUiComponents(ui->tableScores, ui->comboFilter, ui->comboModeFilter);

    // 连接 Score 信号槽
    connect(ui->btnRefresh, &QPushButton::clicked, m_scoreController, &ScoreController::refreshTable);
    connect(ui->comboFilter, &QComboBox::currentTextChanged, m_scoreController, &ScoreController::filterTable);
    connect(ui->comboModeFilter, &QComboBox::currentTextChanged, m_scoreController, &ScoreController::filterTable);

    // 3. 连接 ExamController 信号
    connect(m_examController, &ExamController::sigTimerUpdated, this, &MainWindow::onTimerUpdated);
    connect(m_examController, &ExamController::sigExamFinished, this, &MainWindow::onExamFinished);


    // 加载题库
    if (!m_questionManager->loadQuestions("questions.txt")) {
        QMessageBox::warning(this, "Warning", "Failed to load questions.txt");
    }

    // 初始化界面
    ui->stackedWidget->setCurrentIndex(0); // 登录页
    m_adminController->refreshQuestionList();
}

MainWindow::~MainWindow()
{
    delete m_questionManager;
    delete m_scoreManager;
    delete ui;
}

// ==================== 登录逻辑 ====================

void MainWindow::on_btnAdminLogin_clicked()
{
    QString pwd = ui->inputAdminPwd->text();
    if (pwd == ADMIN_PASSWORD) {
        ui->stackedWidget->setCurrentIndex(1); // 管理员页
        m_adminController->refreshQuestionList();
    } else {
        QMessageBox::critical(this, "Error", "Incorrect Password!");
    }
}

void MainWindow::on_btnUserLogin_clicked()
{
    QString userId = ui->inputUserID->text().trimmed();
    if (userId.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter User ID.");
        return;
    }

    m_currentUserID = userId;
    
    // 使用 Controller 开始考试 (模拟考试模式,题目数量和时间在常量中定义)
    m_examController->startExam(EXAM_QUESTIONS_NUM, ExamMode::MockExam, EXAM_TIME_LIMIT_SECONDS);
    m_examQuestions = m_examController->getExamQuestions();
    
    if (m_examQuestions.isEmpty()) {
        QMessageBox::warning(this, "Warning", "No questions available in the database.");
        return;
    }

    // 初始化考试状态
    m_currentExamIndex = 0;
    m_userAnswers.clear();
    m_userAnswers.resize(m_examQuestions.size()); // 预分配空间

    ui->stackedWidget->setCurrentIndex(4); // 考试页
    showQuestion(0);
}

void MainWindow::on_btnLogoutAdmin_clicked()
{
    // 切换回第 0 页 (登录页)
    ui->stackedWidget->setCurrentIndex(0);

    // 可选：清空一下输入框，防止下次进来还有密码
    ui->inputAdminPwd->clear();
}

// ========================================================
//                  Page 3: 成绩管理逻辑
// ========================================================

// 1. 【跳转】管理员点击“进入成绩管理”
void MainWindow::on_btnStats_clicked()
{
    // 跳转到第 3 页 (成绩页)
    ui->stackedWidget->setCurrentIndex(2);

    // 顺便自动点一下刷新，把数据加载出来
    m_scoreController->refreshTable();
}

// 2. 【跳转】点击“返回管理页”
void MainWindow::on_btnBackToAdmin_clicked()
{
    // 跳回第 1 页 (管理员试题页)
    ui->stackedWidget->setCurrentIndex(1);
}

