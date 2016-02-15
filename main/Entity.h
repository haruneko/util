/**
 * Created by Hal@shurabaP on 2015/06/07.
 * This code is under The BSD 3-Clause License.
 * See more Licence.txt.
 * Copyright (c) 2015 Hal@shurabaP. All rights reserved.
 */
#ifndef HARUNEKO_ENTITY_H
#define HARUNEKO_ENTITY_H

#include <QSharedData>
#include <QSharedDataPointer>

namespace haruneko {
    template <class Identifier, class Value> class Entity {
        class EntityData final : public QSharedData {
        public:
            EntityData(const Identifier &id, const Value &value) : id(id), value(value) { }
            Identifier id;
            Value value;
        };
    protected:
        QSharedDataPointer<EntityData> d;
    public:
        Entity() : d() { }
        Entity(const Identifier &id, const Value &value) : d(new EntityData(id, value)) { }
        Entity(const Entity<Identifier, Value> &other) : Entity(other.id(), other.value()) { }
        Entity<Identifier, Value> &operator =(const Entity<Identifier, Value> &other) { this->d = other.d; return *this; }

        virtual ~Entity() { }

        const Identifier &id() const { return d->id; }
        void setId(const Identifier &id) { d->id = id; }

        const Value &value() const { return d->value; }
        Value &value() { return d->value; }
        void setValue(const Value &value) { d->value = value; }

        bool operator ==(const Entity<Identifier, Value> &right) {
            return id() == right.id();
        }
    };

}


#endif //HARUNEKO_ENTITY_H
