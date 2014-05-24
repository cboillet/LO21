#ifndef TESTUV_H
#define TESTUV_H
#include <QtTest/QtTest>

class TestQString: public QObject
 {
     Q_OBJECT
 private slots:
     void toUpper();
 };

void TestQString::toUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}

#endif // TESTUV_H
