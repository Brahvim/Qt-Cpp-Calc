#include <QFontMetrics>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QWidget>
#include <QScreen>
#include <QString>
#include <QLabel>

#include <iostream>
#include <sstream>
#include <string>

#include "Main.hpp"
#include "CEditor.hpp"

// "Heap `QObject` allocations are frowned upon!"
QApplication const *g_app;
// <:)!

int main(int p_argc, char *p_argv[]) {
	g_app = new QApplication(p_argc, p_argv);

	QVBoxLayout *layout = new QVBoxLayout;

	QWidget *container = new QWidget;
	container->setLayout(layout);

	CEditor *editor = new CEditor(QStringLiteral("Ain't mathin', yo' head, yo?"), container);
	editor->setToolTip("Type math expressions in this box!");
	editor->setAlignment(Qt::AlignCenter);

	QLabel *status = new QLabel(QStringLiteral("Ready!"), container); // I disable `QStatusBar`s' "grip" and they don't have text!
	status->setAlignment(Qt::AlignCenter);

	layout->addWidget(status);
	layout->addWidget(editor);

	container->show();
	editor->setMinimumWidth(editor->width());
	container->setMinimumWidth(container->width());

	{ // Move to the center :)!
		QScreen *screen = QGuiApplication::screenAt(container->pos());
		QSize point = screen->size();

		int const h = point.height();
		int const w = point.width();

		container->move(
			w / 2 - container->width() / 2,
			h / 2 - container->height() / 2
		);
	}

	// Resizing that's A LOT simpler than an HTML `<textarea>`'s:
	QObject::connect(editor, &QLineEdit::textChanged, [container, editor]() {

		// FOUND ON A MAILING LIST!!!
		// I feel BLESSED!
		// ...
		//
		// [ https://lists.qt-project.org/pipermail/qt-interest-old/2010-May/022744.html ]:

		int const w = editor->fontMetrics().boundingRect(editor->text()).width() + 5;
		QScreen *screen = QGuiApplication::screenAt(container->pos());
		int const max = screen->size().width() / 4;

		editor->setMaximumWidth(max);
		editor->resize(w, editor->height());

		container->setMaximumWidth(max + 20);
		container->resize(w + 20, container->height());

	});

	// Calculates stuff when you `Enter` it!:
	QObject::connect(editor, &CEditor::returnPressed, [editor]() {

		std::stringstream ss(editor->text().toLocal8Bit().data());
		// std::stringstream ss(editor->text().toUtf8().data());
		double one; char op; double two;

		// C++ is the hardest to parse. Ever.
		// THAT'S why it comes with THE BEST parsers EVER!!!
		// BEST small lang/expr parsing API thingy EVER! WOOOH!!!:
		if (!(ss >> one >> op >> two)) {

			return;

		}

		double result = 0;

		switch (op) {

			case '+': {

				result = one + two;

			} break;

			case '-': {

				result = one - two;

			} break;

			case '*': {

				result = one * two;

			} break;

			case '/': {

				if (one && two) {

					result = one / two;

				}

			} break;

			default: {

				// Maybe just `return`.
				// Maybe put this in the `QLineEdit`: "Unknown operator".
				// ...
				// Maybe put that text on a *status bar!*

			} break;

		}

		editor->setText(QString::number(result));

	});

	int const ret = g_app->exec();
	// delete g_app; // Apparently `QApplication::exit()` handles this...?!
	return ret;
}
