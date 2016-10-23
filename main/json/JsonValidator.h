/**
 * Created by Hal@shurabaP on 2016/04/24.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2016 Hal@shurabaP. All rights reserved.
 */
#ifndef HARUNEKO_VOICEBANK_ROOT_JSONVALIDATOR_H
#define HARUNEKO_VOICEBANK_ROOT_JSONVALIDATOR_H

#include <QJsonValue>
#include "util/Execption.h"

namespace haruneko {
namespace util {

    class JsonValidationErrorException : public Exception {
    public:
        JsonValidationErrorException(const QString &message, const Exception *cause = NULL) :
                Exception(message, cause) { }
    };
    /**
     * JsonValidator validates QJsonValue.
     * JsonValidator#validate will throw JsonValidationError
     * when the given QJsonValue has something wrong for the class T.
     */
    template<class T> class JsonValidator {
    public:
        ~JsonValidator() { }
        virtual void validate(const QJsonValue &v) const throw(const JsonValidationErrorException *) = 0;
    };

}
}

#endif //HARUNEKO_VOICEBANK_ROOT_JSONVALIDATOR_H
