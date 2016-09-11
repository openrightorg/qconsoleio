import QtQuick 2.0
import QtQuick.Window 2.2
import ConsoleInOut 1.0

Item {
	visible: false
	property string prompt: "p: "

	ConsoleInOut {
		id: consoleio
		Component.onCompleted: {
			consoleio.write(prompt);
		}

		onReadLine: {
			consoleio.writeLine('in: ' + text);
			consoleio.write(prompt);
		}
	}
}

