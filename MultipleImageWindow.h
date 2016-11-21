#pragma once
#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>

class IconWidget;
class MultipleImageWindow : public QMainWindow
{
	Q_OBJECT
public:
	MultipleImageWindow(QWidget * parent = Q_NULLPTR);
	~MultipleImageWindow();

	void AddImage(const std::string& imgPath);
	void AddImage(const std::list<std::string>& imgPathList);
private:
	bool IsExitFilePath(const std::string& imgPath);
protected:
	std::list<IconWidget*> m_iconList;
	QWidget* m_containWidget;
	QGridLayout* m_layout;
};