/**
 * Created by Hal@shurabaP on 2015/05/24.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#ifndef HARUNEKO_QLISTJSON_H
#define HARUNEKO_QLISTJSON_H

#include <QJsonValue>
#include "JsonValidator.h"

class QJsonArray;
class QJsonValue;

template <class T> class QList;

namespace haruneko {
namespace util {

template<class T>
QJsonValue operator<<(QJsonValue &value, const QList<T> &list) {
    QJsonArray array;
    foreach(const T &v, list) {
        QJsonValue json;
        array.append(json << v);
    }
    return (value = array);
}

template<class T>
QJsonValue operator>>(const QJsonValue &value, QList<T> &list) {
    QJsonArray array(value.toArray());
    foreach(auto e, array) {
        T v;
        e >> v;
        list.append(v);
    }
    return value;
}

template <class T> class JsonValidator<QList<T> > {
public:
    void validate(const QJsonValue &value) const throw(const JsonValidationErrorException *) {
        if (!value.isArray()) {
            throw new JsonValidationErrorException("JSON value is expected as array, but it's not.");
        }
        QJsonArray array(value.toArray());
        for(QJsonValue &e : array) {
            JsonValidator validator;
            validator.validate(e);
        }
    }
};
}
}

#endif //HARUNEKO_QLISTJSON_H
