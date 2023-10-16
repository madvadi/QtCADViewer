#include "DT_GUI_Window.h"

using namespace std;

DT_GUI_WidgetTest::DT_GUI_WidgetTest(QWidget* parent)
    : QMainWindow(parent)
{

    ui.setupUi(this);

    gl_ptr = new QGL(ui.openGLWidget);

    gl_ptr->resize(ui.openGLWidget->width(), ui.openGLWidget->height());


    gl_ptr->show();


    QPixmap pix("Logo.bmp");
    QPixmap pix1("ZoomInIcon.bmp");
    QPixmap pix2("ZoomOutIcon.bmp");

    QPixmap pix3("RotateLeft.bmp");
    QPixmap pix4("RotateRight.bmp");


    QPixmap pix5("Infromation.bmp");

    QIcon IC1(pix1);
    QIcon IC2(pix2);
    QIcon IC3(pix3);
    QIcon IC4(pix4);
    QIcon IC5(pix5);

    QGraphicsScene* scene = new QGraphicsScene();

    scene->addPixmap(pix);

    ui.graphicsView->setScene(scene);


    ui.pushButton->setIcon(IC1);
    ui.pushButton->setIconSize(pix1.rect().size());

    ui.pushButton_2->setIcon(IC2);
    ui.pushButton_2->setIconSize(pix2.rect().size());
    ui.pushButton_3->setIcon(IC3);
    ui.pushButton_3->setIconSize(pix3.rect().size());


    ui.pushButton_4->setIcon(IC4);
    ui.pushButton_4->setIconSize(pix4.rect().size());

    ui.pushButton_5->setIcon(IC5);
    ui.pushButton_5->setIconSize(pix5.rect().size());
    ui.pushButton_5->resize(pix5.rect().height(),pix5.rect().width());


    ui.pushButton_7->setIcon(IC5);
    ui.pushButton_7->setIconSize(pix5.rect().size());

    ui.pushButton_11->setIcon(IC5);
    ui.pushButton_11->setIconSize(pix5.rect().size());
    ui.pushButton_12->setIcon(IC5);
    ui.pushButton_12->setIconSize(pix5.rect().size());
 
    this->setCentralWidget(ui.centralwidget);

    ui.centralwidget->setLayout(ui.verticalLayout_4);


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

void DT_GUI_WidgetTest::InitAux()
{

};


DT_GUI_WidgetTest::~DT_GUI_WidgetTest()
{

};
