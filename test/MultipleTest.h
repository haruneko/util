/**
 * Created by Hal@shurabaP on 2015/04/28.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#ifndef UTAU_MULTIPLETEST_H
#define UTAU_MULTIPLETEST_H

#include <QTest>
#include <QHash>
#include <QString>
#include <QSharedPointer>

namespace haruneko {

    namespace MultipleTest {
        QHash<QString, QObject *> &tests();

        int run(int argc, char *argv[]);
    }

    template <class T> class Test {
    public:
        QSharedPointer<T> test;
        Test(const QString &name) : test(new T) {
            if(!MultipleTest::tests().contains(name)) {
                MultipleTest::tests()[name] = test.data();
            }
        }
    };

}

#define DECLARE_TEST(className) static haruneko::Test<className> t(#className);

#endif //UTAU_MULTIPLETEST_H
