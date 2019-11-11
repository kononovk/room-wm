#include <cstdlib>
#include <iostream>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>
#include <QDialog>
#include <QPropertyAnimation>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "window_manager.h"
#include "program.h"
#include "ui_windowmanager.h"

WindowManager::WindowManager(const std::string background_name, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::WindowManager)
{
    ui->setupUi(this);
    bkgnd_name = QString::fromStdString(background_name);
    // QPixmap::load() returns True if loading is successful, else false
    if (bkgnd.load(bkgnd_name)) {
        curr_bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, curr_bkgnd);
        this->setPalette(palette);
    } else {
        qDebug() << "error: background image does not exist";
        QMessageBox::critical(this, "Error", "background image does not exist");
        exit(1);
    }

    mdiArea = new QMdiArea(this);
    // customization scroll bars
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // mdiArea->setStyleSheet("background-color:black;");
    setCentralWidget(mdiArea);

    // добавление sub window
    this->AddSubWindow();
    this->AddSubWindow();
}

WindowManager::~WindowManager() {
    delete ui;
}

void WindowManager::AddSubWindow() {
    // Создаём виджет, который будет окном
    QWidget *widget = new QWidget(mdiArea);
    // Добавляем в него размещение
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Добавляем на виджет надпись
    QLabel *label = new QLabel("Hello, I am sub window!!!", widget);
    gridLayout->addWidget(label);

    // Добавляем виджет в качестве подокна в Mdi Area
    mdiArea->addSubWindow(widget);
    mdiArea->setBackground(QBrush(Qt::transparent));

    // Устанавливаем заголовок окна
    widget->setWindowTitle("Sub Window");
    widget->setStyleSheet("background-color:black;");

    // и показываем виджет
    widget->show();
}

void WindowManager::resizeEvent(QResizeEvent *event) {
    if (event == nullptr)
        return;
    qDebug() << event->size();
    curr_bkgnd = bkgnd.scaled(event->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, curr_bkgnd);
    this->setPalette(palette);
}

void WindowManager::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_Escape:
        exit(0);
    case Qt::Key_F:
        if (isFullScreen) {
            this->showFullScreen();
            qDebug() << "Here1";
        }
        else {
            this->show();
            qDebug() << "Here2";
        }
        isFullScreen = !isFullScreen;
        break;
    default:
        break;
    }
}

void WindowManager::showEvent(QShowEvent* event)
{
    QPropertyAnimation* anim = new QPropertyAnimation(this, "windowOpacity");
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->setDuration(1000);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}


