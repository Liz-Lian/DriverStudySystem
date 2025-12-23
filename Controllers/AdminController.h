#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H

#include <QObject>
#include <QListWidget>
#include <QLineEdit>
#include <QTextBrowser>
#include <QTextEdit>
#include "QuestionManager.h"

class AdminController : public QObject
{
    Q_OBJECT
public:
    explicit AdminController(QuestionManager* qm, QObject *parent = nullptr);

    // 设置需要操作的 UI 控件
    void setUiComponents(QListWidget* list, 
                         QTextEdit* inputQ, QLineEdit* inputA, QLineEdit* inputB, 
                         QLineEdit* inputC, QLineEdit* inputD, QLineEdit* inputAns,
                         QLineEdit* inputSearch, QTextBrowser* textResult);

    // 刷新列表
    void refreshQuestionList();

public slots:
    void onAddClicked();
    void onDeleteClicked();
    void onUpdateClicked();
    void onSearchClicked();
    void onListRowChanged(int currentRow);

private:
    QuestionManager* m_questionManager;
    
    // UI 指针
    QListWidget* m_listQuestions;
    QTextEdit* m_editQuestion;
    QLineEdit* m_editA;
    QLineEdit* m_editB;
    QLineEdit* m_editC;
    QLineEdit* m_editD;
    QLineEdit* m_editAnswer;
    QLineEdit* m_inputSearch;
    QTextBrowser* m_textResult;
};

#endif // ADMINCONTROLLER_H
