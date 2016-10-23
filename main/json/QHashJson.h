/**
 * Created by Hal@shurabaP on 2015/05/24.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#ifndef HARUNEKO_QHASHJSON_H
#define HARUNEKO_QHASHJSON_H

class QJsonObject;
class QJsonValue;
class QString;

#include <QStringList>
#include "JsonValidator.h"

template <class K, class V> class QHash;

namespace haruneko {
namespace util {

template <class T> QString stringify(const T &t);

template <class Key, class Value> QJsonValue operator << (QJsonValue &value, const QHash<Key, Value> &hash) {
    QJsonObject json;
    for(const Key &key : hash.keys()) {
        QString jsonKey = stringify(key);
        QJsonValue j;
        json[jsonKey] = (j << hash[key]);
    }
    return (value = json);
}

template <class Key, class Value> QJsonValue operator >> (const QJsonValue &value, QHash<Key, Value> &hash) {
    QJsonObject json = value.toObject();
    QStringList keys(json.keys());
    for(const QString &key : keys) {
        Key k(key);
        Value v;
        json[key] >> v;
        hash[k] = v;
    }
    return value;
}

template <class K, class V> class JsonValidator<QHash<K, V> > {
public:
    void validate(const QJsonValue &value) const throw(const JsonValidationErrorException *) {
        if(!value.isObject()) {
            throw new JsonValidationErrorException("JSON object is expected, but it's not.");
        }
        QJsonObject json = value.toObject();
        JsonValidator<V> validator;
        QStringList keys(json.keys());
        for (const QString &key : keys) {
            try {
                K k(key);
                validator.validate(json[key]);
            } catch (Exception *e) {
                throw new JsonValidationErrorException(QString("JSON validation error: on the key=") + key);
            }
        }
    }
};

}
}


#endif //HARUNEKO_QHASHJSON_H
