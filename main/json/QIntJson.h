/**
 * Created by Hal@shurabaP on 2016/09/07.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2016 Hal@shurabaP. All rights reserved.
 */
#ifndef HARUNEKO_VOICEBANK_ROOT_QINTJSON_H
#define HARUNEKO_VOICEBANK_ROOT_QINTJSON_H

#include <QJsonValue>
#include "JsonValidator.h"

namespace haruneko {
namespace util {

QJsonValue operator << (QJsonValue &json, const int &value) {
    return (json = QJsonValue(value));
}

QJsonValue operator >> (const QJsonValue &json, int &value) {
    value = json.toInt();
    return json;
}

template <> class JsonValidator<int> {
public:
    void validate(const QJsonValue &v) const throw(const JsonValidationErrorException *) {
        if (v.isDouble()) {
            return;
        }
        throw new JsonValidationErrorException("JSON value is expected as string, but it's not.");
    }
};

constexpr JsonValidator<int> IntValidator = JsonValidator<int>();
}
}

#endif //HARUNEKO_VOICEBANK_ROOT_QINTJSON_H
