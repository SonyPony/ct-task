#ifndef CLONEABLEITEM_H
#define CLONEABLEITEM_H

#include <QWidget>

class CloneableItem : public QWidget
{
        Q_OBJECT

    private:
        bool m_clonable;
        QImage m_imageRepresentation;
        int m_id;

    public:
        CloneableItem(int id, QWidget* parent = 0);

        /**
         * @brief pixmap Return pixmap representation of item
         */
        QPixmap pixmap();

        bool clonable() const;
        int id() const;

    public Q_SLOTS:
        void setClonable(bool value);
};

#endif // CLONEABLEITEM_H
