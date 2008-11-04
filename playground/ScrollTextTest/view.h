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
    void resizeEvent(QResizeEvent *event);

private:
    QWidget *m_scrollWidget;
    QGridLayout *m_gridLayout;
    QGraphicsScene *m_scene;
};

#endif // __VIEW_H__
