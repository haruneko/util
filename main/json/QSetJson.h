/**
 * Created by Hal@shurabaP on 2015/05/24.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#ifndef HARUNEKO_QSETJSON_H
#define HARUNEKO_QSETJSON_H

class QJsonArray;
class QJsonValue;

template <class T> class QSet;

template <class T> QJsonValue operator << (QJsonValue &value, const QSet<T> &set) {
    QJsonArray array;
    foreach(const T &v, set) {
        QJsonValue json;
        array.append(json << v);
    }
    return (value = array);
}

template <class T> QJsonValue operator >> (const QJsonValue &value, QSet<T> &set) {
    if(!value.isArray()) {
        return value;
    }
    QJsonArray array(value.toArray());
    foreach(auto e, array) {
        T v;
        e >> v;
        set.insert(v);
    }
    return value;
}

#endif //HARUNEKO_QSETJSON_H
