#include <QtTest>
#include <QDebug>
#include <QString>
#include <QDebug>
#include <QString>
#include "btree.h"

// add necessary includes here

class AutoTest : public QObject
{
    Q_OBJECT

public:
    AutoTest();
    ~AutoTest();

private slots:

};

AutoTest::AutoTest()
{

}

AutoTest::~AutoTest()
{

}



QTEST_APPLESS_MAIN(AutoTest)

#include "tst_autotest.moc"
