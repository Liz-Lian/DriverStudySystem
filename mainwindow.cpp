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
    , m_currentExamIndex(0)
{
    ui->setupUi(this);

    // 【必须加】初始化计时器，不然 m_timer 是空指针！
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::updateTimer);


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
    refreshQuestionList();
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
    if (pwd == "123456") {
        ui->stackedWidget->setCurrentIndex(1); // 管理员页
        refreshQuestionList();
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
    m_examQuestions = m_questionManager->generateExam(10); // 生成10道题
    
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

// ==================== 管理员逻辑 ====================

void MainWindow::refreshQuestionList()
{
    ui->listQuestions->clear();
    const QVector<Question>& allQuestions = m_questionManager->getAllQuestions();
    for (const Question& q : allQuestions) {
        QListWidgetItem* item = new QListWidgetItem(QString("ID:%1 %2").arg(q.id).arg(q.content));
        // 将ID存储在Item的数据中，方便后续获取
        item->setData(Qt::UserRole, q.id);
        ui->listQuestions->addItem(item);
    }
}

void MainWindow::on_listQuestions_currentRowChanged(int currentRow)
{
    if (currentRow < 0) return;

    QListWidgetItem* item = ui->listQuestions->item(currentRow);
    int id = item->data(Qt::UserRole).toInt();

    Question q = m_questionManager->getQuestionById(id);
    
    // 填充到编辑框
    ui->editQuestion->setText(q.content);
    ui->editA->setText(q.optionA);
    ui->editB->setText(q.optionB);
    ui->editC->setText(q.optionC);
    ui->editD->setText(q.optionD);
    ui->editAnswer->setText(q.answer);
}

void MainWindow::on_btnAdd_clicked()
{
    Question q;
    q.content = ui->editQuestion->text();
    q.optionA = ui->editA->text();
    q.optionB = ui->editB->text();
    q.optionC = ui->editC->text();
    q.optionD = ui->editD->text();
    q.answer = ui->editAnswer->text().toUpper();

    if (q.content.isEmpty() || q.answer.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Content and Answer cannot be empty.");
        return;
    }

    m_questionManager->addQuestion(q);
    m_questionManager->saveQuestions("questions.txt"); // 保存到文件
    refreshQuestionList();
    QMessageBox::information(this, "Info", "Question added.");
}

void MainWindow::on_btnDelete_clicked()
{
    QListWidgetItem* item = ui->listQuestions->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Warning", "Please select a question to delete.");
        return;
    }

    int id = item->data(Qt::UserRole).toInt();
    if (m_questionManager->deleteQuestion(id)) {
        m_questionManager->saveQuestions("questions.txt");
        refreshQuestionList();
        // 清空输入框
        ui->editQuestion->clear();
        ui->editA->clear();
        ui->editB->clear();
        ui->editC->clear();
        ui->editD->clear();
        ui->editAnswer->clear();
        QMessageBox::information(this, "Info", "Question deleted.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete question.");
    }
}

void MainWindow::on_btnUpdate_clicked()
{
    QListWidgetItem* item = ui->listQuestions->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Warning", "Please select a question to update.");
        return;
    }

    int id = item->data(Qt::UserRole).toInt();
    
    Question q;
    q.id = id; // 保持ID不变
    q.content = ui->editQuestion->text();
    q.optionA = ui->editA->text();
    q.optionB = ui->editB->text();
    q.optionC = ui->editC->text();
    q.optionD = ui->editD->text();
    q.answer = ui->editAnswer->text().toUpper();

    if (m_questionManager->updateQuestion(id, q)) {
        m_questionManager->saveQuestions("questions.txt");
        refreshQuestionList();
        QMessageBox::information(this, "Info", "Question updated.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to update question.");
    }
}

void MainWindow::on_btnSearch_clicked()
{
    // 1. 获取搜索框的关键词
    QString keyword = ui->inputSearch->text();

    // 2. 调用 Manager 进行搜索
    QList<Question> results = m_questionManager->searchQuestions(keyword);

    // 3. 准备显示结果
    if (results.isEmpty()) {
        ui->textResult->setText("没有找到包含 \"" + keyword + "\" 的相关题目。");
        return;
    }

    QString displayText; // 用于存储最终拼接的长字符串

    // 4. 【核心修改】遍历结果，拼装详细信息
    for (const Question& q : results) {
        QString item = QString("================================\n"
                               "【题目ID】: %1\n"
                               "【题干】: %2\n\n"
                               "  A. %3\n"
                               "  B. %4\n"
                               "  C. %5\n"
                               "  D. %6\n\n"
                               "★ 标准答案: %7\n"
                               "================================\n\n")
                           .arg(q.id)
                           .arg(q.content)
                           .arg(q.optionA)
                           .arg(q.optionB)
                           .arg(q.optionC)
                           .arg(q.optionD)
                           .arg(q.answer);

        displayText.append(item);
    }

    // 5. 显示到界面上
    ui->textResult->setText(displayText);
}

// 退出登录按钮 (对应 Page 1 的 btnLogoutAdmin)
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
    m_userAnswers[m_currentExamIndex] = ans;

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
    
    QMessageBox::information(this, "Result", msg);

    // 保存成绩
    m_scoreManager->saveScore(m_currentUserID, score, m_currentMode);

    // 返回登录页或重置
    ui->stackedWidget->setCurrentIndex(0);
    ui->inputUserID->clear();
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
    on_btnRefresh_clicked();
}

// 2. 【跳转】点击“返回管理页”
void MainWindow::on_btnBackToAdmin_clicked()
{
    // 跳回第 1 页 (管理员试题页)
    ui->stackedWidget->setCurrentIndex(1);
}

