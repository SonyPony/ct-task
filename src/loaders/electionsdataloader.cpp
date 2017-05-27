#include "electionsdataloader.h"
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

ElectionsDataLoader::ElectionsDataLoader(QString path, QObject *parent) : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    m_dbModel = new QSqlTableModel(this, m_db);
    m_dbModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    connect(this, ElectionsDataLoader::error, [](QString msg) {
        qDebug() << msg;
    });
}

ElectionsDataLoader::~ElectionsDataLoader()
{
    m_db.close();
}

qreal ElectionsDataLoader::participation()
{
    const QVariant data = this->loadSingleRowData("election", "participation");
    if(!data.isValid())
        return -1;
    return data.toReal();
}

QString ElectionsDataLoader::selectedDetailedParty()
{
    const QVariant data = this->loadSingleRowData("name", "detailedView");
    if(!data.isValid())
        return QString();
    return data.toString();
}

QVariantList ElectionsDataLoader::partiesData()
{
    QVariantList data;
    QVariantMap row;
    QSqlRecord rowData;
    if(!this->selectTable("election"))
        return data;

    for(int i = 0; i < m_dbModel->rowCount(); i++) {
        rowData = m_dbModel->record(i);
        for(int j = 0; j < rowData.count(); j++)
            row[rowData.fieldName(j)] = rowData.value(rowData.fieldName(j));
        data.append(QVariant(row));
    }

    return data;
}

QVariantMap ElectionsDataLoader::partyData(const QString partyName)
{
    const QString tableName = QStringLiteral("election");
    if(!this->selectTable(tableName))
        return QVariantMap();

    QVariantMap data;
    m_dbModel->setFilter(QString("name='%1'").arg(partyName));
    if(m_dbModel->rowCount() < 1)
        emit this->error(tr("Unsufficient row count in table %1 after finding %1")
                         .arg(tableName)
                         .arg(partyName));
    else {
        const QSqlRecord rowData = m_dbModel->record(0);
        for(int j = 0; j < rowData.count(); j++)
            data[rowData.fieldName(j)] = rowData.value(rowData.fieldName(j));
    }
    m_dbModel->setFilter("");
    return data;
}

QVariant ElectionsDataLoader::loadSingleRowData(const QString column, const QString tableName)
{
    if(!this->selectTable(tableName))
        return QVariant();

    if(m_dbModel->rowCount() < 1) {
        emit this->error(tr("Unsufficient row count in table %1").arg(tableName));
        return QVariant();
    }
    return m_dbModel->record(0).value(column);
}

bool ElectionsDataLoader::selectTable(const QString tableName)
{
    m_dbModel->setTable(tableName);
    if(!m_dbModel->select()) {
        emit this->error(tr("Could not open table %1.").arg(tableName));
        return false;
    }

    return true;
}

void ElectionsDataLoader::open(QString path)
{
    if(path != "")
        m_path = path;

    m_db.setDatabaseName(m_path);
    if(!m_db.open())
        emit this->error(m_db.lastError().text());
}
