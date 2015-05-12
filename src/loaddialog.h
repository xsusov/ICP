#ifndef LOADDIALOG_H
#define LOADDIALOG_H

#include <QDialog>

namespace Ui {
class LoadDialog;
}

class LoadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadDialog(QWidget *parent = 0, bool type = true);
    ~LoadDialog();

private slots:
    void on_lineEdit_textEdited(const QString &arg1);

    void on_close_button_clicked();

    void on_load_button_clicked();


    void on_browse_clicked();

private:
    Ui::LoadDialog *ui;
    bool type;
};

#endif // LOADDIALOG_H
