#include <QApplication>
#include <QWidget>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "window_manager.h"
#include "customproxy.h"
#include "program.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);                       // resources.qrc initialization
    std::string background = ":/res/background.jpg";  // background initialization
    QApplication room_wm(argc, argv);                 // application initialization

    // window rendering
    QGraphicsScene scene;
    scene.setStickyFocus(true);

    const int gridsize = 5;
    for (int y = 0; y < gridsize; ++y) {
        for (int x = 0; x < gridsize; ++x) {
            CustomProxy *proxy = new CustomProxy(nullptr, Qt::Window);
            proxy->setWidget(new Program);

            QRectF rect = proxy->boundingRect();

            proxy->setPos(x * rect.width() * 1.05, y * rect.height() * 1.05);
            proxy->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

            scene.addItem(proxy);
        }
    }
    scene.setSceneRect(scene.itemsBoundingRect());
    QGraphicsView view(&scene);
    view.scale(0.5, 0.5);
    view.setRenderHints(view.renderHints() | QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.show();
    view.setWindowTitle("Demo");

    WindowManager w(background);
    w.show();

    return room_wm.exec();
}
