#ifndef SPINALCORD_H
#define SPINALCORD_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QByteArray>
#include <QTextStream>
#include <QSoundEffect>
#include "qcustomplot.h"

#define bigArraySize 20
#define smallArraySize 30

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
    void setupSound();
    void decodeToBinary(int dec);

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
    QSoundEffect effect;
    int countForReplot;
    bool startFlag, stimFlag;
    bool windowStart;
    bool saveFlag;
};

#endif // SPINALCORD_H
