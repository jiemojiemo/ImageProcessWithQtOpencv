#include "Magic/TextPainterImpl.h"
#include <QPainter>
QImage PaintTextOnQImge(QImage& img, const QString& text)
{
	QImage newImg = img.copy();
	QPainter painter(&newImg);
	painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
	//�ı仭�ʺ�����
	QPen pen = painter.pen();
	pen.setColor(Qt::red);
	QFont font = painter.font();
	font.setBold(true);//�Ӵ�
	font.setPixelSize(50);//�ı������С

	painter.setPen(pen);
	painter.setFont(font);

	painter.drawText(newImg.rect(), Qt::AlignCenter, text);
	//��Helloд��Image������
	return newImg;
}

QImage TextPainterImpl::PaintText(MImage& img, const std::string& text)
{
	QString str = QString::fromStdString(text);
	return PaintTextOnQImge(img.GetQImage(), str);
}