// 3. 【核心】刷新表格数据
void MainWindow::on_btnRefresh_clicked()
{
    // (1) 问 ScoreManager 要所有数据
    QList<ExamRecord> records = m_scoreManager->getAllRecords();

    // (2) 准备表格
    ui->tableScores->setRowCount(0); // 先把旧的全删了
    ui->tableScores->setRowCount(records.size()); // 设置新行数

    // 准备一个列表，用来存所有考生的名字（给下拉框用）
    QStringList userList;
    userList << "全部用户"; // 默认第一项

    // 开始填表格
    for (int i = 0; i < records.size(); ++i) {
        const ExamRecord& r = records[i];

        // 【重点】在这里调整顺序！
        // 虽然 r 里面存数据的顺序没变，但是我们可以决定把它往哪个格子里塞

        // 你想让“模式”在第1列 (索引0)
        ui->tableScores->setItem(i, 0, new QTableWidgetItem(r.mode));

        // 你想让“用户名”在第2列 (索引1)
        ui->tableScores->setItem(i, 1, new QTableWidgetItem(r.userID));

        // 你想让“分数”在第3列 (索引2)
        ui->tableScores->setItem(i, 2, new QTableWidgetItem(QString::number(r.score)));

        // 你想让“时间”在第4列 (索引3)
        ui->tableScores->setItem(i, 3, new QTableWidgetItem(r.time));

        // 3. 【关键】在循环里收集名字
        if (!userList.contains(r.userID)) {
            userList.append(r.userID);
        }
    }

    // --- 更新【用户】下拉框 ---
    ui->comboFilter->blockSignals(true);
    ui->comboFilter->clear();
    ui->comboFilter->addItems(userList);
    ui->comboFilter->blockSignals(false);

    // --- 更新【模式】下拉框 (新增) ---
    // 这里我们直接手动加这3个固定的选项就行
    ui->comboModeFilter->blockSignals(true);
    ui->comboModeFilter->clear();
    ui->comboModeFilter->addItem("全部模式"); // 默认项
    ui->comboModeFilter->addItem("模拟考试");
    ui->comboModeFilter->addItem("自由训练");
    ui->comboModeFilter->blockSignals(false);
}
// =========================================================
//  新版：多重筛选逻辑
// =========================================================

// 1. 用户下拉框变了 -> 比如选了 "XiaoLian"
void MainWindow::on_comboFilter_currentTextChanged(const QString &arg1)
{
    filterTable(); // 只有一句：去调用通用的筛选函数
}

// 2. 模式下拉框变了 -> 比如选了 "模拟考试"
void MainWindow::on_comboModeFilter_currentTextChanged(const QString &arg1)
{
    filterTable(); // 只有一句：去调用通用的筛选函数
}

// 3. 【核心】真正的干活函数：双重筛选
void MainWindow::filterTable()
{
    // 获取两个下拉框当前选中的文字
    QString userTarget = ui->comboFilter->currentText();     // 选中的人
    QString modeTarget = ui->comboModeFilter->currentText(); // 选中的模式

    // 获取表格总行数
    int rowCount = ui->tableScores->rowCount();

    for (int i = 0; i < rowCount; ++i) {
        // 获取这一行的信息 (注意你的列顺序！)
        // 第0列：模式 | 第1列：用户
        QString modeInRow = ui->tableScores->item(i, 0)->text();
        QString userInRow = ui->tableScores->item(i, 1)->text();

        // 判断1：用户是否匹配？ (选了"全部" 或者 名字一样)
        bool matchUser = (userTarget == "全部用户") || (userInRow == userTarget);

        // 判断2：模式是否匹配？ (选了"全部" 或者 模式一样)
        // 注意：如果你代码里初始化的选项叫 "全部模式"，这里就要对应写 "全部模式"
        bool matchMode = (modeTarget == "全部模式") || (modeInRow == modeTarget);

        // 最终决定：必须两个都满足，才显示
        if (matchUser && matchMode) {
            ui->tableScores->showRow(i);
        } else {
            ui->tableScores->hideRow(i);
        }
    }
}

// 1. 点击“模拟考试”
void MainWindow::on_btnModeMock_clicked()
{
    // 记录模式
    m_currentMode = "模拟考试";

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
    m_remainingSeconds = 45 * 60; // 45分钟

    // 生成试卷 & 跳转
    if (!m_questionManager->generateExam(n).isEmpty()) {
        ui->stackedWidget->setCurrentIndex(3); // 进考场
        showQuestion(0);

        // 启动计时器
        m_timer->start(1000);
        updateTimer();
    }
}

// 2. 点击“自由训练”
void MainWindow::on_btnModeFree_clicked()
{
    // 记录模式
    m_currentMode = "自由训练";

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

    // 生成试卷
    if (!m_questionManager->generateExam(n).isEmpty()) {
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

// 【新增】倒计时逻辑的具体实现
void MainWindow::updateTimer()
{
    m_remainingSeconds--;

    // 把秒数转换成 "分:秒" 的格式
    int min = m_remainingSeconds / 60;
    int sec = m_remainingSeconds % 60;

    // 格式化字符串，例如 "44:59"
    QString timeStr = QString("%1:%2")
                          .arg(min, 2, 10, QChar('0'))
                          .arg(sec, 2, 10, QChar('0'));

    // 显示到界面上的 LCD 数字屏
    ui->lcdTimer->display(timeStr);

    // 如果时间到了
    if (m_remainingSeconds <= 0) {
        m_timer->stop();
        QMessageBox::warning(this, "时间到", "考试时间结束，系统将自动交卷！");
        on_btnSubmit_clicked(); // 强制调用交卷
    }
}
