// simple qml plugin to to read and write lines from console
// public domain

#include <QtQml>
#include <QQmlExtensionPlugin>
#include <QTextStream>
#include <QThread>

class QConsoleInOut : public QObject
{
	Q_OBJECT

public:
	explicit QConsoleInOut();

signals:
	void readLine(const QString &text);

protected:
	Q_INVOKABLE void writeLine(const QString &text);
	Q_INVOKABLE void write(const QString &text);

public slots:
	Q_INVOKABLE void readNotify();

private:
	QSocketNotifier notifier;
	QTextStream in;
	QTextStream out;
};

QConsoleInOut::QConsoleInOut() : notifier(fileno(stdin), QSocketNotifier::Read), in(stdin), out(stdout)
{
	connect(&notifier, SIGNAL(activated(int)), this, SLOT(readNotify()));
}

void QConsoleInOut::readNotify()
{
	QString line;
	if (in.readLineInto(&line)) {
		readLine(line);
	} else {
		notifier.setEnabled(false);
	}
}

void QConsoleInOut::writeLine(const QString &text)
{
	out << text << "\n";
	out.flush();
}

void QConsoleInOut::write(const QString &text)
{
	out << text;
	out.flush();
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

