/**
 * Created by Hal@shurabaP on 2015/06/06.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#ifndef HARUNEKO_DEVICEWRITER_H
#define HARUNEKO_DEVICEWRITER_H

#include <QIODevice>
#include <QSharedPointer>

#include "util/Try.h"

namespace haruneko {
namespace util {
    /**
     * DeviceWriter is a template class to write T into device.
     */
    template <class T> class DeviceWriter {
    public:
        virtual ~DeviceWriter() { }
        /**
         * write T into the given device T.
         * @return Success(Unit) when DeviceWriter succeeded to write.
         *        Failure(e) when DeviceWriter failed writing.
         */
        virtual Try<Unit> write(const T &t, const QSharedPointer<QIODevice> &device) = 0;
    };
}
}

#endif //HARUNEKO_DEVICEWRITER_H
