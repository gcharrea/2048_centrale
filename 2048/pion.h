#ifndef PION_H
#define PION_H
#include <QObject>

using namespace std;

class pion : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString pionQML READ readValeur NOTIFY pChanged)
public:
    explicit pion(QObject *parent = nullptr);
    Q_INVOKABLE void increment();
    Q_INVOKABLE void decrement();
    QString readValeur();

signals:
    void pChanged();
public slots:
    
private:
    int Valeur;
};

#endif // PION_H
