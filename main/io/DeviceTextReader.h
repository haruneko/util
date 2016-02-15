/**
 * Created by Hal@shurabaP on 2015/06/06.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#ifndef HARUNEKO_DEVICETEXTREADER_H
#define HARUNEKO_DEVICETEXTREADER_H

#include <QIODevice>
#include <QSharedPointer>
#include <QString>
#include <QTextCodec>

namespace haruneko {
namespace util {
    class DeviceTextReader {
    public:
        /**
         * readAll returns all string in the given device.
         */
        static QString readAll(const QSharedPointer<QIODevice> &device, QTextCodec *codec = QTextCodec::codecForName("utf-8"));
        /**
         * readLine returns one line of string in the given device.
         */
        static QString readLine(const QSharedPointer<QIODevice> &device, QTextCodec *codec = QTextCodec::codecForName("utf-8"));
    };
}
}


#endif //HARUNEKO_DEVICETEXTREADER_H
