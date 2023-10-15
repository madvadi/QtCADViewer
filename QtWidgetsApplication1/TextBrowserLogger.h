#pragma once
#ifndef _TEXTBROWSERLOGGER_H_
#define _TEXTBROWSERLOGGER_H_

#include <QApplication>
#include <QDebug>
#include <QTextBrowser>

class TextBrowserLogger : public QTextBrowser
{
public:

    TextBrowserLogger(QWidget* parent = nullptr);

    ~TextBrowserLogger();

    void write(const QString& text);

    void showMessage(const QString& message);

};

#endif