/**
 * Created by Hal@shurabaP on 2015/05/31.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#ifndef HARUNEKO_QSTRINGJSON_H
#define HARUNEKO_QSTRINGJSON_H

#include <QJsonValue>

QJsonValue operator << (QJsonValue &json, const QString &value) {
    return (json = QJsonValue(value));
}

QJsonValue operator >> (const QJsonValue &json, QString &value) {
    if(!json.isString()) {
        return value;
    }
    value = json.toString();
    return json;
}

#endif //HARUNEKO_QSTRINGJSON_H
