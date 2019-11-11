#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QMainWindow>
#include <QMdiArea>
#include <QGridLayout>
#include <QLabel>
#include <QCalendarWidget>
#include <QVector>

#include "program.h"
#include "customproxy.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class WindowManager;
}
QT_END_NAMESPACE

class WindowManager : public QMainWindow
{
    Q_OBJECT

public:
    WindowManager(std::string background_name = "", QWidget *parent = nullptr);
    ~WindowManager();
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent* event);
private slots:
    void AddSubWindow();

private:
    Ui::WindowManager *ui;
    QMdiArea* mdiArea;

    // background image variables:
    QString bkgnd_name; // background name string
    QPixmap bkgnd;      // background load variable
    QPixmap curr_bkgnd; // current background (skaled 'bkgnd')

    // boolean is fullscreen
    bool isFullScreen = true;

    // programs in window manager
    QVector<Program> programs;

};

#endif // WINDOWMANAGER_H
