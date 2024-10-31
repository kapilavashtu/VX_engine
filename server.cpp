#include "server.h"
#include "defines.h"
#include <iostream>


Server::Server(quint16 nPort, QWidget* pwgt /*=0*/) : QWidget(pwgt) , m_nNextBlockSize(0)
{
    Init();
    initTabCommands();
    sequence_num = 0;
    pServer = new QTcpServer(this);

    if (!pServer->listen(QHostAddress::Any, nPort))
    {
#ifdef DEBUG
        qDebug() << "Server Error , Unable to start the server:" << '\n';
        emit signalSaveLog("\t * Server Error , Unable to start the server:");
#endif
        pServer->close();
        return;
    }

    if(nPort == 2323)
    {
        connect(pServer,&QTcpServer::newConnection, this, &Server::slotNewTabConnection);
#ifdef DEBUG
        qDebug()<<"start TAB server";
        emit signalSaveLog("\t * start TAB server");
#endif
    }

    if(nPort == 2424)
    {
        connect(pServer,&QTcpServer::newConnection, this, &Server::slotNewEthConnection);
#ifdef DEBUG
        qDebug()<<"start ETH server";
        emit signalSaveLog("\t * start ETH server");
#endif
    }
}


Server::~Server()
{
    if(eth_open_state)
    {
        yClientSocket->close();
        //pServer ->close();
#ifdef DEBUG
        std::cout << "eth socket is closed  \r\n";
#endif
    }

    if(tab_open_state)
    {
        xClientSocket->close();
        //pServer ->close();
#ifdef DEBUG
        std::cout << "tab socket is closed  \r\n";
#endif
    }
    pServer->close();
#ifdef DEBUG
    std::cout << "server is closed \r\n";
#endif

}


void Server::Init()
{
    eth_open_state = false;
    tab_open_state = false;
    input_states = 0;
    device_states = 0;
    fault_states = 0;
    sys_data = 0;
    rx_counter = 0;
    tx_counter = 0;
    wire_error_counter = 0;
    x_counter = 0;

    for (int i = 0; i < 64; i++)
    {
        data_block[i] = 0;
    }

    for (int i = 0; i < 64; i++)
    {
        inputs_states[i] = 0;
    }
#ifdef DEBUG
    qDebug()<<"server init";
    emit signalSaveLog("\t * init server");
#endif

}


void Server::slotNewTabConnection()
{
    QTcpSocket* clientSocket = pServer->nextPendingConnection();
    xClientSocket = clientSocket;
    tab_open_state = true;
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::deletedInfo);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::slotIsTabDisconnected);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::slotReadTabClient);
    emit newTabConnect();
#ifdef DEBUG
    qDebug()<<"new tab connection";
    emit signalSaveLog("\t * new tab connection");
#endif
}


void Server::slotNewEthConnection()
{
    QTcpSocket* clientSocket = new QTcpSocket;
    clientSocket = pServer->nextPendingConnection();
    yClientSocket = clientSocket;
    eth_open_state = true;
    m_nNextBlockSize = 0;
    //connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::destroyed, clientSocket, &QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::deletedInfo);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::slotIsEthDisconnected);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::slotReadEthClient);
#ifdef DEBUG
    qDebug()<<"new eth connection";
    emit signalSaveLog("\t * new eth connection");
#endif
}


void Server::slotIsTabDisconnected()
{
#ifdef DEBUG
    //qDebug()<<"tab disconnection";
    //emit signalSaveLog("\t * tab disconnection");
#endif
    tab_open_state = false;
}


void Server::slotIsEthDisconnected()
{
#ifdef DEBUG
    //qDebug()<<"eth disconnection";
    //emit signalSaveLog("\t * eth disconnection");
#endif
    eth_open_state = false;
}


void Server::slotReadTabClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    for (;;)
    {
        if (!m_nNextBlockSize)
        {
            if (pClientSocket->bytesAvailable() < (int)sizeof(quint16))
            {
                break;
            }

        }
        QByteArray saveData = pClientSocket->readAll();
        QJsonDocument doc(QJsonDocument::fromJson(saveData));
        QString cmd = doc.object().value("cmd").toString();
        parseTabCommand(cmd);
        m_nNextBlockSize = 0;
    }
}


