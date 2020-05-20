#ifndef QMLMQTTMONARKCLIENT_H
#define QMLMQTTMONARKCLIENT_H

#include <QObject>
#include <QMqttClient>

class QmlMqttMonarkClient : public QObject
{
    Q_OBJECT
public:
    explicit QmlMqttMonarkClient(QObject *parent = nullptr);

    enum Mode {
        POWER,
        KP,
        SIMULATION
    };
    Q_ENUMS(Mode)

    Q_PROPERTY(int targetPower READ targetPower WRITE setTargetPower NOTIFY targetPowerChanged)
    Q_PROPERTY(double targetKp READ targetKp WRITE setTargetKp NOTIFY targetKpChanged)
    Q_PROPERTY(int currentPower READ currentPower NOTIFY currentPowerChanged)
    Q_PROPERTY(int currentCadence READ currentCadence NOTIFY currentCadenceChanged)
    Q_PROPERTY(Mode mode READ mode WRITE setMode NOTIFY modeChanged)

public slots:
    int targetPower() const;
    double targetKp() const;
    int currentPower() const;
    int currentCadence() const;
    Mode mode() const;

    void setTargetPower(int newTargetPower);
    void setTargetKp(double newTargetKp);
    void setMode(Mode newMode, bool noPublish = false);

    void incGear();
    void incGearLots();
    void decGear();
    void decGearLots();

private slots:
    void onMqttConnected();
    void onMqttDisconnected();
    void onMqttMessage(const QByteArray &message, const QMqttTopicName &topic);

    void setCurrentPower(int newPower);
    void setCurrentCadence(int newCadence);

signals:
    void targetPowerChanged();
    void targetKpChanged();
    void currentPowerChanged();
    void currentCadenceChanged();
    void modeChanged();

private:
    int m_targetPower;
    double m_targetKp;
    int m_currentPower;
    int m_currentCadence;
    Mode m_mode;

    QMqttClient m_mqttClient;
};

#endif // QMLMQTTMONARKCLIENT_H
