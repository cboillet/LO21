#include <QString>
#include <QtTest>
#include <QCoreApplication>

class TestUVTest : public QObject
{
    Q_OBJECT

public:
    TestUVTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase1_data();
};

TestUVTest::TestUVTest()
{
}

void TestUVTest::initTestCase()
{
}

void TestUVTest::cleanupTestCase()
{
}

void TestUVTest::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

void TestUVTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

QTEST_MAIN(TestUVTest)

#include "tst_testuvtest.moc"
