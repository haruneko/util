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

template <class K, class V> class QHash;
template <class T> QString stringify(const T &t);

template <class Key, class Value> QJsonValue operator << (QJsonValue &value, const QHash<Key, Value> &hash) {
    QJsonObject json;
    foreach(Key key, hash.keys()) {
        QString jsonKey = stringify(key);
        QJsonValue j;
        json[jsonKey] = (j << hash[key]);
    }
    return (value = json);
}

template <class Key, class Value> QJsonValue operator >> (const QJsonValue &value, QHash<Key, Value> &hash) {
    if(!value.isObject()) {
        return value;
    }
    QJsonObject json = value.toObject();
    QStringList keys(json.keys());
    foreach(QString key, keys) {
        Key k(key);
        Value v;
        json[key] >> v;
        hash[k] = v;
    }
    return value;
}

#endif //HARUNEKO_QHASHJSON_H
