#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <QApplication>

class Application final : public QApplication {
	Q_OBJECT
public:
	Application(int& argc, char** argv) : QApplication(argc, argv) {}
	virtual bool notify(QObject *receiver, QEvent *event) override {
		try {
			return QApplication::notify(receiver, event);
		} catch (const std::runtime_error& e) {
			emit errorOccured(QString("Runtime error occured: %1").
							  arg(e.what()));
		}
		catch(const std::exception& e) {
			emit errorOccured(QString("Error occured: %1").
							  arg(e.what()));
		}
		catch(...) {
			emit errorOccured(QString("Unknown error occured"));
		}

		return false;
	}

signals:
	void errorOccured(const QString &errorMessage);

};


#endif // APPLICATION_HPP
