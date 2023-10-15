#pragma once
#ifndef DT_GUI_WINDOW_H
#define DT_GUI_WINDOW_H

#include "ui_WidgetForm.h"
#include <QtWidgets/QMainWindow>
#include <iostream>

#include "OpenglRender.h"
#include "Load.h"

#include "TableViewCustom.h"

#include "TextBrowserLogger.h"




class DT_GUI_WidgetTest : public QMainWindow
{
	Q_OBJECT
public:
	DT_GUI_WidgetTest(QWidget* parent = nullptr);


	void InitAux();

	~DT_GUI_WidgetTest();

private:

	tableViewCustom* table;

	QGL* gl_ptr;

	TextBrowserLogger* Logger;

	Ui::Form ui;

protected:
	/*
	void keyPressEvent(QKeyEvent* event) override
	{
		if (gl_ptr != NULL)
		{

			QString str = event->text();

			int keyi = event->key();

			qDebug() << "key: " << str;
			qDebug() << "key: " << QString::number(keyi);

			if (keyi == 50) {
				gl_ptr->return_view(-0.5f);
			}
			else if(keyi == 56) {
				gl_ptr->return_view(0.5f);
			}


		}
	}*/

	void resizeEvent(QResizeEvent* event) override
	{
		QMainWindow::resizeEvent(event); // call the base class implementation

		// Run your custom function here
		gl_ptr->resize(ui.openGLWidget->width(),ui.openGLWidget->height());


	}


};



#endif