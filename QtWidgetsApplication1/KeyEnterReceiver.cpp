#include "KeyEnterReceiver.h"


KeyEnterReceiver::KeyEnterReceiver(QWidget* parent) : QWidget(parent)
{

    isLeftKeyPressed = false;
    isUpKeyPressed = false;
    isRightKeyPressed = false;
    isDownKeyPressed = false;
	isUpArrowKeyPressed = false;
	isDownArrowKeyPressed = false;

	isNumUpArrowKeyPressed = false;
	isNumDownArrowKeyPressed = false;


	isRightMouseButtonPressed = false;
	isLeftMouseButtonPressed = false;
	isMiddleMouseButtonPressed = false;

	angleWheel = 0.0f;

	x = 0.0f;
	y = 0.0f;


	pressed_x = 0.0f;
    pressed_y = 0.0f;

};

float KeyEnterReceiver::return_MouseMovement()
{
	this->mouseGrabber();


	return 0.0f;
};



bool KeyEnterReceiver::eventFilter(QObject* obj, QEvent* event)
{
	/*
	QMouseEvent* eventMouse = (QMouseEvent*)event;

	x = eventMouse->position().x();

	y = eventMouse->position().y();*/


	if (event->type() == QEvent::KeyPress) {
		QKeyEvent* key = static_cast<QKeyEvent*>(event);
		if (key->key() == Qt::Key_A || key->key() == Qt::Key_Left) {
			this->isLeftKeyPressed = true;
		}

		if (key->key() == Qt::Key_W || key->key() == Qt::Key_Up) {
			this->isUpKeyPressed = true;
		}

		if (key->key() == Qt::Key_D || key->key() == Qt::Key_Right) {
			this->isRightKeyPressed = true;
		}

		if (key->key() == Qt::Key_S || key->key() == Qt::Key_Down) {
			this->isDownKeyPressed = true;
		}
		if (key->key() == Qt::Key_0) {
			this->isNumUpArrowKeyPressed = true;
		}

		if (key->key() == Qt::Key_1) {
			this->isNumDownArrowKeyPressed = true;
		}
		else {
			return QObject::eventFilter(obj, event);
		}
		return true;
	}
	else if (event->type() == QEvent::KeyRelease)
	{
		QKeyEvent* key = static_cast<QKeyEvent*>(event);
		if (key->key() == Qt::Key_A || key->key() == Qt::Key_Left) {
			this->isLeftKeyPressed = false;
		}

		if (key->key() == Qt::Key_W || key->key() == Qt::Key_Up) {
			this->isUpKeyPressed = false;
		}

		if (key->key() == Qt::Key_D || key->key() == Qt::Key_Right) {
			this->isRightKeyPressed = false;
		}

		if (key->key() == Qt::Key_S || key->key() == Qt::Key_Down) {
			this->isDownKeyPressed = false;
		}
		if (key->key() == Qt::Key_0) {
			this->isNumUpArrowKeyPressed = false;
		}

		if (key->key() == Qt::Key_1) {
			this->isNumDownArrowKeyPressed = false;
		}
		else {
			return QObject::eventFilter(obj, event);
		}
		return true;
	}
	else if (event->type() == QEvent::MouseButtonPress)
	{

		QMouseEvent* eventMouse = (QMouseEvent*)event;
		if (eventMouse->button() == Qt::RightButton) {

			isRightMouseButtonPressed = true;
			//qDebug() << "Right button pressed at: " << eventMouse->pos();
		}
		if (eventMouse->button() == Qt::LeftButton) {

			isLeftMouseButtonPressed = true;
			//qDebug() << "Left button pressed at: " << eventMouse->pos();

		}
		if (eventMouse->button() == Qt::MiddleButton) {

			isMiddleMouseButtonPressed = true;
			// qDebug() << "Middle button pressed at: " << eventMouse->pos();
		}

		return true;

	}
	else if (event->type() == QEvent::MouseButtonRelease)
	{

		QMouseEvent* eventMouse = (QMouseEvent*)event;

		if (eventMouse->button() == Qt::RightButton) {

			isRightMouseButtonPressed = false;
			//qDebug() << "Right button pressed at: " << eventMouse->pos();
		}		
		if (eventMouse->button() == Qt::LeftButton) {

			isLeftMouseButtonPressed = false;
			//qDebug() << "Left button pressed at: " << eventMouse->pos();

		}
		if (eventMouse->button() == Qt::MiddleButton) {

			isMiddleMouseButtonPressed = false;
			//qDebug() << "Middle button pressed at: " << eventMouse->pos();
		}

		return true;

	}
	else if (event->type() == QEvent::Wheel) 
	{

		QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);


		x = mapFromGlobal(wheelEvent->position()).x();

	    y = mapFromGlobal(wheelEvent->position()).y();

		angleWheel = angleWheel + (float)wheelEvent->angleDelta().y() / 120.0f;

		//angleWheel = (float)wheelEvent->angleDelta().y() / 120.0f;

		//qDebug() << "Wheel Movement: " << angleWheel;

		return true; 
	}
	else {

		QPoint mousepos = mapFromGlobal(QCursor::pos());

		x = mousepos.x();

		y = mousepos.y();

		//qDebug() << "Mouse position: x: " << x << " y: " <<y;
		return QObject::eventFilter(obj, event);
	}
	return false;
}


float KeyEnterReceiver::return_angleWheel()
{

	return angleWheel;
};


void KeyEnterReceiver::equal_angleWheel(float value)
{
	angleWheel = value;
};

float KeyEnterReceiver::return_x()
{

	return x;
};

float KeyEnterReceiver::return_y()
{

	return y;
};

float KeyEnterReceiver::return_x(QWidget* ptr)
{


	return ptr->mapFromGlobal(QCursor::pos()).x();
};

float KeyEnterReceiver::return_y(QWidget* ptr)
{

	return ptr->mapFromGlobal(QCursor::pos()).y();
};

