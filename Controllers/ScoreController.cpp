#include "ScoreController.h"
#include <QTableWidgetItem>

ScoreController::ScoreController(ScoreManager* sm, QObject *parent)
    : QObject(parent)
    , m_scoreManager(sm)
    , m_tableScores(nullptr)
{
}

void ScoreController::setUiComponents(QTableWidget* table, QComboBox* comboUser, QComboBox* comboMode)
{
    m_tableScores = table;
    m_comboFilter = comboUser;
    m_comboModeFilter = comboMode;
}

void ScoreController::refreshTable()
{
    if (!m_tableScores) return;

    QList<ExamRecord> records = m_scoreManager->getAllRecords();

    m_tableScores->setRowCount(0);
    m_tableScores->setRowCount(records.size());

    QStringList userList;
    userList << "全部用户";

    for (int i = 0; i < records.size(); ++i) {
        const ExamRecord& r = records[i];

        m_tableScores->setItem(i, 0, new QTableWidgetItem(r.mode));
        m_tableScores->setItem(i, 1, new QTableWidgetItem(r.userID));
        m_tableScores->setItem(i, 2, new QTableWidgetItem(QString::number(r.score)));
        m_tableScores->setItem(i, 3, new QTableWidgetItem(r.time));

        if (!userList.contains(r.userID)) {
            userList.append(r.userID);
        }
    }

    // 更新下拉框
    if (m_comboFilter) {
        m_comboFilter->blockSignals(true);
        m_comboFilter->clear();
        m_comboFilter->addItems(userList);
        m_comboFilter->blockSignals(false);
    }

    if (m_comboModeFilter) {
        m_comboModeFilter->blockSignals(true);
        m_comboModeFilter->clear();
        m_comboModeFilter->addItem("全部模式");
        m_comboModeFilter->addItem("模拟考试");
        m_comboModeFilter->addItem("自由训练");
        m_comboModeFilter->blockSignals(false);
    }
}

void ScoreController::filterTable()
{
    if (!m_tableScores || !m_comboFilter || !m_comboModeFilter) return;

    QString userTarget = m_comboFilter->currentText();
    QString modeTarget = m_comboModeFilter->currentText();

    int rowCount = m_tableScores->rowCount();

    for (int i = 0; i < rowCount; ++i) {
        QString modeInRow = m_tableScores->item(i, 0)->text();
        QString userInRow = m_tableScores->item(i, 1)->text();

        bool matchUser = (userTarget == "全部用户") || (userInRow == userTarget);
        bool matchMode = (modeTarget == "全部模式") || (modeInRow == modeTarget);

        if (matchUser && matchMode) {
            m_tableScores->showRow(i);
        } else {
            m_tableScores->hideRow(i);
        }
    }
}
