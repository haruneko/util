/**
 * Created by Hal@shurabaP on 2015/06/06.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#ifndef HARUNEKO_TRY_H
#define HARUNEKO_TRY_H

#include <functional>
#include <QString>
#include <QSharedData>
#include <QSharedDataPointer>
#include "Execption.h"

namespace haruneko {
namespace util {

    class Unit { public: Unit() { } };

    template <class A> class Try;
    template <class A> static Try<A> applyTry(std::function<A()> f);

    /**
     * Try class support some monadic functions.
     * This class has two states, Success and Failure.
     * If an exception was thrown while instantiation,
     * Try will be Failure, otherwise Success.
     */
    template <class A> class Try final {
    public:
        template <class _A> class TryData : public QSharedData {
        public:
            TryData(const _A &a) : a(a), isSuccess(true), exception() { }
            TryData(const Exception &e) : a(), isSuccess(false), exception(e) { }
            const _A a;
            const bool isSuccess;
            const Exception exception;
        };

        Try() : d() { }
        explicit Try(const A &a) : d(new TryData<A>(a)) { }
        explicit Try(const Exception &e) : d(new TryData<A>(e)) { }
        Try(const Try<A> &other) : d(other.d) { }
        Try<A> &operator=(const Try<A> &other) { this->d = other.d; return *this; }

        bool isFailure() const { return !d->isSuccess; }
        bool isSuccess() const { return d->isSuccess; }

        /**
         * get will return the value in Try when Try is Success,
         * otherwise throw an exception.
         */
        const A &get() const {
            if(isSuccess()) {
                return d->a;
            }
            throw d->exception;
        }

        const Exception &error() const {
            return d->exception;
        }

        template <class B> Try<B> flatMap(std::function<Try<B>(A)> f) const {
            return applyTry<B>([f, this]() -> B { return f(this->get()).get(); });
        }

        template <class B> Try<B> map(std::function<B(const A&)> f) const {
            return flatMap<B>([f](const A &a)-> Try<B> {
                return applyTry<B>([f, a]() -> B { return f(a); });
            });
        }

        Try<A> recover(std::function<A(const Exception &)> f) const {
            return recoverWith([f, this](const Exception e) -> Try<A> {
                return applyTry<A>([f, e]() -> A { return f(e); });
            });
        }

        Try<A> recoverWith(std::function<Try<A>(const Exception &)> f) const {
            if(this->isSuccess()) {
                return *this;
            }
            return f(d->exception);
        }
    private:
        QSharedDataPointer<TryData<A> > d;
    };

    template <class A> static Try<A> applyTry(std::function<A()> f) {
        Try<A> result;
        try {
            result = Try<A>(f());
        } catch (const Exception e) {
            result = Try<A>(e);
        }
        return result;
    }
}
}

#endif //HARUNEKO_TRY_H
