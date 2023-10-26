#pragma once

#include <QWidget>
#include <QApplication>
#include <qevent.h>

class KeyEnterReceiver : public QWidget
{
    Q_OBJECT
public:

    explicit  KeyEnterReceiver(QWidget* parent = nullptr);
    

    bool isLeftKeyPressed;
    bool isUpKeyPressed;
    bool isRightKeyPressed;
    bool isDownKeyPressed;	
    bool isUpArrowKeyPressed;
    bool isDownArrowKeyPressed;

    bool isNumUpArrowKeyPressed;
    bool isNumDownArrowKeyPressed;

    float return_angleWheel();


    float return_x();

    float return_y();


private:

    // Different in the mouse wheel movement!
    float angleWheel;

    // Mouse Position
    float x,y;


protected:

    bool eventFilter(QObject* obj, QEvent* event);

};
