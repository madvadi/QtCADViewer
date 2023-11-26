#include "DT_GUI_Window.h"

using namespace std;

DT_GUI_WidgetTest::DT_GUI_WidgetTest(QWidget* parent)
    : QMainWindow(parent)
{

    ui.setupUi(this);

    gl_ptr = new QGL((float)this->width(), (float)this->height(),this, ui.openGLWidget);

    gl_ptr->resize(ui.openGLWidget->width(), ui.openGLWidget->height());

    gl_ptr->show();


    QPixmap pix("Logo.bmp");

    QGraphicsScene* scene = new QGraphicsScene();

    scene->addPixmap(pix);

    ui.graphicsView->setScene(scene);

    gl_ptr->addLayer("Logo2.bmp",0,0);

    this->setCentralWidget(ui.centralwidget);

    ui.centralwidget->setLayout(ui.verticalLayout_4);

    (*gl_ptr).obj_key = new KeyEnterReceiver;

    gl_ptr->installEventFilter((*gl_ptr).obj_key);

    setMouseTracking(true);


};


void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{

    static QTextBrowser* textBrowser = nullptr; // Define a static pointer to your QTextBrowser

    if (!textBrowser) {
        std::cerr << "TextBrowser not set!" << std::endl;
        return;
    }

    switch (type) {
    case QtDebugMsg:
        textBrowser->append(msg);
        break;
        // Handle other message types if necessary
    }


};

void DT_GUI_WidgetTest::resizeGLContext()
{
    gl_ptr->resize(ui.openGLWidget->width(), ui.openGLWidget->height());
};

void DT_GUI_WidgetTest::PrintTo()
{
    GLdouble get_posZ = gl_ptr->return_posZ();



    QString str_output = "posZ: " + QVariant::fromValue(get_posZ).toString();

    ui.textBrowser->append(str_output);

};



DT_GUI_WidgetTest::~DT_GUI_WidgetTest()
{

};
