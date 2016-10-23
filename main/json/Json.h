/**
 * Created by Hal@shurabaP on 2015/05/23.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#ifndef _JSON_H
#define _JSON_H

#include <QList>
#include <QJsonObject>
#include <QJsonValue>
#include "JsonValidator.h"

namespace haruneko {
namespace util {

    class Json {
    public:
        /**
         * toJson method serializes the given arg as t.
         * tparam T should have the overridden method, operator <<,
         * that convert T to JSON.
         */
        template<class T> inline static QJsonValue toJson(const T &t) {
            QJsonValue v;
            return (v << t);
        }

        /**
         * fromJson method deserialize the given json as value.
         * tparam T should have the overriden method, operator <<,
         * that convert JSON to T.
         * tparam also needs a class JsonValidator<T> to validate json.
         * And also T should have the constructor T().
         */
        template<class T> inline static T fromJson(const QJsonValue &value) throw(const JsonValidationErrorException *) {
            JsonValidator<T> validator;
            validator.validate(value);
            T t;
            value >> t;
            return t;
        }
    };

}
}

#endif //_JSON_H
