#include "ddplaylist.h"
#include <types/controls/graphtypeitem.h>

DDPlaylist::DDPlaylist(QWidget *parent) : ListDropArea(parent)
{
    m_activeItemId = -1;

    connect(this, DDPlaylist::activeItemIdChanged, this, DDPlaylist::setItemsSelection);
}

int DDPlaylist::activeItemId() const
{
    return m_activeItemId;
}

int DDPlaylist::itemsCount() const
{
    return m_idList.length();
}

void DDPlaylist::setItemsSelection()
{
    GraphTypeItem* item;
    for(auto itemData: this->items()) {
        if((item = qobject_cast<GraphTypeItem*>(itemData.second)) == nullptr)
            continue;

        if(itemData.first == m_activeItemId)
            item->select();
        else
            item->disselect();
    }
}

void DDPlaylist::setActiveItemId(int activeItemId)
{
    if (m_activeItemId == activeItemId)
        return;

    m_activeItemId = activeItemId;
    emit activeItemIdChanged(activeItemId);
}

void DDPlaylist::setNextActiveItem()
{
    if(!m_idList.length())
        this->setActiveItemId(-1);
    else if(m_activeItemId == -1)
        this->setActiveItemId(m_idList.first());
    else {
        const int nextId = (m_idList.indexOf(m_activeItemId) >= m_idList.length() - 1)
                     ?m_idList.first()
                     :m_idList.at(m_idList.indexOf(m_activeItemId) + 1);
        this->setActiveItemId(nextId);
    }
}

void DDPlaylist::setPreviousActiveItem()
{
    if(!m_idList.length())
        this->setActiveItemId(-1);
    else if(m_activeItemId == -1)
        this->setActiveItemId(m_idList.last());
    else {
        const int nextId = (m_idList.indexOf(m_activeItemId) <= 0)
                     ?m_idList.last()
                     :m_idList.at(m_idList.indexOf(m_activeItemId) - 1);
        this->setActiveItemId(nextId);
    }
}

void DDPlaylist::setUnactive()
{
    this->setActiveItemId(-1);
}

void DDPlaylist::select(int id)
{
    this->setActiveItemId(id);
}

void DDPlaylist::display(int id)
{
    GraphTypeItem* item;
    for(auto itemData: this->items()) {
        if((item = qobject_cast<GraphTypeItem*>(itemData.second)) == nullptr)
            continue;

        item->setDisplayed(itemData.first == id);
    }
}
