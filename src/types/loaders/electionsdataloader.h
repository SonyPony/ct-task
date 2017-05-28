#ifndef ELECTIONSDATALOADER_H
#define ELECTIONSDATALOADER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>

class ElectionsDataLoader : public QObject
{
        Q_OBJECT
    private:
        QString m_path;
        QSqlDatabase m_db;
        QSqlTableModel* m_dbModel;

    public:
        explicit ElectionsDataLoader(QString path = QString(), QObject *parent = 0);
        ~ElectionsDataLoader();

        Q_INVOKABLE qreal participation();
        Q_INVOKABLE QString selectedDetailedParty();
        Q_INVOKABLE QVariantList partiesData();
        Q_INVOKABLE QVariantMap partyData(const QString partyName);

    private Q_SLOTS:
        QVariant loadSingleRowData(const QString column, const QString tableName);
        bool selectTable(const QString tableName);

    public Q_SLOTS:
        void open(QString path = QString());

    Q_SIGNALS:
        void error(QString msg);
};

#endif // ELECTIONSDATALOADER_H
