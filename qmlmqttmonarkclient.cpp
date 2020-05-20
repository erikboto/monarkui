#include "qmlmqttmonarkclient.h"

#define TARGET_POWER "monark/target/power"
#define TARGET_SET_POWER "monark/target/set/power"

#define TARGET_KP "monark/target/kp"
#define TARGET_SET_KP "monark/target/set/kp"

#define DETAILS_MODE "monark/details/mode"
#define DETAILS_SET_MODE "monark/details/set/mode"

#define DETAILS_NAME "monark/details/name"
#define DETAILS_MODEL "monark/details/model"
#define CURRENT_POWER "monark/current/power"
#define CURRENT_KP "monark/current/kp"
#define CURRENT_CADENCE "monark/current/cadence"
#define CURRENT_HEARTRATE "monark/current/heartrate"

#define GEARSHIFT "monark/control/gearshift"

QmlMqttMonarkClient::QmlMqttMonarkClient(QObject *parent) : QObject(parent)
  , m_targetPower(0)
  , m_targetKp(0)
  , m_currentPower(0)
  , m_currentCadence(0)
  , m_mode(POWER)
{
    connect(&m_mqttClient, &QMqttClient::connected, this, &QmlMqttMonarkClient::onMqttConnected);
    connect(&m_mqttClient, &QMqttClient::disconnected, this, &QmlMqttMonarkClient::onMqttDisconnected);
    connect(&m_mqttClient, &QMqttClient::messageReceived, this, &QmlMqttMonarkClient::onMqttMessage);

    m_mqttClient.setClientId("MonarkUI");
    m_mqttClient.setPort(1883);
    m_mqttClient.setHostname("localhost");
    m_mqttClient.connectToHost();
}

void QmlMqttMonarkClient::onMqttConnected()
{
    m_mqttClient.subscribe(QMqttTopicFilter("monark/#"));
}

void QmlMqttMonarkClient::onMqttDisconnected()
{
}

void QmlMqttMonarkClient::setCurrentCadence(int newCadence)
{
    if (m_currentCadence == newCadence)
    {
        return;
    }

    m_currentCadence = newCadence;
    emit currentCadenceChanged();
}

void QmlMqttMonarkClient::setCurrentPower(int newPower)
{
    if (m_currentPower == newPower)
    {
        return;
    }

    m_currentPower = newPower;
    emit currentPowerChanged();
}

void QmlMqttMonarkClient::onMqttMessage(const QByteArray &message, const QMqttTopicName &topic)
{
    qDebug() << "onMqttMessage: " << QString::fromLocal8Bit(message) << " " << topic.name();
    QString msg = QString::fromUtf8(message);
    if (topic.name() == CURRENT_POWER)
    {
        bool ok;
        int pwr = msg.toInt(&ok);
        if (ok)
        {
            setCurrentPower(pwr);
        }
    }
    else if (topic.name() == CURRENT_CADENCE)
    {
        bool ok;
        int cad = msg.toInt(&ok);
        if (ok)
        {
            setCurrentCadence(cad);
        }
    }
    else if (topic.name() == TARGET_POWER)
    {
        bool ok;
        int pwr = msg.toInt(&ok);
        if (ok)
        {
            setTargetPower(pwr);
        }
    }
    else if (topic.name() == TARGET_KP)
    {
        bool ok;
        double kp = msg.toDouble(&ok);
        if (ok)
        {
            setTargetKp(kp);
        }
    }
    else if (topic.name() == DETAILS_MODE)
    {
        if (msg == "power")
        {
            setMode(Mode::POWER, true);
        } else if (msg == "kp")
        {
            setMode(Mode::KP, true);
        } else if (msg == "simulation")
        {
            setMode(Mode::SIMULATION, true);
        }
    }
}

int QmlMqttMonarkClient::targetPower() const
{
    return m_targetPower;
}

double QmlMqttMonarkClient::targetKp() const
{
    return m_targetKp;
}

int QmlMqttMonarkClient::currentPower() const
{
    return m_currentPower;
}

int QmlMqttMonarkClient::currentCadence() const
{
    return m_currentCadence;
}

QmlMqttMonarkClient::Mode QmlMqttMonarkClient::mode() const
{
    return m_mode;
}

void QmlMqttMonarkClient::setTargetPower(int newTargetPower)
{
    if (newTargetPower == m_targetPower)
    {
        return;
    }

    m_mqttClient.publish(QMqttTopicName(TARGET_SET_POWER),
                         QString::number(newTargetPower).toLocal8Bit(),
                         1);

    m_targetPower = newTargetPower;
    emit targetPowerChanged();
}

void QmlMqttMonarkClient::setTargetKp(double newTargetKp)
{
    if (newTargetKp == m_targetKp)
    {
        return;
    }

    m_mqttClient.publish(QMqttTopicName(TARGET_SET_KP),
                     QString::number(newTargetKp, 'f').toLocal8Bit());

    m_targetKp = newTargetKp;
    emit targetKpChanged();
}

void QmlMqttMonarkClient::setMode(QmlMqttMonarkClient::Mode newMode, bool noPublish)
{
    if (newMode == m_mode)
    {
        return;
    }

    QString modeString;
    switch(newMode)
    {
    case POWER:
        modeString = "power";
        break;
    case KP:
        modeString = "kp";
        break;
    case SIMULATION:
        modeString = "simulation";
        break;
    }

    if (!noPublish)
    {
        m_mqttClient.publish(QMqttTopicName(DETAILS_SET_MODE), modeString.toLocal8Bit());
    }

    m_mode = newMode;
    emit modeChanged();
}

void QmlMqttMonarkClient::incGear()
{
    m_mqttClient.publish(QMqttTopicName(GEARSHIFT), QByteArray("inc"), 1);
}

void QmlMqttMonarkClient::incGearLots()
{
    m_mqttClient.publish(QMqttTopicName(GEARSHIFT), QByteArray("inc_lots"), 1);
}

void QmlMqttMonarkClient::decGear()
{
    m_mqttClient.publish(QMqttTopicName(GEARSHIFT), QByteArray("dec"), 1);
}

void QmlMqttMonarkClient::decGearLots()
{
    m_mqttClient.publish(QMqttTopicName(GEARSHIFT), QByteArray("dec_lots"), 1);
}
