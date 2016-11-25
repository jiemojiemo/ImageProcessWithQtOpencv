#include "Magic/QTextPainter.h"
#include "highgui.hpp"
QTextPainter::QTextPainter()
{
	SetPixelSize(50);
	SetColor(Qt::red);
	SetBold(false);
	SetRect(QRect());
}

QImage QTextPainter::PaintText(MImage& img, const std::string& text)
{
	if (!IsValidRect())
	{
		SetRect(QRect(0,0,img.GetWidth(), img.GetHeight()));
	}
	
	return Paint(img.GetQImage(), QString::fromStdString(text));
}

QTextPainter::~QTextPainter()
{

}

void QTextPainter::SetPixelSize(int s/*=50*/)
{
	m_font.setPixelSize(s);
}

void QTextPainter::SetBold(bool b /*= false*/)
{
	m_font.setBold(b);
}

void QTextPainter::SetColor(const QColor& color/*=Qt::red*/)
{
	m_pen.setColor(color);
}

void QTextPainter::SetRect(const QRect& r)
{
	m_rect = r;
}

void QTextPainter::SetRect(int x /*= 0*/, int y /*= 0*/, int width /*= -1*/, int height /*= -1*/)
{
	QRect r(x,y, width, height);
	m_rect = r;
}

bool QTextPainter::IsValidRect() const
{
	return m_rect.isValid();
}

QImage QTextPainter::Paint(QImage& img, const QString& text)
{
	//
	QImage newImg = img.copy();
	QPainter painter(&newImg);
	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.setPen(m_pen);
	painter.setFont(m_font);
	QTextOption option(Qt::AlignLeft | Qt::AlignTop);
	option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

	painter.drawText(newImg.rect(), text, option);
	return newImg;
}

