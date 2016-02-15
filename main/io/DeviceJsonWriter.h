/**
 * Created by Hal@shurabaP on 2015/06/06.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#ifndef HARUNEKO_DEVICEJSONWRITER_H
#define HARUNEKO_DEVICEJSONWRITER_H

#include <QDebug>
#include <QJsonDocument>
#include <QTextCodec>

#include "DeviceWriter.h"
#include "json/Json.h"
#include "util/Execption.h"

namespace haruneko {
namespace util {

    /**
     * DeviceJsonReader is a class that writes JSON to QIODevice.
     * T should have the function `QJsonValue operator <<(const T&)`
     */
    template <class T> class DeviceJsonWriter final : public DeviceWriter<T> {
    private:
        QTextCodec *codec;
    public:
        DeviceJsonWriter(QTextCodec *codec = QTextCodec::codecForName("utf-8")) : codec(codec) { }
        virtual ~DeviceJsonWriter() { }

        /**
         * write JSON to the given QIODevice.
         * @param t is an instance of T to JSON-ize and write into device.
         * @param device to write into.
         * @return Success(Unit) means success of this method.
         *        Failure(e) contains an error on writing JSON.
         */
        Try<Unit> write(const T &t, const QSharedPointer<QIODevice> &device) override {
            return applyTry<Unit>([t, device, this]() -> Unit {
                if(device.isNull()) {
                    throw new Exception("No device found");
                }

                QJsonValue jsonValue(Json::toJson(t));
                if(!jsonValue.isObject()) {
                    throw new Exception("Given object as t is not an object.(maybe an array)");
                }
                QJsonDocument json(jsonValue.toObject());

                if(!device->open(QIODevice::WriteOnly)) {
                    throw new Exception("Failed opening device");
                }

                QTextStream ts(device.data());
                ts.setCodec(this->codec);

                ts << QString::fromUtf8(json.toJson(QJsonDocument::Compact));
                device->close();
                return Unit();
            });
        }
    };
}
}

#endif //HARUNEKO_DEVICEJSONWRITER_H
