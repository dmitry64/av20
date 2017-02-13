#ifndef CHANNELSTABLEITEM_H
#define CHANNELSTABLEITEM_H

#include <QItemDelegate>

class ChannelsTableItem : public QItemDelegate
{
public:
    ChannelsTableItem(QString text, QColor color);
};

#endif // CHANNELSTABLEITEM_H
