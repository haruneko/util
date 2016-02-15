/**
 * Created by Hal@shurabaP on 2015/06/06.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#ifndef HARUNEKO_DEVICEJSONREADER_H
#define HARUNEKO_DEVICEJSONREADER_H

#include <QJsonDocument>

#include "DeviceReader.h"
#include "DeviceTextReader.h"
#include "json/Json.h"
#include "util/Execption.h"

namespace haruneko {
namespace util {

    /**
     * DeviceJsonReader is a class that reads JSON from QIODevice.
     * T should have the function `QJsonValue operator >>(T&)`
     */
    template  <class T> class DeviceJsonReader final : public DeviceReader<T> {
    private:
        QTextCodec *codec;
    public:
        DeviceJsonReader(QTextCodec *codec = QTextCodec::codecForName("utf-8")) : codec(codec) { }

        /**
         * read JSON from the given QIODevice then return the instance of T.
         * @param device is a device that contains JSON.
         * @return Success(T) contains an instance of T corresponding to the JSON.
         *        Failure(e) contains an exception thrown while reading JSON.
         */
        Try<T> read(const QSharedPointer<QIODevice> &device) {
            return applyTry<T>([device, this]() -> T {
                if(device.isNull() || !device->open(QIODevice::ReadOnly)) {
                    throw new Exception("Open-able device not found.");
                }
                QString jsonString = DeviceTextReader::readAll(device, this->codec);
                device->close();

                QJsonParseError error;
                QJsonDocument doc(QJsonDocument::fromJson(jsonString.toUtf8(), &error).object());
                if(error.error != QJsonParseError::NoError) {
                    throw new util::Exception(
                            "Json parse error @" + QString::number(error.offset) + " message is `"  + error.errorString() + "`");
                }
                if(!doc.isObject()) {
                    throw new Exception("Given JSON is not an object.");
                }
                return Json::fromJson<T>(doc.object());
            });
        }
    };

}
}


#endif //HARUNEKO_DEVICEJSONREADER_H
