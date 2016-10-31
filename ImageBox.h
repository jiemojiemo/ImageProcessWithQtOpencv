#pragma once
#include <QWidget>
#include <QImage>
#include <QPixmap>


class ImageBox : public QWidget
{
	Q_OBJECT
public:
	enum PB_MODE { FIXED_SIZE, FIX_SIZE_CENTRED, AUTO_ZOOM, AUTO_SIZE };
	explicit ImageBox(QWidget *parent = 0);
	void setMode(PB_MODE mode);
	~ImageBox();
private:
	QPixmap m_pixmap;
	double m_scale;
	PB_MODE m_mode;
	QBrush m_brush;
protected:
	void paintEvent(QPaintEvent * event);
signals:

	public slots :
	bool setImage(QImage &image, double scale = 1.0);
	void setBackground(QBrush brush);
};

