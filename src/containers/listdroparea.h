#ifndef LISTDROPAREA_H
#define LISTDROPAREA_H

#include <QWidget>
#include <controls/cloneableitem.h>

class ListDropArea : public QWidget
{
        Q_OBJECT
        Q_PROPERTY(QList<int> idList READ idList WRITE setIdList NOTIFY idListChanged)

    private:
        QList<QPair<int, CloneableItem*> > m_items;
        QSize m_itemsSize;
        QList<int> m_idList;

        CloneableItem* findItemWithId(int id);

    public:
        explicit ListDropArea(QWidget *parent = 0);

        void paintEvent(QPaintEvent*) override;

        /**
         * @brief isInDropArea Checks whether item is in drop area.
         * @param item Tested item.
         * @return Returns true item intersects with droparea otherwise returns false.
         */
        bool isInDropArea(const CloneableItem* item) const;
        bool isInDropArea(QRect itemGeometry) const;

        /**
         * @brief calculateSection Calculates index in list of items where the new item
         * should be
         * inserted according to its position.
         * @param item Inserting item.
         * @return Index in list where item should be inserted.
         */
        int calculateSection(CloneableItem* item) const;
        int calculateSection(QPoint itemPos) const;

        /**
         * @brief itemRegistered Check whether item is registered
         * @param item Tested item
         * @return Return true ifc item is registered else false
         */
        bool itemRegistered(const CloneableItem* item);

        QList<int> idList() const;

    private Q_SLOTS:
        /**
         * @brief realignItems Reposition items according to their order in item list.
         */
        void realignItems();

        /**
         * @brief registerItem Register item in drop area.
         * @param item Registered item.
         * @return Returns true if item with the same id had
         * not been registered before, else return false.
         */
        bool registerItem(CloneableItem* item);

    public Q_SLOTS:
        /**
         * @brief unregisterItem Unregister item from drop area.
         * @param item
         */
        void unregisterItem(CloneableItem* item);

        /**
         * @brief handleDroppedItem Handle item which was dropped into drop area.
         * @param item Dropped item.
         * @return Returns true if item with the same id had
         * not been registered before, else return false.
         */
        bool handleDroppedItem(CloneableItem* item);
        void setIdList(QList<int> idList);

    Q_SIGNALS:
        void idListChanged(QList<int> idList);
};

#endif // LISTDROPAREA_H