void Server::slotReadEthClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    //qDebug()<<"rx bytes available = " << pClientSocket->bytesAvailable();
    in.setVersion(QDataStream::Qt_5_3);
    for (;;)
    {
        if (!m_nNextBlockSize)
        {
            if (pClientSocket->bytesAvailable() < (int)sizeof(quint16))
            {
                //qDebug()<<"rx bytes available < 16 bit";
                break;
            }

            in >> m_nNextBlockSize;
            //qDebug()<<"in >> m_nNextBlockSize = " << m_nNextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < m_nNextBlockSize)
        {
            // qDebug()<<"segment not full";
            break;
        }

        QString word;
#ifdef LINQ
        for(int i = 0; i < 64; i++)
        {
            in >> data_block[i];
        }
        unPack(data_block);
        emit signalNewEthRxData(&input_states);
#endif
        m_nNextBlockSize = 0;
    }
}


void Server::binPrint()
{
    std::cout << "inputs:";
    for(int i = 63; i >= 0; i--)
    {
        if(BIT_IS_SET(input_states, i)) std::cout << '1';
        else std::cout << '0';
    }
}


void Server::unPack(quint8 *ptr)
{
    CopyData((quint8 *) &input_states, (ptr + INPUTS_OFFSET), INPUTS_BLOCK_SIZE);
    CopyData((quint8 *) &device_states, (ptr + DEVICE_OFFSET), DEVICES_BLOCK_SIZE);
    CopyData((quint8 *) &fault_states, (ptr + FAULT_OFFSET), FAULT_BLOCK_SIZE);
    CopyData((quint8 *) &sys_data, (ptr + SYS_OFFSET), SYS_BLOCK_SIZE);
    CopyData((quint8 *) &rx_counter, (ptr + RX_COUNTER_OFFSET), RX_COUNTER_SIZE);
    CopyData((quint8 *) &tx_counter, (ptr + TX_COUNTER_OFFSET), TX_COUNTER_SIZE);
    CopyData((quint8 *) &wire_error_counter, (ptr + WIRE_CRC_ERROR_OFFSET), WIRE_CRC_ERROR_SIZE);
    CopyData((quint8 *) &x_counter, (ptr + X_COUNTER_OFFSET), X_COUNTER_SIZE);

#ifdef SERVER_DEBUG
    //std::cout <<"input_states = " << input_states << '\t';
    //std::cout <<"device_states = " << device_states << '\t';
    //std::cout <<"fault_states = " << fault_states << '\t';
    //std::cout <<"sys_data = " << sys_data << '\t';
    ////std::cout <<"rx_counter = " << rx_counter << '\t';
    ////std::cout <<"tx_counter = " << tx_counter << '\t';
    //std::cout <<"wire_error_counter = " << wire_error_counter << '\t';
    //std::cout <<"x_counter = " << x_counter << '\t';
    ///binPrint();
    std::cout <<'\r';
#endif

}


void Server::parseTabCommand(QString val)
{
    QString message = "\t *** recieve tab command = " + val;
    emit signalSaveLog(message);

    if(val == "game_start") emit signalStartGame();
    else if(val == "service") emit signalServiceMode();
    else if(val == "show") emit showMainWindow();
    else if(val == "stop_game") emit signalStopGame();
    else if(val == "inc_timer") emit signalIncTimer();
    else if(val == "dec_timer") emit signalDecTimer();
    else if(val == "start_anm") emit signalStartScreamer();
    else if(val == "dn_scream") emit signalDoneScream();
    else if(val == "go3room") emit signalGoRoom3();
    else if(val == "dn_evac") emit signalDoneEvacuation();
    else if(val == "dn_sock") emit signalDoneSockets();
    else if(val == "dn_key_pnl") emit signalDoneKeyPanel();
    else if(val == "dn_head")  emit signalDoneHead();
    else if(val == "dn_ct_sec") emit signalDoneCatchSeconds();
    else if(val == "dn_body") emit signalDoneBodyManeken();
    else if(val == "dn_memory") emit signalDoneMemorized();
    else if(val == "dn_photo") emit signalDonePhotoelements();
    else if(val == "dn_light") emit signalDoneLights();
    else if(val == "dn_puzzle") emit signalDonePuzzleBox();
    else if(val == "dn_big_box") emit signalDoneBigBox();
    else if(val == "dn_switch") emit signalDoneSwitches();
    else if(val == "exit") emit exit();
    else SetOutputState(val);
}


void Server::txTabLedData(QString command)
{
    if(tab_open_state)
    {
        QJsonObject cmd;
        QJsonObject params;
        cmd["cmd"] = command;
        QJsonDocument doc(cmd);
        const char endw = '\n';
        xClientSocket->write(doc.toJson(QJsonDocument::Compact));
        QByteArray end;
        end.append(endw);
        xClientSocket->write(end);
    }
}


