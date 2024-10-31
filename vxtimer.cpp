#include "vxtimer.h"


VxTimer::VxTimer(QWidget *parent) : QLabel(parent)
{
    xtimer = new QTimer(this);
    game_timer = new QTimer(this);
    logfile_tick = new QTimer(this);
    switch_done = false;

    connect(xtimer, &QTimer::timeout, this, &VxTimer::slotWorkerTick);
    connect(game_timer, &QTimer::timeout, this, &VxTimer::slotUpdateGameDateTime);
    connect(logfile_tick, &QTimer::timeout, this, &VxTimer::logTimer);
    //xtimer->start(WORKER_TIMER_INTERVAL);
    logfile_tick -> start(600000);
    val = 0;
    slotWorkerTick();
}

VxTimer::~VxTimer()
{

}

void VxTimer::slotWorkerTick()
{
    //common_time = QDateTime::currentDateTime().toString(Qt::DefaultLocaleShortDate);
    //setText("<H2><CENTER>" + common_time + "</CENTER></H2>");
    val++;
    emit workerTick(val);
}

void VxTimer::slotUpdateGameDateTime()
{
    if(!seconds)
    {
        if(minutes < 10) game_time = '0' + QString::number(minutes) + ':' + '0' + QString::number(seconds);
        else game_time = QString::number(minutes) + ':' + '0' + QString::number(seconds);
        minutes--;
        seconds = 59;
    } else
    {

        if(seconds < 10)
        {
            if(minutes < 10) game_time = '0' + QString::number(minutes) + ':' + '0' + QString::number(seconds);
            else game_time = QString::number(minutes) + ':' + '0' + QString::number(seconds);
            seconds--;

        } else

        {
            if(minutes < 10) game_time = '0' + QString::number(minutes) + ':' + QString::number(seconds);
            else game_time = QString::number(minutes) + ':' + QString::number(seconds);
            seconds--;
        }

    }

    if(minutes == 0 && seconds == 00)
    {
        game_time = "YOU DEAD!";
        game_timer->stop();
        emit endTimer();
        switch_done = false;

    }
    emit updateGameTimer(game_time);
    emit updateGameTimerTab(game_time);

    if((minutes == 59) && (seconds == 49)) emit introStarting(0);
    if((minutes == 5) && (seconds == 0) && (!switch_done)) emit signalFiveMinLeft();
    if((minutes == 3) && (seconds == 0)) emit signalThreeMinLeft();
    if((minutes == 2) && (seconds == 30)) emit countDown();
}

void VxTimer::slotStartGameTimer()
{
    qDebug()<<"slotStartGameTimer";
    game_timer -> start(1000);
    minutes = 59;
    seconds = 59;
    slotUpdateGameDateTime();
}

void VxTimer::slotStopGameTimer()
{
    qDebug()<<"slotStopGameTimer";
    game_timer->stop();
}

void VxTimer::gameTimerPause()
{
    qDebug()<<"gameTimerPause";
    pause_minutes = minutes;
    pause_seconds = seconds;

}

void VxTimer::gameTimerPlay()
{
    qDebug()<<"gameTimerPlay";
    minutes = pause_minutes;
    seconds = pause_seconds;

}

void VxTimer::slotIncTimer()
{
    if(minutes < 50) minutes += 5;
}

void VxTimer::slotDecTimer()
{
    if(minutes > 10) minutes -= 5;
}

void VxTimer::slotSetFiveMin()
{
    minutes = 5;
    seconds = 46;
    switch_done = true;
}

void VxTimer::resetTimer()
{
    game_timer -> stop();
    minutes = 0;
    seconds = 0;
}

void VxTimer::logTimer()
{
    emit signalLogTimer();
    qDebug() << "log timer click";
}
