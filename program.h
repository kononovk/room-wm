#ifndef PROGRAM_H
#define PROGRAM_H

#include <QDialog>

QT_FORWARD_DECLARE_CLASS(Ui_Program);

namespace Ui {
class Program;
}

class Program : public QDialog
{
    Q_OBJECT
public:
    explicit Program(QWidget *parent = nullptr);
    ~Program();

public slots:
    void layoutDirectionChanged(int index);
    void spacingChanged(int spacing);
    void fontChanged(const QFont &font);
    void styleChanged(const QString &styleName);

private:
    Ui_Program *ui;
};

#endif // PROGRAM_H
