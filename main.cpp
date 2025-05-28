#include <QPushButton>
#include <QApplication>

#include "CMyObject.hpp"

int main(int p_argc, char *p_argv[]) {
	QApplication app(p_argc, p_argv);

	QPushButton button("Click me, nerd!");
	button.resize(200, 60);
	button.show();

	CMyObject a(&button);

	QObject::connect(&button, &QPushButton::clicked, []() {

		qInfo("You clicked the button! Nice job, champ!");

	});

	return app.exec();
}
