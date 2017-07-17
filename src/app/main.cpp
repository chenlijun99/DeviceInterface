#include <QErrorMessage>

#include <Application.hpp>
#include <gui/MainWindow.hpp>

int main(int argc, char *argv[])
{
	Application app(argc, argv);
	MainWindow w;
	w.show();
	QObject::connect(&app, &Application::errorOccured,
					 &w, &MainWindow::errorOccured);
	return app.exec();
}
