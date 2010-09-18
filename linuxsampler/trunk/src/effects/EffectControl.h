/*
    Copyright (C) 2010 Christian Schoenebeck
*/

#ifndef LS_EFFECTCONTROL_H
#define LS_EFFECTCONTROL_H

#include "../common/Exception.h"
#include "../common/optional.h"

namespace LinuxSampler {

// just symbol prototyping
class Effect;

/**
 * Represents an effect parameter. As the set of parameters an effect offers,
 * varies quite a bit, this class provides necessary informations about the
 * respective effect parameter.
 */
class EffectControl {
public:
    enum Type_t {
        TYPE_FLOAT,
        TYPE_INT,
        TYPE_BOOL
    };

    EffectControl();
    virtual void SetValue(float val) throw (Exception);
    virtual float& Value();
    Type_t Type() const;
    String TypeAsString() const;
    String Description() const;
    optional<float> DefaultValue() const;
    optional<float> MinValue() const;
    optional<float> MaxValue() const;

protected:
    void SetDefaultValue(float val);
    void SetMinValue(float val);
    void SetMaxValue(float val);
    void SetType(Type_t t);
    void SetDescription(String s);

    friend class Effect;

private:
    float value;
    Type_t type;
    String description;
    optional<float> defaultValue;
    optional<float> minValue;
    optional<float> maxValue;
};

} // namespace LinuxSampler

#endif // LS_EFFECTCONTROL_H
