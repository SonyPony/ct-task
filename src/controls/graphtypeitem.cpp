#include "graphtypeitem.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>

void GraphTypeItem::paintEvent(QPaintEvent*)
{
    QTextOption textOption(Qt::AlignCenter);
    QPainter painter(this);

    painter.setPen(QColor("transparent"));
    painter.setBrush(m_color);
    if(m_selected)
        painter.setBrush(m_selectedColor);
    painter.drawRect(this->rect());

    painter.setPen(m_textColor);
    painter.drawText(this->rect(), m_text, textOption);

}

GraphTypeItem::GraphTypeItem(int id, QWidget *parent) : CloneableItem(id, parent)
{
    m_selected = false;

    connect(this, GraphTypeItem::selectedChanged, [this]() { this->update(); });
    connect(this, GraphTypeItem::textChanged, [this]() { this->update(); });
}

GraphTypeItem::GraphTypeItem(int id, const GraphTypeItemProperties& properties, QWidget* parent):
    GraphTypeItem(id, parent)
{
    m_selectedColor = properties.selectedColor;
    m_color = properties.color;
    m_textColor = properties.textColor;
}

bool GraphTypeItem::selected() const
{
    return m_selected;
}

QString GraphTypeItem::text() const
{
    return m_text;
}

QColor GraphTypeItem::textColor() const
{
    return m_textColor;
}

QColor GraphTypeItem::color() const
{
    return m_color;
}

QColor GraphTypeItem::selectedColor() const
{
    return m_selectedColor;
}

void GraphTypeItem::select()
{
    if(m_selected)
        return;
    m_selected = true;
    emit this->selectedChanged(m_selected);
}

void GraphTypeItem::disselect()
{
    if(!m_selected)
        return;
    m_selected = false;
    emit this->selectedChanged(m_selected);
}

void GraphTypeItem::setText(QString text)
{
    if (m_text == text)
        return;

    m_text = text;
    emit textChanged(text);
}

void GraphTypeItem::setTextColor(QColor textColor)
{
    if (m_textColor == textColor)
        return;

    m_textColor = textColor;
    emit textColorChanged(textColor);
}

void GraphTypeItem::setColor(QColor color)
{
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged(color);
}

void GraphTypeItem::setSelectedColor(QColor selectedColor)
{
    if (m_selectedColor == selectedColor)
        return;

    m_selectedColor = selectedColor;
    emit selectedColorChanged(selectedColor);
}
