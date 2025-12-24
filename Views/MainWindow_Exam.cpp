#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QButtonGroup>

// ==================== 考试逻辑 ====================

void MainWindow::showQuestion(int index)
{
    if (index < 0 || index >= m_examQuestions.size()) return;

    const Question& q = m_examQuestions[index];

    // 更新题目索引显示
    if (ui->lblQuestionIndex) {
        ui->lblQuestionIndex->setText(QString("题目 %1 / %2").arg(index + 1).arg(m_examQuestions.size()));
    }

    ui->labelExamQuestion->setText(QString("%1. %2").arg(index + 1).arg(q.content));
    
    // 清除之前的选中状态
    // 必须先 setAutoExclusive(false) 才能取消选中，然后再设回 true
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

    // 恢复之前的答案
    if (index < m_userAnswers.size()) {
        QString savedAns = m_userAnswers[index];
        if (savedAns == "A") ui->radioA->setChecked(true);
        else if (savedAns == "B") ui->radioB->setChecked(true);
        else if (savedAns == "C") ui->radioC->setChecked(true);
        else if (savedAns == "D") ui->radioD->setChecked(true);
    }
    
    // 控制按钮状态
    ui->btnPrev->setEnabled(index > 0);
    ui->btnNext->setEnabled(index < m_examQuestions.size() - 1);
}

void MainWindow::on_btnPrev_clicked()
{
    // 保存当前题目的答案
    QString ans = "";
    if (ui->radioA->isChecked()) ans = "A";
    else if (ui->radioB->isChecked()) ans = "B";
    else if (ui->radioC->isChecked()) ans = "C";
    else if (ui->radioD->isChecked()) ans = "D";

    if (m_currentExamIndex < m_userAnswers.size()) {
        m_userAnswers[m_currentExamIndex] = ans;
    }

    // 进入上一题
    if (m_currentExamIndex > 0) {
        m_currentExamIndex--;
        showQuestion(m_currentExamIndex);
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
    int total = m_examQuestions.size();
    int correctCount = 0;

    for (int i = 0; i < total; ++i) {
        // 使用 QuestionManager 的 checkAnswer 逻辑，或者直接比对
        // 这里直接比对，因为我们有 Question 对象
        if (m_examQuestions[i].answer.trimmed().toUpper() == m_userAnswers[i].trimmed().toUpper()) {
            correctCount++;
        }
    }

    // 计算百分制分数
    int score = 0;
    if (total > 0) {
        score = (correctCount * 100) / total;
    }

    // 弹窗显示
    QString msg = QString("考试结束!\n用户 : %1\n分数 : %2 / 100\n正确率 : %3 / %4")
                      .arg(m_currentUserID)
                      .arg(score)
                      .arg(correctCount)
                      .arg(total);
    
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
    int n = EXAM_QUESTIONS_NUM; 
    
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
    ui->frameFreeSetup->show(); // 显示顶部输入栏！
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

    // 跳转进考场
    ui->stackedWidget->setCurrentIndex(3);
}

// 3. 自由训练模式下，点击“生成题目”
void MainWindow::on_btnGenFree_clicked()
{
    QString strNum = ui->inputFreeNum->text().trimmed();
    if (strNum.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入题目数量！");
        return;
    }

    // 获取输入的数字
    int n = strNum.toInt();
    if (n <= 0) {
        QMessageBox::warning(this, "提示", "题目数量必须大于0！");
        return;
    }

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

// 倒计时逻辑的具体实现
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
