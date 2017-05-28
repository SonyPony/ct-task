#ifndef GRAPHTYPEITEM_H
#define GRAPHTYPEITEM_H

#include <QLabel>
#include <QWidget>
#include <controls/cloneableitem.h>

struct GraphTypeItemProperties
{
    QColor selectedColor;
    QColor color;
    QColor textColor;
};

class GraphTypeItem : public CloneableItem
{
        Q_OBJECT
        Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
        Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor NOTIFY selectedColorChanged)

    private:
        bool m_displayed;
        bool m_selected;
        QPoint m_pressPos;
        QString m_text;
        QColor m_textColor;
        QColor m_color;
        QColor m_selectedColor;

    protected:
        void paintEvent(QPaintEvent*) override;

    public:
        explicit GraphTypeItem(int id, QWidget *parent = 0);
        GraphTypeItem(int id, const GraphTypeItemProperties& properties, QWidget* parent = 0);

        bool displayed() const;
        bool selected() const;
        QString text() const;
        QColor textColor() const;
        QColor color() const;
        QColor selectedColor() const;
        GraphTypeItemProperties properties() const;

    public Q_SLOTS:
        void setDisplayed(bool displayed);
        void select();
        void disselect();
        void setText(QString text);
        void setTextColor(QColor textColor);
        void setColor(QColor color);
        void setSelectedColor(QColor selectedColor);

    Q_SIGNALS:
        void selectedChanged(bool selected);

        void textChanged(QString text);
        void textColorChanged(QColor textColor);
        void colorChanged(QColor color);
        void selectedColorChanged(QColor selectedColor);
};

#endif // GRAPHTYPEITEM_H
