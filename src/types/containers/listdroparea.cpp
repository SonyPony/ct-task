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

QList<QPair<int, CloneableItem*> > ListDropArea::items()
{
    return m_items;
}

ListDropArea::ListDropArea(QWidget *parent) : QWidget(parent)
{
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
    return this->isInDropArea(item->geometry());
}

bool ListDropArea::isInDropArea(QRect itemGeometry) const
{
    return this->geometry().intersects(itemGeometry);
}

int ListDropArea::calculateSection(CloneableItem* item) const
{
    return this->calculateSection(item->pos());
}

int ListDropArea::calculateSection(QPoint itemPos) const
{
    typedef QPair<int, int> Interval;

    if(m_items.isEmpty())
        return 0;

    QList<Interval> insertIntervals;
    int itemCenter = m_itemsSize.width() / 2.;
    const int itemX = itemPos.x();

    // insert interval from 0 to first item
    insertIntervals.append(qMakePair(0, m_items.at(0).second->x() + itemCenter));

    for(int i = 0; i < m_items.length() - 1; i++) {
        insertIntervals.append(qMakePair(
                                   m_items.at(i).second->x() + itemCenter,
                                   m_items.at(i + 1).second->x() + itemCenter
                               ));
    }

    // insert interval from last item to end
    insertIntervals.append(qMakePair(m_items.at(m_items.length() - 1).second->x() + itemCenter, this->width()));

    // check interval of item
    for(int i = insertIntervals.length() - 1; i >= 0; i--) {
        if(insertIntervals.at(i).first <= itemX)
            return i;
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

QSize ListDropArea::itemsSize() const
{
    return m_itemsSize;
}

void ListDropArea::realignItems(int index)
{
    // TODO set offset
    constexpr int offset = 10;
    const int itemsCount = m_items.length() + (int)(index != -1);
    QPoint pos(this->width() / 2. - (itemsCount * m_itemsSize.width() + offset * (itemsCount - 1)) / 2. + this->x(),
               this->height() / 2. - m_itemsSize.height() / 2. + this->y());

    QList<int> newIdList;
    for(int i = 0; i < m_items.length(); i++) {
        if(i == index)
            pos += QPoint(offset + m_itemsSize.width(), 0);
        newIdList.append(m_items.at(i).first);
        m_items[i].second->move(pos);
        pos += QPoint(offset + m_itemsSize.width(), 0);
    }

    this->setIdList(newIdList);
}

bool ListDropArea::registerItem(CloneableItem* item)
{
    if(this->findItemWithId(item->id()) == nullptr)
        m_items.insert(this->calculateSection(item), qMakePair(item->id(), item));
    else
        return false;
    return true;
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

void ListDropArea::handleDraggingItem(int id, QPoint itemPos)
{
    if(m_idList.contains(id))
        return;
    if(!this->isInDropArea(QRect(itemPos, m_itemsSize))) {
        this->realignItems();
        return;
    }

    this->realignItems(this->calculateSection(itemPos));
}

void ListDropArea::setItemsSize(QSize itemsSize)
{
    if (m_itemsSize == itemsSize)
        return;

    m_itemsSize = itemsSize;
    emit itemsSizeChanged(itemsSize);
}

void ListDropArea::setIdList(QList<int> idList)
{
    if (m_idList == idList)
        return;

    m_idList = idList;
    emit idListChanged(idList);
}
