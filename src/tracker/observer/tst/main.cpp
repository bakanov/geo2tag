#include <QtTest/QtTest>
#include <QtCore/QtCore>
#include <QApplication>

// Test headers
#include "tokenInObserver_test.h"

int main(int c, char **v)
{
  QApplication app(c,v);

  Test::tokenInObserver_test test;
  QTest::qExec(&test);

  return 0;
}
