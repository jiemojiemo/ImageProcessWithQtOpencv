#pragma once
#include <QDialog>
#include "ui_SaveImageDialog.h"

class SaveImageDialog : public QDialog
{
public:
	SaveImageDialog(QWidget* parent = Q_NULLPTR);
	~SaveImageDialog() = default;
private:
	Ui::SaveImageDialog ui;
};