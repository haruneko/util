/**
 * Created by Hal@shurabaP on 2015/06/06.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#ifndef HARUNEKO_DEVICEREADER_H
#define HARUNEKO_DEVICEREADER_H

#include <QIODevice>
#include <QSharedPointer>

#include "util/Try.h"

namespace haruneko {
namespace util {

    /**
     * DeviceReader is a template class to read T from QIODevice.
     */
    template <class T> class DeviceReader {
    public:
        virtual ~DeviceReader() { }
        /**
         * read T from QIODevice.
         * @param device to read.
         * @return Success(T) contains an instance of T on device.
         *        Failure(e) contains an error on reading.
         */
        virtual Try<T> read(const QSharedPointer<QIODevice> &device) = 0;
    };

}
}

#endif //HARUNEKO_DEVICEREADER_H
