#ifndef CLONEABLEITEM_H
#define CLONEABLEITEM_H

#include <QWidget>

class CloneableItem : public QWidget
{
        Q_OBJECT

    private:
        bool m_clonable;
        QImage m_imageRepresentation;

    public:
        CloneableItem(QWidget* parent = 0);
        void paintEvent(QPaintEvent*);

        QPixmap pixmap();
        bool clonable() const;

    public Q_SLOTS:
        void setClonable(bool value);
};

#endif // CLONEABLEITEM_H
