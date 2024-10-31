#ifndef VXTIMER_H
#define VXTIMER_H

#include <QtWidgets>

class VxTimer : public QLabel
{
    Q_OBJECT

    int minutes;
    int seconds;
    int pause_minutes;
    int pause_seconds;
    bool switch_done;

public:
    VxTimer(QWidget *parent = nullptr);
    ~VxTimer();
    QString common_time;
    QString game_time;

    QTimer *xtimer;
    QTimer *game_timer;
    QTimer *logfile_tick;
    quint32 val;

Q_SIGNALS:
    void updateTimer(QString time);
    void workerTick(quint32 val);
    void updateGameTimer(const QString &str);
    void updateGameTimerTab(const QString &str);

    void introStarting(int track);
    void endTimer();
    void signalFiveMinLeft();
    void signalThreeMinLeft();
    void countDown();
    void signalLogTimer();

public Q_SLOTS:
    void slotWorkerTick();
    void slotSetFiveMin();

    void slotUpdateGameDateTime();
    void slotStartGameTimer();
    void slotStopGameTimer();

    void gameTimerPause();
    void gameTimerPlay();

    void slotIncTimer();
    void slotDecTimer();

    void resetTimer();
    void logTimer();
};

#endif // VXTIMER_H
