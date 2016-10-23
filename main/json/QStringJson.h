/**
 * Created by Hal@shurabaP on 2015/05/31.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#ifndef HARUNEKO_QSTRINGJSON_H
#define HARUNEKO_QSTRINGJSON_H

#include <QJsonValue>
#include "JsonValidator.h"

namespace haruneko {
namespace util {

QJsonValue operator << (QJsonValue &json, const QString &value) {
    return (json = QJsonValue(value));
}

QJsonValue operator >> (const QJsonValue &json, QString &value) {
    value = json.toString();
    return json;
}

template <> class JsonValidator<QString> {
public:
    void validate(const QJsonValue &v) const throw(const JsonValidationErrorException *) {
        if (v.isString()) {
            return;
        }
        throw new JsonValidationErrorException("JSON value is expected as string, but it's not.");
    }
};
constexpr JsonValidator<QString> QStringValidator = JsonValidator<QString>();
}
}

#endif //HARUNEKO_QSTRINGJSON_H
