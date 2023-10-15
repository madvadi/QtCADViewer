#pragma once
#ifndef _TABLEVIEWCUSTOM_H_
#define _TABLEVIEWCUSTOM_H_


#include <qwidget.h>
#include <qtableview.h>
#include<qstandarditemmodel>
#include <qheaderview.h>
#include <qmenu.h>
#include <QtWidgets/QApplication>
#include <QtWidgets>
#include <QtWidgets/QMainWindow>
#include <qmessagebox>
#include <qtableview>
#include<qstandarditemmodel>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/qdialogbuttonbox.h>
#include <qmessagebox>
#include <QDir>
#include <qfile>
#include <qprocess.h>



class tableViewCustom : public QTableView
{
	Q_OBJECT
public:
	tableViewCustom(QWidget* parent = nullptr);
	~tableViewCustom();

	int InitTableModel(QList<QString> HeaderHorizontal, QList<QString> HeadersVertical);

	int InitTableView();

	int addCMenu(QMenu* menu);

	int addCMenu(QList<QString> list);


	void contextMenuEvent(QContextMenuEvent* event);

	int EditSettings();

	int Render();

	QVariant GetData(int rowIndex, int columnIndex);


private:

	QMenu* contextMenu;


	QStandardItemModel* QSmodel;



};

#endif
