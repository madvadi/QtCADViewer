#include "DT_GUI_Window.h"


int main(int argc, char** argv)
{

	QApplication app(argc, argv);

	DT_GUI_WidgetTest* win_ptr = new DT_GUI_WidgetTest();

	win_ptr->show();	

	win_ptr->resizeGLContext();
	
	return app.exec();

};
