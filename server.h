#ifndef SERVER_H
#define SERVER_H


#include <QWidget>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QtEndian>
#include <QTimer>
#include <QTcpSocket>
#include <QTcpServer>
#include <QtEndian>
#include <QtNetwork>
#include <QtWidgets>
#include <QHostAddress>
#include <QFile>
#include <QDebug>

#include "data.h"

class Server : public QWidget
{
    Q_OBJECT

    quint16 m_nNextBlockSize;
    bool tab_open_state;
    bool eth_open_state;

    QTcpServer* pServer;


    QTcpSocket* xClientSocket;
    QTcpSocket* yClientSocket;

    void Init();
    void initTabCommands();
    void parseTabCommand(QString val);
    bool SetOutputState(QString command);

public:
    Server(quint16 nPort, QWidget* pwgt = nullptr);
    ~Server();
    void unPack(quint8 *ptr);
    void CopyData(quint8 *dest, quint8 *source, quint8 size);
    uint16_t nTohs(uint16_t hostshort);
    void binPrint();

    quint8 inputs_states[64];
    QTimer *f_timer;
    quint16 sequence_num;

    //MK recieve data
    quint64 input_states;
    quint64 device_states;
    quint64 fault_states;
    quint64 sys_data;
    quint64 rx_counter;
    quint64 tx_counter;
    quint64 wire_error_counter;
    quint64 x_counter;

    //MK tx data(command to mk from worker)
    quint8 tx_data_block[66];

    //only data block = segment - header (64 byte)
    quint8 data_block[64];

    QList<QString> tabCommand;
    QList<QString>::iterator tabCommandInterator;

Q_SIGNALS:
    void newEthConnect();
    void newTabConnect();

    void ethDisconnect();
    void tabDisconnect();
    void ehtDataRecieved();
    void exit();
    void showMainWindow();

    void signalNewEthRxData(quint64 *inputs_states);
    void signalNewEthData(quint8 *val);
    void signalServiceData(QString cmd,QString message);

    void signalScreamerAction1();
    void signalScreamerAction2();
    void signalSetPinState(quint8 cntl,quint8 pin, quint8 state);
    void signalSaveLog(QString message);

//! from tab to worker signals
    void signalStartGame();
    void signalServiceMode();
    void signalStopGame();

    void signalIncTimer();
    void signalDecTimer();

    void signalStartScreamer();
    void signalGoRoom3();

    void signalDoneEvacuation();
    void signalDoneSockets();
    void signalDoneKeyPanel();
    void signalDoneHead();
    void signalDoneScream();
    void signalDoneCatchSeconds();
    void signalDoneBodyManeken();
    void signalDoneMemorized();
    void signalDonePhotoelements();
    void signalDoneLights();
    void signalDonePuzzleBox();
    void signalDoneBigBox();
    void signalDoneSwitches();

public Q_SLOTS:

    void deletedInfo();

    virtual void slotNewTabConnection();
    virtual void slotNewEthConnection();

    void slotReadTabClient();
    void slotReadEthClient();

    void txTabLedData(QString command);
    void txTabCommandData(QString command,QString text);
    void sendTabTime(QString time);

    void slotTxEthMkData(quint8 cntl, quint8 pin, quint8 state);
    void ethSendData();

    void slotIsTabDisconnected();
    void slotIsEthDisconnected();

};


#endif // SERVER_H
