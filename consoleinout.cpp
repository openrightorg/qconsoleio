// simple qml plugin to to read and write lines from console
// public domain

#include <QtQml>
#include <QQmlExtensionPlugin>
#include <QTextStream>
#include <QThread>

class QConsoleInOut : public QThread
{
private:
	Q_OBJECT

public:
	explicit QConsoleInOut();

signals:
	void readLine(const QString &text);

protected:
	Q_INVOKABLE void writeLine(const QString &text);
	Q_INVOKABLE void write(const QString &text);

	void run();
};

QConsoleInOut::QConsoleInOut() : QThread()
{
	QThread::start();
}

void QConsoleInOut::run()
{
	QTextStream in(stdin);
	QString line;
	while (in.readLineInto(&line)) {
		readLine(line);
	}
}

void QConsoleInOut::writeLine(const QString &text)
{
	QTextStream out(stdout);
	out << text << "\n";
}

void QConsoleInOut::write(const QString &text)
{
	QTextStream out(stdout);
	out << text;
}

class QConsoleInOutQmlPlugin : public QQmlExtensionPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
	void registerTypes(const char *uri)
	{
		qmlRegisterType<QConsoleInOut>(uri, 1, 0, "ConsoleInOut");
	}
};

#include "consoleinout.moc"

