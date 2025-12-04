#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QTextBrowser>

class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDialog(QWidget *parent = nullptr);
    ~HelpDialog();

private:
    QTextBrowser *browser;
    void loadDocumentation();
};

#endif // HELPDIALOG_H