void Server::txTabCommandData(QString command,QString text)
{
    if(tab_open_state)
    {
        QJsonObject cmd;
        QJsonObject params;

        cmd["cmd"] = command;
        params["text"] = text;
        cmd["params"] = params;

        QJsonDocument doc(cmd);
        const char endw = '\n';
        xClientSocket->write(doc.toJson(QJsonDocument::Compact));
        QByteArray end;
        end.append(endw);
        xClientSocket->write(end);

        QString message = "\t * txTabCommandData = " + command + ":" + text;
        emit signalSaveLog(message);
    }
}


void Server::sendTabTime(QString time)
{
    txTabCommandData("game_time",time);
    QString message = "\t\t\t\t\t\t\t\t\t game time " + time;
    emit signalSaveLog(message);
}


void Server::slotTxEthMkData(quint8 cntl, quint8 pin, quint8 state)
{
    quint32 limit_counter = 0;
    quint8 n_state = 0;
    while(!eth_open_state)
    {
        if(!n_state)
        {
            emit signalSaveLog("wait for ethernet server reconnect");
            n_state = 1;
            qDebug()<<"wait for ethernet server reconnect";
        }
        limit_counter++;
        if(limit_counter == 1000000000)
        {
            emit signalSaveLog("\t\t\t\t\t\t\t\t\t\t mk0 not response!");
            qDebug()<<"\t\t\t\t\t\t\t\t\t\t mk0 not response!";
            break;
        }
        //emit signalBlockEthernet Input Data +

    }

    if(eth_open_state)
    {
        QJsonObject cmd;
        cmd["cntl"] = cntl;
        cmd["pin"] = pin;
        cmd["state"] = state;
        cmd["seq"] = sequence_num;
        QJsonDocument doc(cmd);
        yClientSocket->write(doc.toJson(QJsonDocument::Compact));
        const char endw = '\n';
        QByteArray end;
        end.append(endw);
        yClientSocket->write(end);


        QString message = "\t * send to mk0 = cntl:" + QString::number(cntl) + " pin:" +  QString::number(pin) + " state:" +  QString::number(state) + " sequence number:" + QString::number(sequence_num);
        emit signalSaveLog(message);
        sequence_num++;
    }
}


void Server::ethSendData()
{
    if(eth_open_state)
    {
        //block (tx_data_block)
        yClientSocket->write((const char *) tx_data_block, 66);
        //unblock (tx_data_block)
    }
}


void Server::initTabCommands()
{
    for(int i = 0; i < 64; i++)
    {
        QString command = "sw" + QString::number(i) + "on";
        tabCommand << command;

    }

    for(int i = 0; i < 64; i++)
    {
        QString command = "sw" + QString::number(i) + "off";
        tabCommand << command;

    }

    tabCommandInterator = tabCommand.begin();

}


bool Server::SetOutputState(QString command)
{

    tabCommandInterator = tabCommand.begin();
    for(quint8 i = 0; i < 64; i++)
    {
        if(*tabCommandInterator == command)
        {
            emit signalSetPinState(8, i, 1);
#ifdef DEBUG
            //qDebug()<<"set output:" << i << "as HIGH";
#endif
            //QString message1 = "output:" + QString::number(i) + " as HIGH";
            //emit signalServiceData("diag",message1);
            return true;
        }
        tabCommandInterator++;
    }

    for(quint8 i = 0; i < 64; i++)
    {
        if(*tabCommandInterator == command)
        {
            emit signalSetPinState(8, i, 0);
#ifdef DEBUG
            //qDebug()<<"set output:" << i << "as LOW";
#endif
            //QString message2 = "output:" + QString::number(i) + " as LOW";
            //emit signalServiceData("diag",message2);
            return true;
        }
        tabCommandInterator++;
    }
    return false;
}


void Server::CopyData(quint8 *dest, quint8 *source, quint8 size)
{
    for(quint8 i = 0; i < size; i++)
    {
        dest[i] = source[i];
    }
}


quint16 Server::nTohs(quint16 hostshort)
{
    quint16 temp;
    quint8 *ptr_source = (quint8*) &hostshort;
    quint8 *ptr_dest = (quint8*) &temp;
    ptr_dest[0] = ptr_source[1];
    ptr_dest[1] = ptr_source[0];
    return temp;
}


void Server::deletedInfo()
{
#ifdef DEBUG
    //qDebug()<<"clientSocket is deleted";
#endif
    //write to log
}
