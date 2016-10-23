/**
 * Created by Hal@shurabaP on 2016/02/21.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2016 Hal@shurabaP. All rights reserved.
 */
#ifndef HARUNEKO_UTIL_ROOT_DURATION_H
#define HARUNEKO_UTIL_ROOT_DURATION_H

#include <QSharedData>

namespace haruneko {
namespace util {

    /**
     * Duration contains a time duration.
     * Internally this class has micros seconds, and micros, millis, seconds and minutes return value for each unit.
     */
    class Duration {
        class DurationData : public QSharedData {
        public:
            explicit DurationData(const DurationData &other) : _microSeconds(other._microSeconds) { }
            explicit DurationData(const qint64 micros) : _microSeconds(micros) { }
            const qint64 _microSeconds;
        };
        QSharedDataPointer<DurationData> d;
    public:
        Duration(const Duration &other) : d(other.d) { }
        explicit Duration(const qint64 micros) : d(new DurationData(micros)) { }
        qint64 micros() const { return d->_microSeconds; }
        qint64 millis() const { return d->_microSeconds / 1000; }
        qint64 seconds() const { return d->_microSeconds / 1000 / 1000; }
        qint64 minutes() const { return d->_microSeconds / 1000 / 1000 / 60; }

        bool operator ==(const Duration &other) const { return this->d->_microSeconds == other.d->_microSeconds; }
        Duration operator +(const Duration &other) const { return Duration(this->d->_microSeconds + other.d->_microSeconds); }
        Duration operator -(const Duration &other) const { return Duration(this->d->_microSeconds - other.d->_microSeconds); }

        static Duration millis(qint64 m) { return Duration(m * 1000L); }
        static Duration seconds(qint64 s) { return millis(s * 1000L); }
        static Duration minutes(qint64 m) { return seconds(m * 60L); }
        static Duration hours(qint64 h) { return minutes(h * 60L); }
        static Duration days(qint64 d) { return hours(d * 24L); }
    };

}
}

#endif //HARUNEKO_UTIL_ROOT_DURATION_H
