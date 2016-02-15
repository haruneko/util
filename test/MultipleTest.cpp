/**
 * Created by Hal@shurabaP on 2015/04/28.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#include "MultipleTest.h"

using namespace haruneko;

QHash<QString, QObject *> &MultipleTest::tests() {
    static QHash<QString, QObject *> t;
    return t;
}

int MultipleTest::run(int argc, char *argv[]) {
    int ret = 0;
    QList<QString> failureTests;
    printf("Start unit tests - utau_test");
    foreach(QObject* test, tests().values()) {
        int result =  QTest::qExec(test, argc, argv);
            if(result) {
                failureTests.append(tests().key(test));
            }
            ret |= result;
        }
        if(ret == 0) {
            printf("[success] All test succeeded!\n");
        } else {
        printf("[error] %d test(s) failed.\n", failureTests.size());
        foreach(const QString &testName, failureTests) {
            printf("[error]  Test failed in: %s\n", testName.toLocal8Bit().data());
        }
    }
    printf("End unit tests - utau_test");
    return ret;
}
