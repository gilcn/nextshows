#ifndef __VIEW_H__
#define __VIEW_H__

#include <QtGui>

class View : public QGraphicsView
{
    Q_OBJECT;

public:
    View(QWidget *parent = 0);
    ~View();

protected:
    void timerEvent(QTimerEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    QWidget *m_scrollWidget;
    QGraphicsProxyWidget *m_scrollWidgetProxy;
    QGridLayout *m_gridLayout;
    QGraphicsScene *m_scene;
    int m_timer;
};

#endif // __VIEW_H__
