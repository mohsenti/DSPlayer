//
// Created by mohsen on 1/3/17.
//

#ifndef DSPLAYER_CORETOOLS_H
#define DSPLAYER_CORETOOLS_H

namespace Core {

    class RefCounter {
    private:
        int refCount;
    public:
        RefCounter() : refCount(0) {}

        void AddRef() { refCount++; }

        bool Release() { return --refCount <= 0; }
    };

    template<class T>
    class Ref {
    private:
        T *object;
        RefCounter *refCounter;
    public:

        Ref(T *object) : object(object) {
            refCounter = new RefCounter();
            refCounter->AddRef();
        }

        Ref(const Ref<T> &Ref) : object(Ref.object), refCounter(Ref.refCounter) {
            refCounter->AddRef();
        }

        virtual ~Ref() {
            if (refCounter->Release()) {
                delete object;
                delete refCounter;
            }
        }

        T &operator*() {
            return *object;
        }

        T *operator->() {
            return object;
        }

        bool IsValid() {
            return object != nullptr;
        }

        T *resetObject(T *obj) {
            T *tmp = object;
            object = obj;
            return tmp;
        }
    };
}

#endif //DSPLAYER_CORETOOLS_H
