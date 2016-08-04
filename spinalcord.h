#ifndef SPINALCORD_H
#define SPINALCORD_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QByteArray>
#include <QTextStream>
#include "qcustomplot.h"

namespace Ui {
class spinalcord;
}

class spinalcord : public QMainWindow
{
    Q_OBJECT

public:
    explicit spinalcord(QSerialPort *serialPort, QWidget *parent = 0);
    ~spinalcord();

    void setupPlotting(QCustomPlot *customPlot);
    void plotReceivedData(int recData);
    void calShortAve();

private slots:
    void serialPortReader();
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);
    void handleStartButton();

private:
    Ui::spinalcord *ui;
    QString demoName;
    QTimer dataTimer;
    QSerialPort *m_serialPort;
    QTextStream m_standardOutput;
    QPushButton *m_startButton;
    int countForReplot;
    bool startFlag, signalFlagF, signalFlagB;
    quint64 accumulation, counter;
    int shortArray[5], BigArray[20], smallArray[30];
    int longAve, shortAve;
    int minBig, maxBig, maxSmall;
};

#endif // SPINALCORD_H
