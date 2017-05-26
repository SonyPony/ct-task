#include "listdroparea.h"

#include <QPainter>
#include <QDebug>
#include <QPair>

CloneableItem* ListDropArea::findItemWithId(int id)
{
    for(auto item: m_items) {
        if(item.first == id)
            return item.second;
    }
    return nullptr;
}

ListDropArea::ListDropArea(QWidget *parent) : QWidget(parent)
{
    // TODO get and set
    m_itemsSize = QSize(100, 100);
}

void ListDropArea::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen(QColor(Qt::transparent));
    painter.setBrush(QColor("lightGray"));
    painter.drawRect(this->rect());
}

bool ListDropArea::isInDropArea(const CloneableItem* item) const
{
    return this->geometry().intersects(item->geometry());
}

int ListDropArea::calculateSection(CloneableItem* item) const
{
    typedef QPair<int, int> Interval;

    if(m_items.isEmpty())
        return 0;

    QList<Interval> insertIntervals;
    int itemCenter = m_itemsSize.width() / 2.;
    const int itemX = item->x();
    const int itemWidth = item->width();

    // insert interval from 0 to first item
    insertIntervals.append(qMakePair(0, m_items.at(0).second->x() + itemCenter));

    for(int i = 0; i < m_items.length() - 2; i++) {
        insertIntervals.append(qMakePair(
                                   m_items.at(i).second->x() + itemCenter,
                                   m_items.at(i + 1).second->x() + itemCenter
                               ));
    }

    // insert interval from first item to end
    insertIntervals.append(qMakePair(m_items.at(m_items.length() - 1).second->x() + itemCenter, this->width()));

    // check interval of item
    for(const Interval& interval: insertIntervals) {
        if(interval.first <= itemX && itemX + itemWidth <= interval.second)
            return insertIntervals.indexOf(interval);
    }

    return 0;
}

bool ListDropArea::itemRegistered(const CloneableItem* item)
{
    if(this->findItemWithId(item->id()) != nullptr)
        return true;
    return false;
}

QList<int> ListDropArea::idList() const
{
    return m_idList;
}

void ListDropArea::realignItems()
{
    // TODO set offset
    constexpr int offset = 10;
    const int itemsCount = m_items.length();
    QPoint pos(this->width() / 2. - (itemsCount * m_itemsSize.width() + offset * (itemsCount - 1)) / 2. + this->x(),
               this->height() / 2. - m_itemsSize.height() / 2. + this->y());

    for(int i = 0; i < itemsCount; i++) {
        m_items[i].second->move(pos);
        pos += QPoint(offset + m_itemsSize.width(), 0);
    }
}

bool ListDropArea::registerItem(CloneableItem* item)
{
    if(this->findItemWithId(item->id()) == nullptr)
        m_items.insert(this->calculateSection(item), qMakePair(item->id(), item));
    else
        return false;
    return true;
    // TODO connect with destruct?
}

void ListDropArea::unregisterItem(CloneableItem* item)
{
    CloneableItem* registeredItem = this->findItemWithId(item->id());
    if(registeredItem == nullptr)
        return;

    m_items.removeAll(qMakePair(item->id(), registeredItem));
    this->realignItems();
}

bool ListDropArea::handleDroppedItem(CloneableItem* item)
{
    const bool registerResult = this->registerItem(item);
    if(registerResult)
        this->realignItems();

    return registerResult;
}

void ListDropArea::setIdList(QList<int> idList)
{
    if (m_idList == idList)
        return;

    m_idList = idList;
    emit idListChanged(idList);
}
