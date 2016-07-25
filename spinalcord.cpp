#include "spinalcord.h"
#include "ui_spinalcord.h"
#include <iostream>

#define dataTreshold 10
#define colorTreshold 500
#define timeInterval 500
#define numToReplot 5

spinalcord::spinalcord(QSerialPort *serialPort, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::spinalcord),
    m_serialPort(serialPort),
    m_standardOutput(stdout)
{
    ui->setupUi(this);

    QPushButton *m_startButton = ui->startButton;
    connect(m_startButton, SIGNAL(released()),this, SLOT(startPlot());

    setupPlotting(ui->customPlot);

    countForReplot = 0;

    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(serialPortReader()));
    dataTimer.start(timeInterval);
}

spinalcord::~spinalcord()
{
    delete ui;
}

void spinalcord::serialPortReader()
{
    connect(m_serialPort, SIGNAL(readyRead()), SLOT(handleReadyRead()));
    //connect(m_serialPort, SIGNAL(error(QSerialPort::SerialPortError)), SLOT(handleError(QSerialPort::SerialPortError)));
}

void spinalcord::handleReadyRead()
{
    if(m_serialPort->canReadLine()){
    char buf[5];
    qint64 lineLength = m_serialPort->readLine(buf, sizeof(buf));
    if (lineLength != -1) {
        // the line is available in buf
        //std::cout << buf;
        int recData = std::atoi(buf);
        m_standardOutput << "Recieved data is: " << recData << endl;
        if(recData > dataTreshold)
            plotReceivedData(recData);
        else
            plotReceivedData(0);
    }
    }
    if(!dataTimer.isActive())
        dataTimer.start(timeInterval);
}

void spinalcord::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        m_standardOutput << QObject::tr("An I/O error occurred while reading the data from port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
        QCoreApplication::exit(1);
    }
}

void spinalcord::setupPlotting(QCustomPlot *customPlot)
{
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
    QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
#endif
    demoName = "Real Time Data Demo";

    // include this section to fully disable antialiasing for higher performance:
    ///*
    customPlot->setNotAntialiasedElements(QCP::aeAll);
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    customPlot->xAxis->setTickLabelFont(font);
    customPlot->yAxis->setTickLabelFont(font);
    customPlot->legend->setFont(font);
    //*/
    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    //customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    customPlot->graph(0)->setAntialiasedFill(false);

    customPlot->addGraph(); // blue dot
    customPlot->graph(1)->setPen(QPen(Qt::blue));
    customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);


    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    customPlot->xAxis->setAutoTickStep(false);
    customPlot->xAxis->setTickStep(2);
    customPlot->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
}

void spinalcord::plotReceivedData(int value0)
{
    // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
    double key = 0;
#else
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
#endif

    static double lastPointKey = 0;
    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
        // add data to lines:
        ui->customPlot->graph(0)->addData(key, value0);
        // set data of dots:
        //ui->customPlot->graph(1)->clearData();
        ui->customPlot->graph(1)->addData(key, value0);
        // remove data of lines that's outside visible range:
        ui->customPlot->graph(0)->removeDataBefore(key-8);
        // rescale value (vertical) axis to fit the current data:
        ui->customPlot->graph(0)->rescaleValueAxis();
        lastPointKey = key;
    }

    ///*
    if(countForReplot == numToReplot){
        if(value0 < colorTreshold){
            ui->customPlot->graph(0)->setPen(QPen(Qt::red));
            ui->customPlot->graph(1)->setPen(QPen(Qt::red));
        }
        else{
            ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
            ui->customPlot->graph(1)->setPen(QPen(Qt::blue));
        }

        // make key axis range scroll with the data (at a constant range size of 8):
        ui->customPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
        ui->customPlot->replot();

        countForReplot = 0;
    }
    else
        countForReplot++;
    //*/
    // calculate frames per second:
    ///*
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
        ui->statusBar->showMessage(
                QString("%1 FPS, Total Data points: %2")
                .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                .arg(ui->customPlot->graph(0)->data()->count()+ui->customPlot->graph(1)->data()->count())
                , 0);
        lastFpsKey = key;
        frameCount = 0;
    }
    //*/
}

void spinalcord::startPlot()
{
    m_startButton->setText("Stop");
}
