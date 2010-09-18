/*
    Copyright (C) 2010 Christian Schoenebeck
*/

#ifndef LS_EFFECT_FACTORY_H
#define LS_EFFECT_FACTORY_H

#include "Effect.h"
#include "EffectInfo.h"
#include "../common/Exception.h"

namespace LinuxSampler {

/**
 * Manages all sampler internal effects. It offers a list and detailed
 * informations about all internal effects available for the sampler and allows
 * to create and destroy instances of those effects. It provides a general
 * interface for these functions, independent of the respective effect system's
 * implementation details.
 */
class EffectFactory {
public:
    /**
     * Returns comma separated list of all effect systems currently available
     * for this sampler. This list can vary on the exact configuration of the
     * running machine and the options with which the sampler was compiled.
     */
    static String AvailableEffectSystemsAsString();

    /**
     * Returns total amount of effects currently available for the sampler. This
     * value can vary on the exact configuration of the running machine and
     * especially on which effect plugins are currently installed on the machine.
     *
     * @e Note: When this method is called the 1st tim, it can take quite some
     * time to return, since it will trigger a scan to retrieve all effects,
     * currently available on the system. Those informations are then buffered
     * in RAM and won't change on subsequent calls to AvailableEffectsCount()
     * until an update of available effects is forced by calling
     * UpdateAvailableEffects() .
     *
     * @see UpdateAvailableEffects()
     */
    static uint AvailableEffectsCount();

    /**
     * Force to refresh the internal list of available effects and their
     * detailed informations. This might be necessary e.g. when the user
     * installed new effect plugins on his system and doesn't want to restart
     * the whole sampler session just for being able to access the new effects.
     */
    static void UpdateAvailableEffects();

    /**
     * Returns unique identifier and further detailed informations about the
     * requested effect.
     *
     * @param index - index of the effect to retrieve informations about, must
     *                be between 0 and AvailableEffectsCount()
     * @see UpdateAvailableEffects()
     */
    static EffectInfo* GetEffectInfo(uint index);

    /**
     * Create an instance of the requested effect. You should call Destroy()
     * once the effect is not used anymore.
     *
     * @param pInfo - unique identifier of the effect to create
     * @returns pointer to new effect instance, throws an Exception otherwise
     * @throws Exception - if the requested effect could not be instantiated
     *                     successfully
     */
    static Effect* Create(EffectInfo* pInfo) throw (Exception);

    /**
     * Destroy and free the given effect instance from memory, previously
     * created with Create() .
     *
     * @param pEffect - effect instance to destroy
     */
    static void Destroy(Effect* pEffect);
};

} // namespace LinuxSampler

#endif // LS_EFFECT_FACTORY_H
