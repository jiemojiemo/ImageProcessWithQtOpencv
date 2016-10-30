#ifndef ICONWIDGET_H
#define ICONWIDGET_H

#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QLabel>
#include "ui_iconwidget.h"

class IconWidget : public QLabel
{
	Q_OBJECT

public:
	IconWidget(const QString& path, QWidget *parent = 0);
	~IconWidget();
	virtual void enterEvent(QEvent *event);
	virtual void leaveEvent(QEvent *event);

	QString GetImagePath()const { return m_imgPath; }
private slots:
	void ClickCloseButton();
signals:
	void IconClose(IconWidget* removeItem);
private:
	Ui::IconWidgetClass ui;
	QPushButton m_pushBut;
	QString m_imgPath;
	static const int kWindowWidth;
	static const int kWindowHeight;
	static const int kButtonWidth;
	static const int kButtonHeight;
};

#endif // ICONWIDGET_H
