#include "InputTextDialog.h"

InputTextDialog::InputTextDialog(QWidget* parent /*= Q_NULLPTR*/):
	QDialog(parent)
{
	ui.setupUi(this);
}

InputTextDialog::~InputTextDialog()
{

}

QString InputTextDialog::GetTextEditString()
{
	return ui.textEdit_2->toPlainText();
}

