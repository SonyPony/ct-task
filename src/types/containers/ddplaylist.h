#ifndef DDPLAYLIST_H
#define DDPLAYLIST_H

#include <QWidget>
#include <types/containers/listdroparea.h>

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
        /**
         * @brief setItemsSelection Calls select method if item if id matches with its id.
         */
        void setItemsSelection();

    public Q_SLOTS:
        void setActiveItemId(int activeItemId);

        /**
         * @brief setNextActiveItem Sets next id in list as active if id is last in list
         * then it will set first id in list.
         */
        void setNextActiveItem();

        /**
         * @brief setPreviousActiveItem Sets previous id in list as active if id is first in
         * list then it will set last id in list.
         */
        void setPreviousActiveItem();

        /**
         * @brief setUnactive Disselects all items. And set active id on -1.
         */
        void setUnactive();
        void select(int id);
        void display(int id);

    Q_SIGNALS:
        void activeItemIdChanged(int activeItemId);
};

#endif // DDPLAYLIST_H
