#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include <QLabel>

#include <containers/listdroparea.h>

class ControlWidget : public QWidget
{
        Q_OBJECT

    private:
        static QString graphTypeMimeType();

        ListDropArea* m_dropPlaylist;

    protected:
        void dragEnterEvent(QDragEnterEvent *event) override;
        void dragMoveEvent(QDragMoveEvent *event) override;
        void dropEvent(QDropEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;

    public:
        explicit ControlWidget(QWidget *parent = 0);

    public Q_SLOTS:

    Q_SIGNALS:

};

#endif // CONTROLWIDGET_H
