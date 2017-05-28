#ifndef CONTROLQMLADAPTER_H
#define CONTROLQMLADAPTER_H

#include <QObject>
#include <types/widgets/controlwidget.h>

class ControlQMLAdapter : public QObject
{
        Q_OBJECT
    public:
        explicit ControlQMLAdapter(QObject *parent = 0);

        void setTarget(ControlWidget* target);

    Q_SIGNALS:
        void updateDataRequest();
        void showGraph(int type);
};

#endif // CONTROLQMLADAPTER_H
