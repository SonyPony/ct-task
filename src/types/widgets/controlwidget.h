#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <types/containers/ddplaylist.h>
#include <types/controls/graphtypeitem.h>

class ControlWidget : public QWidget
{
        Q_OBJECT

    private:
        static QString graphTypeMimeType();

        DDPlaylist* m_dropPlaylist;
        GraphTypeItemProperties m_itemProperties;
        QSize m_itemSize;
        QPushButton* m_updateDataButton;

    protected:
        void dragEnterEvent(QDragEnterEvent *event) override;
        void dragMoveEvent(QDragMoveEvent *event) override;
        void dropEvent(QDropEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void keyPressEvent(QKeyEvent* event) override;

    public:
        explicit ControlWidget(QWidget *parent = 0);

    public Q_SLOTS:

    Q_SIGNALS:
        void showGraph(int type);
        void updateDataRequest();
};

#endif // CONTROLWIDGET_H
