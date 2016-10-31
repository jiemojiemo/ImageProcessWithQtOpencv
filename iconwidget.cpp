#include "iconwidget.h"
#include "DataStructure/MImage.h"
const int IconWidget::kWindowWidth = 128;
const int IconWidget::kWindowHeight = 128;
const int IconWidget::kButtonWidth = IconWidget::kWindowWidth / 5;
const int IconWidget::kButtonHeight = IconWidget::kWindowHeight / 5;

IconWidget::IconWidget(const QString& path, QWidget *parent)
	: QLabel(parent),
	m_pushBut("X", this),
	m_imgPath(path),
	m_img(new MImage(path))
{
	
	this->Init();
	SetUpConnect(parent);
}

//IconWidget::IconWidget(MImage* pImg, const QString& path, QWidget* parent /*= 0*/):
//	QLabel(parent),
//	m_pushBut("X", this),
//	m_img(pImg),
//	m_imgPath(path)
//{
//	QPixmap pixmap(QPixmap::fromImage(pImg->GetQImage()));
//	this->Init(pixmap);
//	SetUpConnect(parent);
//}

IconWidget::~IconWidget()
{
	if (m_img != nullptr)
	{
		delete m_img;
		m_img = nullptr;
	}
}

const QImage& IconWidget::GetQImage() const
{
	return m_img->GetQImage();
}

QImage& IconWidget::GetQImage()
{
	return m_img->GetQImage();
}

QString IconWidget::GetImagePath()
{
	return m_imgPath;
}

void IconWidget::enterEvent(QEvent *event)
{
	m_pushBut.setVisible(true);
	this->SetOpenHandCursor();
}

void IconWidget::leaveEvent(QEvent *event)
{
	m_pushBut.setVisible(false);
	this->SetArrowCursor();
}

void IconWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit clicked(this);
	}
}

void IconWidget::DoMagic()
{
	m_img->DoMagic();
	UpdateBackgound();
}

void IconWidget::SetMag(std::shared_ptr<Magician>& val)
{
	m_img->SetMag(val);
}

void IconWidget::ClickCloseButton()
{
	this->close();
	emit IconClose(this);
}

void IconWidget::Init()
{
	this->setFixedSize(kWindowWidth, kWindowHeight);
	UpdateBackgound();
	InitCloseButton();
	ui.setupUi(this);

}

void IconWidget::InitCloseButton()
{
	m_pushBut.setFixedSize(kButtonWidth, kButtonHeight);
	m_pushBut.move(kWindowWidth - kButtonWidth, 0);
	m_pushBut.setVisible(false);
}

void IconWidget::SetBackgound(const QPixmap& pixmap)
{
	setAutoFillBackground(false);
	this->setPixmap(pixmap.scaled(kWindowWidth, kWindowHeight));
}

void IconWidget::UpdateBackgound()
{
	QPixmap pixmap(QPixmap::fromImage(m_img->GetQImage()));
	this->SetBackgound(pixmap);
}

void IconWidget::SetUpConnect(QWidget* parent)
{
	connect(&m_pushBut, SIGNAL(clicked()), this, SLOT(ClickCloseButton()));
	connect(this, SIGNAL(IconClose(IconWidget*)), parent, SLOT(RemoveIcon(IconWidget*)));
	connect(this, SIGNAL(clicked(IconWidget*)), parent, SLOT(OpenImage(IconWidget*)));
}

void IconWidget::SetOpenHandCursor()
{
	this->setCursor(Qt::OpenHandCursor);
}

void IconWidget::SetArrowCursor()
{
	this->setCursor(Qt::ArrowCursor);
}