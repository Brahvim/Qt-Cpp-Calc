#pragma once

#include <QWidget>
#include <QLineEdit>

class CEditor : public QLineEdit
{
	Q_OBJECT;

public:
	~CEditor();
	explicit CEditor(QWidget *parent = nullptr);
	explicit CEditor(QString const &placeholderText, QWidget *parent = nullptr);

	void keyPressEvent(QKeyEvent *p_event) final override;
};
