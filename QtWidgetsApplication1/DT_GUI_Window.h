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

	void mouseMoveEvent(QMouseEvent* event)  override;


	void resizeGLContext();

	~DT_GUI_WidgetTest();

private:

	tableViewCustom* table;

	QGL* gl_ptr;

	TextBrowserLogger* Logger;

	//MouseTracker mouseP;

	Ui::Form ui;

protected:



	void resizeEvent(QResizeEvent* event) override
	{
		QMainWindow::resizeEvent(event); // call the base class implementation

		// Run your custom function here
		gl_ptr->resize(ui.openGLWidget->width(),ui.openGLWidget->height());


	}


};



#endif