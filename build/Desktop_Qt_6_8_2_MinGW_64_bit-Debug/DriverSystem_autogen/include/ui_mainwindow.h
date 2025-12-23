/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QLineEdit *inputUserID;
    QLabel *label_2;
    QPushButton *btnUserLogin;
    QLabel *label_3;
    QLineEdit *inputAdminPwd;
    QPushButton *btnAdminLogin;
    QWidget *page_3;
    QListWidget *listQuestions;
    QLineEdit *editA;
    QLineEdit *editB;
    QLineEdit *editC;
    QLineEdit *editD;
    QLineEdit *editAnswer;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QPushButton *btnUpdate;
    QPushButton *btnStats;
    QPushButton *btnLogoutAdmin;
    QTextEdit *editQuestion;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QWidget *page_4;
    QTableWidget *tableScores;
    QLabel *label_4;
    QComboBox *comboFilter;
    QPushButton *btnRefresh;
    QPushButton *btnBackToAdmin;
    QLabel *label_6;
    QComboBox *comboModeFilter;
    QWidget *page_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *labelExamQuestion;
    QRadioButton *radioA;
    QRadioButton *radioB;
    QRadioButton *radioC;
    QRadioButton *radioD;
    QPushButton *btnNext;
    QPushButton *btnSubmit;
    QWidget *tab_2;
    QLineEdit *inputSearch;
    QPushButton *btnSearch;
    QTextBrowser *textResult;
    QFrame *frameFreeSetup;
    QLabel *label_5;
    QLineEdit *inputFreeNum;
    QPushButton *btnGenFree;
    QLCDNumber *lcdTimer;
    QPushButton *btnReturnToMode;
    QPushButton *btnLogout;
    QWidget *page_5;
    QPushButton *btnModeMock;
    QPushButton *btnModeFree;
    QWidget *page_6;
    QPushButton *btnNextWrong;
    QRadioButton *radioWrongA;
    QRadioButton *radioWrongD;
    QRadioButton *radioWrongC;
    QRadioButton *radioWrongB;
    QLabel *lblWrongQuestion;
    QPushButton *btnExitWrong;
    QLabel *lblCorrectAnswer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(761, 466);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 20, 731, 411));
        page = new QWidget();
        page->setObjectName("page");
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 10, 481, 61));
        QFont font;
        font.setPointSize(25);
        label->setFont(font);
        inputUserID = new QLineEdit(page);
        inputUserID->setObjectName("inputUserID");
        inputUserID->setGeometry(QRect(200, 140, 331, 31));
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(100, 150, 91, 21));
        QFont font1;
        font1.setPointSize(20);
        label_2->setFont(font1);
        btnUserLogin = new QPushButton(page);
        btnUserLogin->setObjectName("btnUserLogin");
        btnUserLogin->setGeometry(QRect(560, 140, 121, 31));
        QFont font2;
        font2.setPointSize(15);
        btnUserLogin->setFont(font2);
        label_3 = new QLabel(page);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(80, 250, 111, 31));
        label_3->setFont(font1);
        inputAdminPwd = new QLineEdit(page);
        inputAdminPwd->setObjectName("inputAdminPwd");
        inputAdminPwd->setGeometry(QRect(200, 250, 331, 31));
        inputAdminPwd->setEchoMode(QLineEdit::EchoMode::Password);
        btnAdminLogin = new QPushButton(page);
        btnAdminLogin->setObjectName("btnAdminLogin");
        btnAdminLogin->setGeometry(QRect(560, 250, 121, 31));
        btnAdminLogin->setFont(font2);
        stackedWidget->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        listQuestions = new QListWidget(page_3);
        listQuestions->setObjectName("listQuestions");
        listQuestions->setGeometry(QRect(10, 10, 441, 321));
        listQuestions->setWordWrap(true);
        editA = new QLineEdit(page_3);
        editA->setObjectName("editA");
        editA->setGeometry(QRect(580, 130, 113, 31));
        editB = new QLineEdit(page_3);
        editB->setObjectName("editB");
        editB->setGeometry(QRect(580, 170, 113, 31));
        editC = new QLineEdit(page_3);
        editC->setObjectName("editC");
        editC->setGeometry(QRect(580, 210, 113, 31));
        editD = new QLineEdit(page_3);
        editD->setObjectName("editD");
        editD->setGeometry(QRect(580, 250, 113, 31));
        editAnswer = new QLineEdit(page_3);
        editAnswer->setObjectName("editAnswer");
        editAnswer->setGeometry(QRect(580, 290, 113, 31));
        btnAdd = new QPushButton(page_3);
        btnAdd->setObjectName("btnAdd");
        btnAdd->setGeometry(QRect(10, 350, 91, 41));
        btnDelete = new QPushButton(page_3);
        btnDelete->setObjectName("btnDelete");
        btnDelete->setGeometry(QRect(110, 350, 91, 41));
        btnUpdate = new QPushButton(page_3);
        btnUpdate->setObjectName("btnUpdate");
        btnUpdate->setGeometry(QRect(210, 350, 91, 41));
        btnStats = new QPushButton(page_3);
        btnStats->setObjectName("btnStats");
        btnStats->setGeometry(QRect(310, 350, 91, 41));
        btnLogoutAdmin = new QPushButton(page_3);
        btnLogoutAdmin->setObjectName("btnLogoutAdmin");
        btnLogoutAdmin->setGeometry(QRect(610, 350, 91, 41));
        editQuestion = new QTextEdit(page_3);
        editQuestion->setObjectName("editQuestion");
        editQuestion->setGeometry(QRect(510, 10, 191, 101));
        label_7 = new QLabel(page_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(460, 40, 41, 51));
        label_8 = new QLabel(page_3);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(520, 130, 51, 31));
        label_9 = new QLabel(page_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(520, 171, 51, 31));
        label_10 = new QLabel(page_3);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(520, 211, 51, 31));
        label_11 = new QLabel(page_3);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(520, 250, 51, 31));
        label_12 = new QLabel(page_3);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(510, 290, 61, 31));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        tableScores = new QTableWidget(page_4);
        if (tableScores->columnCount() < 4)
            tableScores->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableScores->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableScores->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableScores->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableScores->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableScores->setObjectName("tableScores");
        tableScores->setGeometry(QRect(230, 10, 461, 341));
        label_4 = new QLabel(page_4);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(110, 10, 111, 31));
        comboFilter = new QComboBox(page_4);
        comboFilter->setObjectName("comboFilter");
        comboFilter->setGeometry(QRect(110, 40, 91, 31));
        btnRefresh = new QPushButton(page_4);
        btnRefresh->setObjectName("btnRefresh");
        btnRefresh->setGeometry(QRect(90, 230, 91, 51));
        btnBackToAdmin = new QPushButton(page_4);
        btnBackToAdmin->setObjectName("btnBackToAdmin");
        btnBackToAdmin->setGeometry(QRect(90, 300, 91, 51));
        label_6 = new QLabel(page_4);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(110, 80, 111, 31));
        comboModeFilter = new QComboBox(page_4);
        comboModeFilter->setObjectName("comboModeFilter");
        comboModeFilter->setGeometry(QRect(110, 110, 91, 31));
        stackedWidget->addWidget(page_4);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        tabWidget = new QTabWidget(page_2);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(20, 60, 581, 311));
        tab = new QWidget();
        tab->setObjectName("tab");
        labelExamQuestion = new QLabel(tab);
        labelExamQuestion->setObjectName("labelExamQuestion");
        labelExamQuestion->setGeometry(QRect(20, 20, 531, 61));
        labelExamQuestion->setWordWrap(true);
        radioA = new QRadioButton(tab);
        radioA->setObjectName("radioA");
        radioA->setGeometry(QRect(40, 110, 411, 21));
        radioB = new QRadioButton(tab);
        radioB->setObjectName("radioB");
        radioB->setGeometry(QRect(40, 140, 401, 31));
        radioC = new QRadioButton(tab);
        radioC->setObjectName("radioC");
        radioC->setGeometry(QRect(40, 180, 411, 31));
        radioD = new QRadioButton(tab);
        radioD->setObjectName("radioD");
        radioD->setGeometry(QRect(40, 220, 451, 31));
        btnNext = new QPushButton(tab);
        btnNext->setObjectName("btnNext");
        btnNext->setGeometry(QRect(440, 170, 101, 41));
        btnSubmit = new QPushButton(tab);
        btnSubmit->setObjectName("btnSubmit");
        btnSubmit->setGeometry(QRect(440, 220, 101, 41));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        inputSearch = new QLineEdit(tab_2);
        inputSearch->setObjectName("inputSearch");
        inputSearch->setGeometry(QRect(20, 20, 321, 21));
        btnSearch = new QPushButton(tab_2);
        btnSearch->setObjectName("btnSearch");
        btnSearch->setGeometry(QRect(350, 20, 56, 18));
        textResult = new QTextBrowser(tab_2);
        textResult->setObjectName("textResult");
        textResult->setGeometry(QRect(20, 50, 321, 121));
        tabWidget->addTab(tab_2, QString());
        frameFreeSetup = new QFrame(page_2);
        frameFreeSetup->setObjectName("frameFreeSetup");
        frameFreeSetup->setGeometry(QRect(20, -10, 461, 61));
        frameFreeSetup->setFrameShape(QFrame::Shape::StyledPanel);
        frameFreeSetup->setFrameShadow(QFrame::Shadow::Raised);
        label_5 = new QLabel(frameFreeSetup);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 20, 81, 21));
        inputFreeNum = new QLineEdit(frameFreeSetup);
        inputFreeNum->setObjectName("inputFreeNum");
        inputFreeNum->setGeometry(QRect(90, 10, 111, 41));
        btnGenFree = new QPushButton(frameFreeSetup);
        btnGenFree->setObjectName("btnGenFree");
        btnGenFree->setGeometry(QRect(260, 10, 111, 41));
        lcdTimer = new QLCDNumber(page_2);
        lcdTimer->setObjectName("lcdTimer");
        lcdTimer->setGeometry(QRect(490, 30, 151, 41));
        lcdTimer->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);
        btnReturnToMode = new QPushButton(page_2);
        btnReturnToMode->setObjectName("btnReturnToMode");
        btnReturnToMode->setGeometry(QRect(620, 250, 101, 41));
        btnLogout = new QPushButton(page_2);
        btnLogout->setObjectName("btnLogout");
        btnLogout->setGeometry(QRect(620, 300, 101, 41));
        stackedWidget->addWidget(page_2);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        btnModeMock = new QPushButton(page_5);
        btnModeMock->setObjectName("btnModeMock");
        btnModeMock->setGeometry(QRect(170, 160, 121, 51));
        btnModeFree = new QPushButton(page_5);
        btnModeFree->setObjectName("btnModeFree");
        btnModeFree->setGeometry(QRect(420, 160, 111, 51));
        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        btnNextWrong = new QPushButton(page_6);
        btnNextWrong->setObjectName("btnNextWrong");
        btnNextWrong->setGeometry(QRect(420, 130, 131, 41));
        radioWrongA = new QRadioButton(page_6);
        radioWrongA->setObjectName("radioWrongA");
        radioWrongA->setEnabled(false);
        radioWrongA->setGeometry(QRect(50, 110, 331, 21));
        radioWrongD = new QRadioButton(page_6);
        radioWrongD->setObjectName("radioWrongD");
        radioWrongD->setEnabled(false);
        radioWrongD->setGeometry(QRect(50, 220, 341, 31));
        radioWrongC = new QRadioButton(page_6);
        radioWrongC->setObjectName("radioWrongC");
        radioWrongC->setEnabled(false);
        radioWrongC->setGeometry(QRect(50, 180, 321, 31));
        radioWrongB = new QRadioButton(page_6);
        radioWrongB->setObjectName("radioWrongB");
        radioWrongB->setEnabled(false);
        radioWrongB->setGeometry(QRect(50, 140, 331, 31));
        lblWrongQuestion = new QLabel(page_6);
        lblWrongQuestion->setObjectName("lblWrongQuestion");
        lblWrongQuestion->setGeometry(QRect(50, 20, 531, 61));
        lblWrongQuestion->setWordWrap(true);
        btnExitWrong = new QPushButton(page_6);
        btnExitWrong->setObjectName("btnExitWrong");
        btnExitWrong->setGeometry(QRect(420, 190, 131, 41));
        lblCorrectAnswer = new QLabel(page_6);
        lblCorrectAnswer->setObjectName("lblCorrectAnswer");
        lblCorrectAnswer->setGeometry(QRect(70, 280, 311, 21));
        lblCorrectAnswer->setStyleSheet(QString::fromUtf8("color: green; font-weight: bold; font-size: 16px;"));
        stackedWidget->addWidget(page_6);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 761, 18));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(3);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\351\251\276\351\251\266\345\221\230\347\220\206\350\256\272\350\257\276\347\250\213\346\250\241\346\213\237\350\200\203\350\257\225\344\270\216\345\255\246\344\271\240\347\263\273\347\273\237", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267ID", nullptr));
        btnUserLogin->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\347\231\273\345\275\225", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\347\256\241\347\220\206\345\221\230\345\257\206\347\240\201", nullptr));
        btnAdminLogin->setText(QCoreApplication::translate("MainWindow", "\347\256\241\347\220\206\345\221\230\347\231\273\351\231\206", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\350\257\225\351\242\230", nullptr));
        btnDelete->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\350\257\225\351\242\230", nullptr));
        btnUpdate->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\344\277\256\346\224\271", nullptr));
        btnStats->setText(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\347\273\237\350\256\241", nullptr));
        btnLogoutAdmin->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\351\242\230\347\233\256", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "A\351\200\211\351\241\271", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "B\351\200\211\351\241\271", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "C\351\200\211\351\241\271", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "D\351\200\211\351\241\271", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\346\255\243\347\241\256\347\255\224\346\241\210", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableScores->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\350\200\203\350\257\225\346\250\241\345\274\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableScores->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableScores->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\345\210\206\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableScores->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\350\200\203\350\257\225\346\227\266\351\227\264", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\346\214\211\347\224\250\346\210\267\347\255\233\351\200\211\357\274\232", nullptr));
        btnRefresh->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260\346\225\260\346\215\256", nullptr));
        btnBackToAdmin->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\346\214\211\346\250\241\345\274\217\347\255\233\351\200\211\357\274\232", nullptr));
        labelExamQuestion->setText(QCoreApplication::translate("MainWindow", "\351\242\230\347\233\256", nullptr));
        radioA->setText(QCoreApplication::translate("MainWindow", "A", nullptr));
        radioB->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        radioC->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        radioD->setText(QCoreApplication::translate("MainWindow", "D", nullptr));
        btnNext->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\351\242\230", nullptr));
        btnSubmit->setText(QCoreApplication::translate("MainWindow", "\344\272\244\345\215\267", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\345\234\250\347\272\277\350\200\203\350\257\225", nullptr));
        inputSearch->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\345\205\263\351\224\256\350\257\215", nullptr));
        btnSearch->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\347\237\245\350\257\206\346\237\245\350\257\242", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\350\256\255\347\273\203\351\242\230\346\225\260\357\274\232", nullptr));
        btnGenFree->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\351\242\230\347\233\256", nullptr));
        btnReturnToMode->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        btnModeMock->setText(QCoreApplication::translate("MainWindow", "\346\250\241\346\213\237\350\200\203\350\257\225", nullptr));
        btnModeFree->setText(QCoreApplication::translate("MainWindow", "\350\207\252\347\224\261\350\256\255\347\273\203", nullptr));
        btnNextWrong->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\351\242\230", nullptr));
        radioWrongA->setText(QCoreApplication::translate("MainWindow", "A", nullptr));
        radioWrongD->setText(QCoreApplication::translate("MainWindow", "D", nullptr));
        radioWrongC->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        radioWrongB->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        lblWrongQuestion->setText(QCoreApplication::translate("MainWindow", "\351\242\230\347\233\256", nullptr));
        btnExitWrong->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        lblCorrectAnswer->setText(QCoreApplication::translate("MainWindow", "\346\255\243\347\241\256\347\255\224\346\241\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
