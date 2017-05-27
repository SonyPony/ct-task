#include "controlwidget.h"

#include "controls/cloneableitem.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDragMoveEvent>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>

ControlWidget::ControlWidget(QWidget *parent) : QWidget(parent)
{
    this->setAcceptDrops(true);
    this->resize(500, 500);

    m_dropPlaylist = new ListDropArea(this);
    m_dropPlaylist->resize(500, 150);
    m_dropPlaylist->move(0, 350);
    // TODO make better
    CloneableItem* item = new CloneableItem(1, this);
    item->resize(100, 100);
    item->show();
}

QString ControlWidget::graphTypeMimeType()
{
    return QStringLiteral("application/x-graphtype");
}

void ControlWidget::dragEnterEvent(QDragEnterEvent* event)
{
    if(event->mimeData()->hasFormat(ControlWidget::graphTypeMimeType())) {
        if(event->source() == this) {
            event->setDropAction(Qt::CopyAction);
            event->accept();
        }
        else
            event->acceptProposedAction();
    }

    else if(event->mimeData()->hasText())
        event->acceptProposedAction();
    else
        event->ignore();
}

void ControlWidget::dragMoveEvent(QDragMoveEvent* event)
{
    if(event->mimeData()->hasFormat(ControlWidget::graphTypeMimeType())) {
        if(event->source() == this) {
            QByteArray itemData = event->mimeData()->data(ControlWidget::graphTypeMimeType());
            QDataStream dataStream(&itemData, QIODevice::ReadOnly);
            QPoint offset;
            int id;
            dataStream >> offset >> id;

            m_dropPlaylist->handleDraggingItem(id, event->pos() - offset);
            event->setDropAction(Qt::CopyAction);
            event->accept();
        }
        else
            event->acceptProposedAction();
    }

    else if(event->mimeData()->hasText())
        event->acceptProposedAction();
    else
        event->ignore();
}

void ControlWidget::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();
    QByteArray itemData = mimeData->data(ControlWidget::graphTypeMimeType());
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);
    QPoint offset;
    int id;

    dataStream >> offset >> id;

    if(mimeData->hasFormat(ControlWidget::graphTypeMimeType())) {
        CloneableItem* newItem = new CloneableItem(id, this);

        newItem->move(event->pos() - offset);
        newItem->setClonable(false);
        // TODO get size from data
        newItem->resize(100, 100);

        newItem->setAttribute(Qt::WA_DeleteOnClose);

        if(m_dropPlaylist->isInDropArea(newItem)) {
            if(m_dropPlaylist->handleDroppedItem(newItem))
                newItem->show();
            else
                newItem->close();
        }

        else {
            m_dropPlaylist->unregisterItem(newItem);
            newItem->deleteLater();
        }

        if(event->source() == this) {
            event->setDropAction(Qt::CopyAction);
            event->accept();
        }
        else
            event->acceptProposedAction();
    }

    else if(mimeData->hasText())
        event->acceptProposedAction();
    else
        event->ignore();
}

void ControlWidget::mousePressEvent(QMouseEvent* event)
{
    CloneableItem* child = dynamic_cast<CloneableItem*>(this->childAt(event->pos()));
    if(!child)
        return;

    const bool reorderAction = m_dropPlaylist->geometry().contains(event->pos());
    QByteArray itemData;
    QPoint hotSpot = event->pos() - child->pos();
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << hotSpot << child->id();

    QMimeData* mimeData = new QMimeData;
    mimeData->setData(ControlWidget::graphTypeMimeType(), itemData);

    if(reorderAction)
        m_dropPlaylist->unregisterItem(child);

    QDrag* drag = new QDrag(this);
    drag->setHotSpot(hotSpot);
    drag->setMimeData(mimeData);
    drag->setPixmap(child->pixmap());

    if(!child->clonable())
        child->close();
    drag->exec(Qt::MoveAction | Qt::CopyAction);
}
