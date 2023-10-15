#include "TextBrowserLogger.h"



void TextBrowserLogger::write(const QString& text) {
    this->append(text);
}

void TextBrowserLogger::showMessage(const QString& message) {
    this->append(message);
}


TextBrowserLogger::TextBrowserLogger(QWidget* parent) : QTextBrowser(parent)
{

};

TextBrowserLogger::~TextBrowserLogger()
{
};