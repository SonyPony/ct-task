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

    // TODO make better
    CloneableItem* item = new CloneableItem(this);
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
        if(this->children().contains(event->source())) {
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
        if(this->children().contains(event->source())) {
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

    dataStream >> offset;

    if(mimeData->hasFormat(ControlWidget::graphTypeMimeType())) {
        CloneableItem* newItem = new CloneableItem(this);

        newItem->move(event->pos() - offset);
        newItem->setClonable(false);
        // TODO get size from data
        newItem->resize(100, 100);

        newItem->setAttribute(Qt::WA_DeleteOnClose);
        newItem->show();

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
    CloneableItem* child = static_cast<CloneableItem*>(this->childAt(event->pos()));
    if(!child)
        return;

    QByteArray itemData;
    QPoint hotSpot = event->pos() - child->pos();
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << hotSpot;

    QMimeData* mimeData = new QMimeData;
    mimeData->setData(ControlWidget::graphTypeMimeType(), itemData);

    QDrag* drag = new QDrag(this);
    drag->setHotSpot(hotSpot);
    drag->setMimeData(mimeData);
    drag->setPixmap(child->pixmap());

    if(!child->clonable())
        child->hide();
    drag->exec(Qt::MoveAction | Qt::CopyAction);
    if(!child->clonable())
        child->close();
}
