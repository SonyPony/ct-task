#ifndef DDPLAYLIST_H
#define DDPLAYLIST_H

#include <QWidget>
#include <containers/listdroparea.h>

class DDPlaylist : public ListDropArea
{
        Q_OBJECT
        Q_PROPERTY(int activeItemId READ activeItemId WRITE setActiveItemId NOTIFY activeItemIdChanged)

    private:
        int m_activeItemId;

    public:
        explicit DDPlaylist(QWidget *parent = 0);

        int activeItemId() const;
        int itemsCount() const;

    private Q_SLOTS:
        void handleIdListChange();
        void setItemsSelection();

    public Q_SLOTS:
        void setActiveItemId(int activeItemId);
        void setNextActiveItem();
        void setPreviousActiveItem();
        void setUnactive();
        void select(int id);
        void display(int id);

    Q_SIGNALS:
        void activeItemIdChanged(int activeItemId);
};

#endif // DDPLAYLIST_H
