/**
 * Created by Hal@shurabaP on 2015/06/06.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#ifndef HARUNEKO_EXECPTION_H
#define HARUNEKO_EXECPTION_H

#include <QString>

namespace haruneko {
namespace util {

    /**
     * Base exception class.
     * This class has a message and cause of exception.
     */
    class Exception {
    private:
        static QString getMessageInternal(const Exception *e) {
            return e->message + (e->cause != NULL ? "\n  Caused by " + getMessageInternal(e->cause) : QString());
        }
    public:
        Exception() : Exception(QString(), NULL) { }
        Exception(const QString &message, const Exception *cause = NULL) : message(message), cause(NULL) {
            if(cause != NULL) {
                this->cause = new Exception(*cause);
            }
        }
        Exception(const Exception &other) : Exception(other.message, other.cause) { }
        virtual ~Exception() {
            delete cause;
        }

        QString messages() const {
            return getMessageInternal(this);
        }

        const QString message;
        const Exception *cause;
    };
}
}
#endif //HARUNEKO_EXECPTION_H
