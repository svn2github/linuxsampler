#include <gig.h>

template<typename T>
class Param {
protected:
    gig::DimensionRegion* object;
public:
    virtual T& access() = 0;
};

template<typename T>
class Param1 : public Param<T> {
    using Param<T>::object;
    T gig::DimensionRegion::* param;
public:
    Param1(T gig::DimensionRegion::* param) : param(param) { }
    T& access();
};

template<typename T>
T& Param1<T>::access() {
    printf("ojsan");
    return object->*param;
}

class ParamUnityNote : public Param<uint8_t> {
public:
    uint8_t& access() {
        printf("hejsan\n");
        return object->UnityNote; }
};


int main() {
    ParamUnityNote p1;
    Param1<uint8_t> p2(&gig::DimensionRegion::ChannelOffset);
    Param<uint8_t>& pp = p1;
    printf("%d\n", pp.access());
}
