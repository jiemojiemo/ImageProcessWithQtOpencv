#pragma once
#include "DataStructure/MImage.h"
#include <QPainter>
#include <QRect>
#include <string>
class QTextPainter
{
public:
	QTextPainter();
	virtual QImage PaintText(MImage& img, const std::string& text) = 0;
	virtual ~QTextPainter();
	void SetPixelSize(int s=50);
	void SetBold(bool b = false);
	void SetColor(const QColor& color=Qt::red);
	void SetRect(const QRect& r);
	void SetRect(int x = 0, int y = 0, int width = -1, int height = -1);
private:
	bool IsValidRect()const;
	QImage Paint(QImage& img, const QString& text);
protected:
	//QPainter m_painter;
	QPen m_pen;
	QFont m_font;
	QRect m_rect;
};