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
    m_scrollWidget->setLayout(m_gridLayout);
    m_scrollWidget->setAttribute(Qt::WA_NoSystemBackground);

    for (int i=0; i<10; ++i) {
        for (int j=0; j<3; ++j) {
            m_gridLayout->addWidget(new QLabel("test"), i, j);
        }
    }

    m_scene->addWidget(m_scrollWidget);

    setScene(m_scene);
} // ctor()

View::~View()
{
    delete m_scene;
    delete m_gridLayout;
    delete m_scrollWidget;
} // dtor()


/*
** protected:
*/
void View::resizeEvent(QResizeEvent * /*event*/)
{
} // resizeEvent()
