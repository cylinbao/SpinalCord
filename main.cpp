#include "spinalcord.h"
#include <QApplication>
#include <QtSerialPort/QSerialPort>
#include <QFile>
#include <QString>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSerialPort serialPort;
    QString serialPortName = "/dev/rfcomm0";
    serialPort.setPortName(serialPortName);

    QTextStream standardOutput(stdout);

    int serialPortBaudRate = 9600;
    serialPort.setBaudRate(serialPortBaudRate);

    if (!serialPort.open(QIODevice::ReadOnly)) {
        standardOutput << QObject::tr("Failed to open port %1, error: %2").arg(serialPortName).arg(serialPort.errorString()) << endl;
        return 1;
    }

    standardOutput << "Start spinalcord" << endl;

    spinalcord w(&serialPort);
    w.show();

    return a.exec();
}
