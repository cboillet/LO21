#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "manager.h"
#include "UTProfiler.h"

class TestCursus : public Cursus, public QObject
{
    Q_OBJECT

public:
    TestCursus():Cursus(){}

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase1_data();
};

void TestCursus::initTestCase()
{

}

void TestCursus::cleanupTestCase()
{
}

void TestCursus::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

void TestCursus::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

QTEST_MAIN(TestCursus)

#include "tst_test.moc"
