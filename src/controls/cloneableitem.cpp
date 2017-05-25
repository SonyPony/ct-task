#include "cloneableitem.h"

#include <QPainter>

CloneableItem::CloneableItem(QWidget* parent): QWidget(parent)
{
    m_clonable = true;
}

void CloneableItem::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setBrush(QColor("red"));
    painter.drawRect(QRect(QPoint(), this->size()));
}

QPixmap CloneableItem::pixmap()
{
    m_imageRepresentation = QImage(this->size(), QImage::Format_ARGB32);
    m_imageRepresentation.fill(Qt::transparent);
    QPainter painter(&m_imageRepresentation);
    this->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);

    return QPixmap::fromImage(m_imageRepresentation);
}

bool CloneableItem::clonable() const
{
    return m_clonable;
}

void CloneableItem::setClonable(bool value)
{
    m_clonable = value;
}
