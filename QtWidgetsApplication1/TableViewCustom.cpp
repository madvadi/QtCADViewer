#include "TableViewCustom.h"

tableViewCustom::tableViewCustom(QWidget* parent) : QTableView(parent)
{

	contextMenu = NULL;
};

tableViewCustom::~tableViewCustom()
{


};

int tableViewCustom::InitTableModel(QList<QString> HeaderHorizontal, QList<QString> HeadersVertical)
{
	QSmodel = new QStandardItemModel();

	QSmodel->setRowCount(HeaderHorizontal.size());
	QSmodel->setColumnCount(HeadersVertical.size());

	QSmodel->setHorizontalHeaderLabels(HeaderHorizontal);

	QSmodel->setVerticalHeaderLabels(HeadersVertical);

	return 0;

};

int tableViewCustom::InitTableView()
{
	/*
	QSmodel = new QStandardItemModel();

	QSmodel->setRowCount(noRows);
	QSmodel->setColumnCount(noColumns);

	QSmodel->setHorizontalHeaderLabels(QList<QString>({"Aa","Bb","Cc" }) );

	QSmodel->setVerticalHeaderLabels(QList<QString>({ "1!", "2\"", "3£" }) );*/

	if (QSmodel == NULL)
	{
		qDebug() << "The tableView's model is still NULL!";
		return -1;
	}


	this->setVisible(true);

	// Enable sorting
	this->setSortingEnabled(false);

	// Set row and column headers
	this->verticalHeader()->setVisible(true);

	this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	this->horizontalHeader()->setVisible(true);

	this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	this->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

	// Allow editing in the cells.
	this->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);

	this->setModel(QSmodel);



	return 0;
};

void tableViewCustom::contextMenuEvent(QContextMenuEvent* event)
{

	// Show the context menu at the cursor position!
	if (contextMenu != NULL && event != NULL)
		contextMenu->exec(event->globalPos());

}

int tableViewCustom::addCMenu(QMenu* menu)
{

	contextMenu = menu;

	return 0;

};


int tableViewCustom::addCMenu(QList<QString> list)
{

	contextMenu = new QMenu(this);

	for (const QString& qstring : list)
		contextMenu->addAction(qstring);

	return 0;

};

int tableViewCustom::EditSettings()
{

	return 0;
};

int tableViewCustom::Render()
{
	return 0;
};

QVariant tableViewCustom::GetData(int rowIndex, int columnIndex)
{
	QAbstractItemModel* model = this->model();

	if (rowIndex >= model->rowCount() || columnIndex >= model->columnCount())
	{
		qDebug() << "You are trying to access index:";
		qDebug() << "Row Number = " << QString::number(rowIndex);
		qDebug() << "Column Number = " << QString::number(columnIndex);
		qDebug() << "In a TableView with only " << QString::number(model->rowCount()) << " rows and " << QString::number(model->columnCount());


		return QVariant();
	}

	QModelIndex IndexCurrent = model->index(rowIndex, columnIndex);

	return model->data(IndexCurrent);

};