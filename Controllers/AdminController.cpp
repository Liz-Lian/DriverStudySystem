#include "AdminController.h"
#include <QMessageBox>
#include <QListWidgetItem>

AdminController::AdminController(QuestionManager* qm, QObject *parent)
    : QObject(parent)
    , m_questionManager(qm)
    , m_listQuestions(nullptr)
{
}

void AdminController::setUiComponents(
   QListWidget* list, 
   QTextEdit* inputQ, QLineEdit* inputA, QLineEdit* inputB, 
   QLineEdit* inputC, QLineEdit* inputD, QLineEdit* inputAns,
   QLineEdit* inputSearch, QTextBrowser* textResult
   )
{
    m_listQuestions = list;
    m_editQuestion = inputQ;
    m_editA = inputA;
    m_editB = inputB;
    m_editC = inputC;
    m_editD = inputD;
    m_editAnswer = inputAns;
    m_inputSearch = inputSearch;
    m_textResult = textResult;

    // 设置 Placeholder (占位符提示文本)
    if (m_editQuestion) m_editQuestion->setPlaceholderText("请输入题目内容...");
    if (m_editA) m_editA->setPlaceholderText("请输入选项 A...");
    if (m_editB) m_editB->setPlaceholderText("请输入选项 B...");
    if (m_editC) m_editC->setPlaceholderText("请输入选项 C...");
    if (m_editD) m_editD->setPlaceholderText("请输入选项 D...");
    if (m_editAnswer) m_editAnswer->setPlaceholderText("请输入正确答案 (如 A)...");
    if (m_inputSearch) m_inputSearch->setPlaceholderText("请输入关键词搜索...");
}

void AdminController::refreshQuestionList()
{
    if (!m_listQuestions) return;

    m_listQuestions->clear();
    const QVector<Question>& allQuestions = m_questionManager->getAllQuestions();
    for (const Question& q : allQuestions) {
        QListWidgetItem* item = new QListWidgetItem(QString("ID:%1 %2").arg(q.id).arg(q.content));
        // 将ID存储在Item的数据中，方便后续获取
        item->setData(Qt::UserRole, q.id);
        m_listQuestions->addItem(item);
    }
}

void AdminController::onListRowChanged(int currentRow)
{
    if (currentRow < 0 || !m_listQuestions) {
        // 如果没有选中项（例如列表被清空），则清空输入框
        if(m_editQuestion) m_editQuestion->clear();
        if(m_editA) m_editA->clear();
        if(m_editB) m_editB->clear();
        if(m_editC) m_editC->clear();
        if(m_editD) m_editD->clear();
        if(m_editAnswer) m_editAnswer->clear();
        return;
    }

    QListWidgetItem* item = m_listQuestions->item(currentRow);
    int id = item->data(Qt::UserRole).toInt();

    Question q = m_questionManager->getQuestionById(id);
    
    // 填充到编辑框
    if(m_editQuestion) m_editQuestion->setText(q.content);
    if(m_editA) m_editA->setText(q.optionA);
    if(m_editB) m_editB->setText(q.optionB);
    if(m_editC) m_editC->setText(q.optionC);
    if(m_editD) m_editD->setText(q.optionD);
    if(m_editAnswer) m_editAnswer->setText(q.answer);
}

void AdminController::onAddClicked()
{
    Question q;
    q.content = m_editQuestion->toPlainText();
    q.optionA = m_editA->text();
    q.optionB = m_editB->text();
    q.optionC = m_editC->text();
    q.optionD = m_editD->text();
    q.answer = m_editAnswer->text().toUpper();

    if (q.content.isEmpty() || q.answer.isEmpty()) {
        QMessageBox::warning(nullptr, "Warning", "Content and Answer cannot be empty.");
        return;
    }

    m_questionManager->addQuestion(q);
    m_questionManager->saveQuestions("questions.txt");
    refreshQuestionList();
    QMessageBox::information(nullptr, "Info", "Question added.");

    // 添加完成后清空输入框，方便添加下一题
    m_editQuestion->clear();
    m_editA->clear();
    m_editB->clear();
    m_editC->clear();
    m_editD->clear();
    m_editAnswer->clear();
}

void AdminController::onDeleteClicked()
{
    QListWidgetItem* item = m_listQuestions->currentItem();
    if (!item) {
        QMessageBox::warning(nullptr, "Warning", "Please select a question to delete.");
        return;
    }

    int id = item->data(Qt::UserRole).toInt();
    if (m_questionManager->deleteQuestion(id)) {
        m_questionManager->saveQuestions("questions.txt");
        refreshQuestionList();
        
        m_editQuestion->clear();
        m_editA->clear();
        m_editB->clear();
        m_editC->clear();
        m_editD->clear();
        m_editAnswer->clear();
        
        QMessageBox::information(nullptr, "Info", "Question deleted.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to delete question.");
    }
}

void AdminController::onUpdateClicked()
{
    QListWidgetItem* item = m_listQuestions->currentItem();
    if (!item) {
        QMessageBox::warning(nullptr, "Warning", "Please select a question to update.");
        return;
    }

    int id = item->data(Qt::UserRole).toInt();
    
    Question q;
    q.id = id;
    q.content = m_editQuestion->toPlainText();
    q.optionA = m_editA->text();
    q.optionB = m_editB->text();
    q.optionC = m_editC->text();
    q.optionD = m_editD->text();
    q.answer = m_editAnswer->text().toUpper();

    if (m_questionManager->updateQuestion(id, q)) {
        m_questionManager->saveQuestions("questions.txt");
        refreshQuestionList();
        QMessageBox::information(nullptr, "Info", "Question updated.");
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to update question.");
    }
}

void AdminController::onSearchClicked()
{
    QString keyword = m_inputSearch->text();
    QList<Question> results = m_questionManager->searchQuestions(keyword);

    if (results.isEmpty()) {
        m_textResult->setText("没有找到包含 \"" + keyword + "\" 的相关题目。");
        return;
    }

    QString displayText;
    for (const Question& q : results) {
        QString item = QString(
         "================================\n"
         "【题目ID】: %1\n"
         "【题干】: %2\n\n"
         "  A. %3\n"
         "  B. %4\n"
         "  C. %5\n"
         "  D. %6\n\n"
         "★ 标准答案: %7\n"
         "================================\n\n"
         )
         .arg(q.id)
         .arg(q.content)
         .arg(q.optionA)
         .arg(q.optionB)
         .arg(q.optionC)
         .arg(q.optionD)
         .arg(q.answer);

        displayText.append(item);
    }
    m_textResult->setText(displayText);
}
