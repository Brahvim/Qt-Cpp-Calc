#include <QKeyEvent>

#include "Main.hpp"
#include "CEditor.hpp"

CEditor::CEditor(QString const &p_str, QWidget *p_parent) : QLineEdit(p_str, p_parent) { }
CEditor::CEditor(QWidget *p_parent) : QLineEdit(p_parent) { }
CEditor::~CEditor() { }

// Qt events run IN SYNC! They can't use the signals and slots system AT ALL.
// That absolute genius is async and ascends all your threading problems to heaven.
void CEditor::keyPressEvent(QKeyEvent *p_event) {
	QLineEdit::keyPressEvent(p_event); // Call the parent method or wonder why key presses don't trigger signals!

	if (p_event->key() == Qt::Key_Escape) {

		g_app->exit();
		// this->close(); // What if we're not the only `QWidget`?!
		p_event->accept();

	}
}
