#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

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
