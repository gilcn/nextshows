#include "view.h"

/*
** public:
*/
View::View(QWidget *parent)
    : QGraphicsView(parent)
    , m_scrollWidget(new QWidget())
    , m_gridLayout(new QGridLayout())
    , m_scene(new QGraphicsScene())
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    m_scrollWidget->setLayout(m_gridLayout);
    m_scrollWidget->setAttribute(Qt::WA_NoSystemBackground);

    for (int i=0; i<10; ++i) {
        for (int j=0; j<3; ++j) {
            m_gridLayout->addWidget(new QLabel("test"), i, j);
        }
    }

    m_scrollWidgetProxy = m_scene->addWidget(m_scrollWidget);

    setScene(m_scene);

    m_timer = startTimer(50);
} // ctor()

View::~View()
{
} // dtor()


/*
** protected:
*/
void View::timerEvent(QTimerEvent * /*event*/)
{
    QPointF oldPos = m_scrollWidgetProxy->pos();
    QPointF newPos(oldPos.x(), oldPos.y()-0.5);
    m_scrollWidgetProxy->setPos(newPos);

//    qDebug() << m_scrollWidgetProxy->pos();
} // timerEvent()

void View::resizeEvent(QResizeEvent * /*event*/)
{
} // resizeEvent()
