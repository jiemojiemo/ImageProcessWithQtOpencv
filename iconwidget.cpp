#include "iconwidget.h"

const int IconWidget::kWindowWidth = 128;
const int IconWidget::kWindowHeight = 128;
const int IconWidget::kButtonWidth = IconWidget::kWindowWidth / 5;
const int IconWidget::kButtonHeight = IconWidget::kWindowHeight / 5;

IconWidget::IconWidget(const QString& path, QWidget *parent)
	: QLabel(parent),m_pushBut("X", this),m_imgPath(path)
{
	//setWindowFlags(Qt::FramelessWindowHint);
	this->setFixedSize(kWindowWidth, kWindowHeight);
	setAutoFillBackground(false);
	m_pushBut.setFixedSize(kButtonWidth, kButtonHeight);
	m_pushBut.move(kWindowWidth-kButtonWidth,0);
	m_pushBut.setVisible(false);



	QPixmap pixmap(m_imgPath);
	
	this->setPixmap(pixmap.scaled(kWindowWidth, kWindowHeight));
	
	connect(&m_pushBut, SIGNAL(clicked()), this, SLOT(ClickCloseButton()));
	connect(this, SIGNAL(IconClose(IconWidget*)), parent, SLOT(RemoveIcon(IconWidget*)));

	ui.setupUi(this);
}

IconWidget::~IconWidget()
{

}

void IconWidget::enterEvent(QEvent *event)
{
	m_pushBut.setVisible(true);
}

void IconWidget::leaveEvent(QEvent *event)
{
	m_pushBut.setVisible(false);
}

void IconWidget::ClickCloseButton()
{
	this->close();
	emit IconClose(this);
}
