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
    m_adminController->setUiComponents(ui->listQuestions, 
                                       ui->editQuestion, ui->editA, ui->editB, 
                                       ui->editC, ui->editD, ui->editAnswer,
                                       ui->inputSearch, ui->textResult);

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

    // 让程序把当前的工作目录打印出来！
    qDebug() << "=============================================";
    qDebug() << "【现在的家】文件都存在这里：" << QDir::currentPath();
    qDebug() << "=============================================";

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
    // Controllers are children of MainWindow, so they will be deleted automatically
    delete ui;
}

// ==================== 登录逻辑 ====================

void MainWindow::on_btnAdminLogin_clicked()
{
    QString pwd = ui->inputAdminPwd->text();
    if (pwd == "123456") {
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
    
    // 使用 Controller 开始考试 (默认模拟考试，10题)
    m_examController->startExam(10, ExamMode::MockExam);
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

// ==================== 考试逻辑 ====================

void MainWindow::showQuestion(int index)
{
    if (index < 0 || index >= m_examQuestions.size()) return;

    const Question& q = m_examQuestions[index];

    ui->labelExamQuestion->setText(QString("Question %1: %2").arg(index + 1).arg(q.content));
    
    // 清除之前的选中状态
    // 必须先 setAutoExclusive(false) 才能取消选中，然后再设回 true
    QButtonGroup* bg = new QButtonGroup(this); // 临时组或者直接操作
    // 这里假设 UI 设计中 radioA...radioD 没有被显式放入 QButtonGroup，
    // 它们通常是自动互斥的（如果父组件相同）。
    // 为了安全起见，手动处理：
    ui->radioA->setAutoExclusive(false);
    ui->radioB->setAutoExclusive(false);
    ui->radioC->setAutoExclusive(false);
    ui->radioD->setAutoExclusive(false);

    ui->radioA->setChecked(false);
    ui->radioB->setChecked(false);
    ui->radioC->setChecked(false);
    ui->radioD->setChecked(false);

    ui->radioA->setAutoExclusive(true);
    ui->radioB->setAutoExclusive(true);
    ui->radioC->setAutoExclusive(true);
    ui->radioD->setAutoExclusive(true);

    ui->radioA->setText("A. " + q.optionA);
    ui->radioB->setText("B. " + q.optionB);
    ui->radioC->setText("C. " + q.optionC);
    ui->radioD->setText("D. " + q.optionD);

    // 如果用户之前回答过这道题（比如实现了“上一题”功能），这里可以恢复选中状态
    // 但当前需求只有“下一题”，所以通常是空的。
    
    // 控制 Next 按钮状态
    if (index == m_examQuestions.size() - 1) {
        ui->btnNext->setEnabled(false);
    } else {
        ui->btnNext->setEnabled(true);
    }
}

void MainWindow::on_btnNext_clicked()
{
    // 保存当前题目的答案
    QString ans = "";
    if (ui->radioA->isChecked()) ans = "A";
    else if (ui->radioB->isChecked()) ans = "B";
    else if (ui->radioC->isChecked()) ans = "C";
    else if (ui->radioD->isChecked()) ans = "D";

    m_userAnswers[m_currentExamIndex] = ans;

    // 进入下一题
    m_currentExamIndex++;
    if (m_currentExamIndex < m_examQuestions.size()) {
        showQuestion(m_currentExamIndex);
    }
}

void MainWindow::on_btnSubmit_clicked()
{
    // 保存最后一题（或当前题）的答案
    QString ans = "";
    if (ui->radioA->isChecked()) ans = "A";
    else if (ui->radioB->isChecked()) ans = "B";
    else if (ui->radioC->isChecked()) ans = "C";
    else if (ui->radioD->isChecked()) ans = "D";
    
    // 只有当当前题目答案未被记录时才记录（防止覆盖）
    // 其实直接覆盖也没问题，因为这是当前显示题目的最新状态
    if (m_currentExamIndex < m_userAnswers.size()) {
        m_userAnswers[m_currentExamIndex] = ans;
    }

    // 计算分数
    int score = 0;
    int total = m_examQuestions.size();
    int correctCount = 0;

    for (int i = 0; i < total; ++i) {
        // 使用 QuestionManager 的 checkAnswer 逻辑，或者直接比对
        // 这里直接比对，因为我们有 Question 对象
        if (m_examQuestions[i].answer.trimmed().toUpper() == m_userAnswers[i].trimmed().toUpper()) {
            score += 10; // 假设每题10分
            correctCount++;
        }
    }

    // 弹窗显示
    QString msg = QString("Exam Finished!\nUser: %1\nScore: %2 / %3\nCorrect: %4")
                      .arg(m_currentUserID)
                      .arg(score)
                      .arg(total * 10)
                      .arg(correctCount);
    
    // 准备错题数据
    int wrongCount = m_reviewController->prepareReview(m_examQuestions, m_userAnswers);

    // 停止考试计时
    m_examController->stopExam();

    // 保存成绩
    QString modeStr = (m_examController->getCurrentMode() == ExamMode::MockExam) ? "模拟考试" : "自由训练";
    m_scoreManager->saveScore(m_currentUserID, score, modeStr);

    // 构造弹窗
    QMessageBox msgBox;
    msgBox.setWindowTitle("Result");
    msgBox.setText(msg);
    
    QPushButton *btnOK = msgBox.addButton("确定", QMessageBox::AcceptRole);
    QPushButton *btnReview = nullptr;
    
    if (wrongCount > 0) {
        btnReview = msgBox.addButton("查看错题", QMessageBox::ActionRole);
    }

    msgBox.exec();

    if (msgBox.clickedButton() == btnReview) {
        // 跳转到错题回顾页 (Page 5)
        ui->stackedWidget->setCurrentIndex(5);
        m_currentWrongIndex = 0;
        showWrongQuestion(0);
    } else {
        // 返回登录页或重置
        ui->stackedWidget->setCurrentIndex(0);
        ui->inputUserID->clear();
    }
}

// ==================== 错题回顾逻辑 ====================

void MainWindow::showWrongQuestion(int index)
{
    if (index < 0 || index >= m_reviewController->getWrongCount()) return;

    Question q = m_reviewController->getWrongQuestions()[index];
    QString userAns = m_reviewController->getWrongUserAnswer(index);
    QString correctAns = q.answer.trimmed().toUpper();

    // 显示题目
    ui->lblWrongQuestion->setText(QString("错题 %1: %2").arg(index + 1).arg(q.content));

    // 显示选项文本
    ui->radioWrongA->setText("A. " + q.optionA);
    ui->radioWrongB->setText("B. " + q.optionB);
    ui->radioWrongC->setText("C. " + q.optionC);
    ui->radioWrongD->setText("D. " + q.optionD);

    // 1. 重置样式
    ui->radioWrongA->setStyleSheet("");
    ui->radioWrongB->setStyleSheet("");
    ui->radioWrongC->setStyleSheet("");
    ui->radioWrongD->setStyleSheet("");

    // 2. 标红（用户错选）
    if (userAns == "A") ui->radioWrongA->setStyleSheet("color: red; font-weight: bold; font-size: 14px;");
    else if (userAns == "B") ui->radioWrongB->setStyleSheet("color: red; font-weight: bold; font-size: 14px;");
    else if (userAns == "C") ui->radioWrongC->setStyleSheet("color: red; font-weight: bold; font-size: 14px;");
    else if (userAns == "D") ui->radioWrongD->setStyleSheet("color: red; font-weight: bold; font-size: 14px;");

    // 3. 标绿（正确答案）
    if (correctAns == "A") ui->radioWrongA->setStyleSheet("color: green; font-weight: bold; font-size: 14px;");
    else if (correctAns == "B") ui->radioWrongB->setStyleSheet("color: green; font-weight: bold; font-size: 14px;");
    else if (correctAns == "C") ui->radioWrongC->setStyleSheet("color: green; font-weight: bold; font-size: 14px;");
    else if (correctAns == "D") ui->radioWrongD->setStyleSheet("color: green; font-weight: bold; font-size: 14px;");

    // 4. 底部显示正确答案
    ui->lblCorrectAnswer->setText("正确答案：" + correctAns);

    // 控制按钮状态
    if (index == m_reviewController->getWrongCount() - 1) {
        ui->btnNextWrong->setEnabled(false);
        ui->btnNextWrong->setText("已是最后一道");
    } else {
        ui->btnNextWrong->setEnabled(true);
        ui->btnNextWrong->setText("下一题");
    }
}

void MainWindow::on_btnNextWrong_clicked()
{
    m_currentWrongIndex++;
    if (m_currentWrongIndex < m_reviewController->getWrongCount()) {
        showWrongQuestion(m_currentWrongIndex);
    }
}

void MainWindow::on_btnExitWrong_clicked()
{
    // 退出错题回顾，返回模式选择页 (Page 4)
    ui->stackedWidget->setCurrentIndex(4);
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

// ==================== 考试模式选择逻辑 ====================

// 1. 点击“模拟考试”
void MainWindow::on_btnModeMock_clicked()
{
    // 界面调整：
    ui->frameFreeSetup->hide(); // 隐藏自由训练的输入框
    ui->lcdTimer->show();       // 显示倒计时器

    // 【新增】模拟考试进场必须直接显示选项！
    ui->radioA->show();
    ui->radioB->show();
    ui->radioC->show();
    ui->radioD->show();
    ui->btnNext->show();
    ui->btnSubmit->show();

    // 1. 强制切回到第0页("在线考试"页)，防止用户正停留在知识查询页被锁死
    ui->tabWidget->setCurrentIndex(0);

    // 2. 把第1页("知识查询"页) 禁用掉！变灰不可点！
    ui->tabWidget->setTabEnabled(1, false);
    // (如果知识查询是第1个标签，就把1改成0；通常它是第2个，所以是1)

    // 逻辑设定：
    int n = 5; // 暂时先设5道题测试，之后改成100
    
    // 使用 Controller 开始考试
    m_examController->startExam(n, ExamMode::MockExam);
    m_examQuestions = m_examController->getExamQuestions();

    // 生成试卷 & 跳转
    if (!m_examQuestions.isEmpty()) {
        // 初始化用户答案
        m_userAnswers.clear();
        m_userAnswers.resize(m_examQuestions.size());
        m_currentExamIndex = 0;

        ui->stackedWidget->setCurrentIndex(3); // 进考场
        showQuestion(0);
    }
}

// 2. 点击“自由训练”
void MainWindow::on_btnModeFree_clicked()
{
    // 允许点击"知识查询"标签
    ui->tabWidget->setTabEnabled(1, true);

    // 界面调整：
    ui->frameFreeSetup->show(); // 【关键】显示顶部输入栏！
    ui->lcdTimer->hide();       // 隐藏倒计时器
    ui->radioA->hide();
    ui->radioB->hide();
    ui->radioC->hide();
    ui->radioD->hide();
    ui->btnNext->hide();
    ui->btnSubmit->hide();

    // 清空考场：先不生成题目，给个空白或者提示
    ui->labelExamQuestion->setText("请在上方输入题目数量，点击生成开始训练。");
    // 把选项都隐藏或者清空，防止误触 (这里简单处理，不清空也没事，反正没生成题)

    // 直接进考场
    ui->stackedWidget->setCurrentIndex(3);
}

// 3. 自由训练模式下，点击“生成题目”
void MainWindow::on_btnGenFree_clicked()
{
    // 获取输入的数字
    int n = ui->inputFreeNum->text().toInt();
    if (n <= 0) n = 5; // 默认值

    // 使用 Controller 开始考试
    m_examController->startExam(n, ExamMode::FreeTraining);
    m_examQuestions = m_examController->getExamQuestions();

    // 生成试卷
    if (!m_examQuestions.isEmpty()) {
        // 初始化用户答案
        m_userAnswers.clear();
        m_userAnswers.resize(m_examQuestions.size());
        m_currentExamIndex = 0;

        ui->radioA->show();
        ui->radioB->show();
        ui->radioC->show();
        ui->radioD->show();
        ui->btnNext->show();
        ui->btnSubmit->show();

        showQuestion(0); // 显示第1题
        QMessageBox::information(this, "开始", QString("已为您生成 %1 道训练题！").arg(n));
    } else {
        QMessageBox::warning(this, "错误", "题目生成失败，题库可能为空。");
    }
}

// ==================== 返回与退出逻辑 ====================

void MainWindow::on_btnReturnToMode_clicked()
{
    // 1. 停止考试 (停止计时器)
    m_examController->stopExam();

    // 2. 清理界面状态 (可选)
    ui->labelExamQuestion->clear();
    ui->radioA->setChecked(false);
    ui->radioB->setChecked(false);
    ui->radioC->setChecked(false);
    ui->radioD->setChecked(false);
    ui->lcdTimer->display("00:00");

    // 3. 跳转回模式选择页 (Page 4)
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_btnLogout_clicked()
{
    // 1. 停止考试
    m_examController->stopExam();

    // 2. 清理用户状态
    m_currentUserID.clear();
    ui->inputUserID->clear();

    // 3. 清理界面状态
    ui->labelExamQuestion->clear();
    ui->lcdTimer->display("00:00");

    // 4. 跳转回登录页 (Page 0)
    ui->stackedWidget->setCurrentIndex(0);
}

// 【新增】倒计时逻辑的具体实现
void MainWindow::onTimerUpdated(QString timeStr)
{
    // 显示到界面上的 LCD 数字屏
    ui->lcdTimer->display(timeStr);
}

void MainWindow::onExamFinished()
{
    QMessageBox::warning(this, "时间到", "考试时间结束，系统将自动交卷！");
    on_btnSubmit_clicked(); // 强制调用交卷
}
