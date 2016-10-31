#ifndef ICONWIDGET_H
#define ICONWIDGET_H

#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QPixmap>
#include "DataStructure/Image.h"
#include "ui_iconwidget.h"


class MImage;
class IconWidget : public QLabel, public Image
{
	Q_OBJECT

public:
	IconWidget(const QString& path, QWidget *parent = 0);
	//IconWidget(MImage* pImg, const QString& path,QWidget* parent = 0);
	~IconWidget();

	const QImage& GetQImage()const;
	QImage& GetQImage();
	QString GetImagePath();

	virtual void DoMagic();
	virtual void SetMag(std::shared_ptr<Magician>& val);

	virtual void enterEvent(QEvent *event);
	virtual void leaveEvent(QEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);


private slots:
	void ClickCloseButton();

signals:
	void IconClose(IconWidget* removeItem);
	void clicked(IconWidget* item);
private:
	void Init();
	void InitCloseButton();
	void SetBackgound(const QPixmap& pixmap);
	void UpdateBackgound();
	void SetUpConnect(QWidget* parent);
	void SetOpenHandCursor();
	void SetArrowCursor();
private:
	Ui::IconWidgetClass ui;
	QPushButton m_pushBut;
	QString m_imgPath;
	MImage* m_img;

	static const int kWindowWidth;
	static const int kWindowHeight;
	static const int kButtonWidth;
	static const int kButtonHeight;
};

#endif // ICONWIDGET_H
