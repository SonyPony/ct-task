#include "controlqmladapter.h"

ControlQMLAdapter::ControlQMLAdapter(QObject *parent) : QObject(parent)
{
}

void ControlQMLAdapter::setTarget(ControlWidget* target)
{
    connect(target, ControlWidget::updateDataRequest, this, ControlQMLAdapter::updateDataRequest);
    connect(target, ControlWidget::showGraph, this, ControlQMLAdapter::showGraph);
}
