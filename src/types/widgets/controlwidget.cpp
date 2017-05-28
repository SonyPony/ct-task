#include "controlwidget.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDragMoveEvent>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QDebug>

ControlWidget::ControlWidget(QWidget *parent) : QWidget(parent)
{
    this->setAcceptDrops(true);
    this->setWindowTitle(tr("Kontrolní okno"));
    this->resize(500, 500);

    m_itemSize = QSize(100, 100);

    m_dropPlaylist = new DDPlaylist(this);
    m_dropPlaylist->setItemsSize(m_itemSize);
    m_dropPlaylist->resize(500, 150);
    m_dropPlaylist->move(0, 300);

    m_updateDataButton = new QPushButton(tr("AKTUALIZOVAT"), this);
    m_updateDataButton->move(0, m_dropPlaylist->y() + m_dropPlaylist->height());
    m_updateDataButton->resize(m_dropPlaylist->width(), 50);

    m_itemProperties.color = QColor("#303030");
    m_itemProperties.textColor = QColor("#FFFFFF");
    m_itemProperties.selectedColor = QColor("#0683BA");

    GraphTypeItem* item = nullptr;
    const QStringList labels = { "ÚČAST VOLIČŮ", "ZISK STRAN", "DETAIL ZISKU STRANY" };

    // create three graph type items
    for(int i = 0; i < 3; i++) {
        item = new GraphTypeItem(i + 1, m_itemProperties, this);
        item->resize(m_itemSize);
        item->setText(labels.at(i));
        item->move(i * (m_itemSize.width() + 50) + 50, 20);
        item->show();
    }

    connect(m_updateDataButton, QPushButton::clicked, this, ControlWidget::updateDataRequest);
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
    QString text;
    bool selected;

    if(mimeData->hasFormat(ControlWidget::graphTypeMimeType())) {
        dataStream >> offset >> id >> selected >> text;

        GraphTypeItem* newItem = new GraphTypeItem(id, m_itemProperties, this);
        newItem->resize(m_itemSize);
        newItem->setText(text);
        if(selected)
            m_dropPlaylist->select(newItem->id());

        newItem->move(event->pos() - offset);
        newItem->setClonable(false);
        newItem->setAttribute(Qt::WA_DeleteOnClose);

        if(m_dropPlaylist->isInDropArea(newItem)) {
            if(m_dropPlaylist->handleDroppedItem(newItem))
                newItem->show();
            else
                newItem->close();
        }

        else {
            newItem->close();
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
    GraphTypeItem* child = dynamic_cast<GraphTypeItem*>(this->childAt(event->pos()));
    if(!child)
        return;

    const bool reorderAction = m_dropPlaylist->geometry().contains(event->pos());

    QPoint hotSpot = event->pos() - child->pos();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << hotSpot << child->id() << child->selected() << child->text();

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

void ControlWidget::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        bool emptyPlaylist = !m_dropPlaylist->itemsCount();
        if(emptyPlaylist)
            emit this->showGraph(m_dropPlaylist->activeItemId());
        m_dropPlaylist->setNextActiveItem();
        if(!emptyPlaylist) {
            m_dropPlaylist->display(m_dropPlaylist->activeItemId());
            emit this->showGraph(m_dropPlaylist->activeItemId());
        }

        else
            m_dropPlaylist->display(-1);
    }
    else if(event->key() == Qt::Key_Escape) {
        m_dropPlaylist->display(-1);
        m_dropPlaylist->setUnactive();
        emit this->showGraph(m_dropPlaylist->activeItemId());

    }
}
