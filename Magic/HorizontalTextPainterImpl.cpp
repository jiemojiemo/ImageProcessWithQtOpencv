#include "Magic/HorizontalTextPainterImpl.h"
#include <QPainter>
QImage PaintTextOnQImge(QImage& img, const QString& text)
{
	QImage newImg = img.copy();
	QPainter painter(&newImg);
	painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
	//改变画笔和字体
	QPen pen = painter.pen();
	pen.setColor(Qt::red);
	QFont font = painter.font();
	font.setBold(true);//加粗
	font.setPixelSize(50);//改变字体大小

	painter.setPen(pen);
	painter.setFont(font);

	painter.drawText(newImg.rect(), Qt::AlignTop | Qt::AlignLeft, text);
	return newImg;
}

QImage HorizontalTextPainterImpl::PaintText(MImage& img, const std::string& text)
{
	return QTextPainter::PaintText(img, text);
	//QString str = QString::fromStdString(text);
	//return PaintTextOnQImge(img.GetQImage(), str);
}

