#pragma once

#include <QDialog>

#include "ui_InputTextDialog.h"

class InputTextDialog : public QDialog
{
	Q_OBJECT

public:
	InputTextDialog(QWidget* parent = Q_NULLPTR);
	~InputTextDialog();

	QString GetTextEditString();

private:
	Ui::InputTextDialog ui;
};