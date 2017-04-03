#include "channelscalibration.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QTextStream>

TactID ChannelsCalibration::getTactId() const
{
    return _tactId;
}

void ChannelsCalibration::setTactId(const TactID &tactId)
{
    _tactId = tactId;
}

void ChannelsCalibration::setChannels(const std::vector<Channel> &channels)
{
    _channels = channels;
}

CalibrationInfo ChannelsCalibration::getInfo() const
{
    return _info;
}

void ChannelsCalibration::setInfo(const CalibrationInfo &info)
{
    _info = info;
}

void ChannelsCalibration::setChannel(const ChannelID index, const Channel &channel)
{
    _channels[index] = channel;
}

bool ChannelsCalibration::getActive() const
{
    return _active;
}

void ChannelsCalibration::setActive(bool active)
{
    _active = active;
}

ChannelsCalibration::ChannelsCalibration()
{
    _tactId = 0;
    _info._id = 0;
    _info._name = "none";
    _active = true;
}

ChannelsCalibration::~ChannelsCalibration()
{

}

void ChannelsCalibration::saveToFile(const QString &path, size_t saveIndex) const
{
    QFile outFile(path);
    logEvent("ChanCalib","Saving to file:"+path);
    if(outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QDomDocument doc = generateXML(saveIndex);
        QTextStream stream(&outFile);
        stream << doc.toString();
        outFile.close();
    }
    else {
        qDebug() << "Cannot save to file"<<path;
        Q_ASSERT(false);
    }
}

void ChannelsCalibration::loadFromFile(const QString &path)
{
    QDomDocument doc;
    logEvent("ChanCalib","Loading from file:"+path);
    QFile inputFile(path);
    if (!inputFile.open(QIODevice::ReadOnly) || !doc.setContent(&inputFile)) {
        qDebug() << "Cannot load from file";
        Q_ASSERT(false);
        return;
    }
    inputFile.close();
    QDomNode calibration = doc.elementsByTagName("calibration").at(0);
    if(!calibration.isNull()) {
        QDomElement tact = calibration.firstChildElement("tact");
        _tactId = tact.text().toUInt();
        QDomElement info = calibration.firstChildElement("info");
        _info._id = info.firstChildElement("id").text().toUInt();
        _info._name = info.firstChildElement("name").text();
        _active = true;

        _channels.clear();
        QDomElement channels = calibration.firstChildElement("channels");
        QDomNodeList chans = channels.elementsByTagName("channel");
        for(int i=0; i<chans.size(); i++) {
            QDomNode channel = chans.at(i);
            if(!channel.isNull()) {
                Channel newChannel;
                newChannel.loadXML(channel);
                _channels.push_back(newChannel);
            }
            else {
                qDebug() << "Cannot read channel";
            }
        }
    }
    else {
        qDebug() << "Cannot read calibration";
    }
}

QDomDocument ChannelsCalibration::generateXML(size_t newIndex) const
{
    QDomDocument doc;

    QDomNode xmlNode = doc.createProcessingInstruction("xml",
                       "version=\"1.0\" encoding=\"UTF-8\" ");
    doc.insertBefore(xmlNode, doc.firstChild());
    QDomElement calibration = doc.createElement("calibration");
    doc.appendChild(calibration);

    QDomElement tact = doc.createElement("tact");
    tact.appendChild(doc.createTextNode(QString::number(_tactId)));
    calibration.appendChild(tact);

    QDomElement info = doc.createElement("info");
    QDomElement idElement = doc.createElement("id");
    idElement.appendChild(doc.createTextNode(QString::number(newIndex)));
    QDomElement nameElement = doc.createElement("name");
    nameElement.appendChild(doc.createTextNode(_info._name));
    info.appendChild(idElement);
    info.appendChild(nameElement);
    calibration.appendChild(info);

    QDomElement channelsElement = doc.createElement("channels");
    for(auto it = _channels.begin(); it!=_channels.end(); it++) {
        const Channel & chan = it.operator *();
        QDomElement element = chan.generateXML(doc);
        channelsElement.appendChild(element);
    }

    calibration.appendChild(channelsElement);

    return doc;
}

ChannelsCalibration ChannelsCalibration::getSnapshot()
{
    return ChannelsCalibration(*this);
}

Channel ChannelsCalibration::getChannel(const ChannelID index) const
{
    Q_ASSERT(index<8);
    Q_ASSERT(_channels.size() > 0);
    return _channels.at(index);
}

DisplayChannel ChannelsCalibration::getDisplayChannel(const ChannelID chan, const DisplayChannelID disp) const
{
    ChannelsInfo info;
    info._channel = chan;
    info._displayChannel = disp;
    return getDisplayChannel(info);
}

DisplayChannel ChannelsCalibration::getDisplayChannel(const ChannelsInfo &info) const
{
    const auto & channels = getChannel(info._channel).getDisplayChannels();
    return channels.at(info._displayChannel);
}

uint8_t ChannelsCalibration::getChannelsCount() const
{
    uint8_t size = _channels.size();
    Q_ASSERT(size <= 8);
    return size;
}
