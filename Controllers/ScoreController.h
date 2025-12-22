#ifndef SCORECONTROLLER_H
#define SCORECONTROLLER_H

#include <QObject>
#include <QTableWidget>
#include <QComboBox>
#include "ScoreManager.h"

class ScoreController : public QObject
{
    Q_OBJECT
public:
    explicit ScoreController(ScoreManager* sm, QObject *parent = nullptr);

    void setUiComponents(QTableWidget* table, QComboBox* comboUser, QComboBox* comboMode);

    // 刷新数据
    void refreshTable();

public slots:
    // 筛选
    void filterTable();

private:
    ScoreManager* m_scoreManager;
    
    QTableWidget* m_tableScores;
    QComboBox* m_comboFilter;
    QComboBox* m_comboModeFilter;
};

#endif // SCORECONTROLLER_H
