/*
    Copyright (C) 2010 Christian Schoenebeck
*/

#include "EffectFactory.h"
#include "LadspaEffect.h"

namespace LinuxSampler {

static bool bInitialized = false;

static std::vector<EffectInfo*> vEffectInfos;

static std::vector<Effect*> vEffectInstances;

////////////////////////////////////////////////////////////////////////////
// class 'EffectFactory'

String EffectFactory::AvailableEffectSystemsAsString() {
    return "LADSPA";
}

uint EffectFactory::AvailableEffectsCount() {
    if (!bInitialized) UpdateAvailableEffects();
    bInitialized = true;
    return vEffectInfos.size();
}

EffectInfo* EffectFactory::GetEffectInfo(uint index) {
    if (index >= vEffectInfos.size()) return NULL;
    return vEffectInfos[index];
}

Effect* EffectFactory::Create(EffectInfo* pEffectInfo) throw (Exception) {
    Effect* pEffect = NULL;
    try {
        if (pEffectInfo->EffectSystem() == "LADSPA") {
            pEffect = new LadspaEffect(pEffectInfo);
        } else {
            throw Exception(
                "Effect system '" + pEffectInfo->EffectSystem() +
                "' not supported"
            );
        }
    } catch (Exception e) {
        throw Exception("Could not create effect: " + e.Message());
    } catch (...) {
        throw Exception("Could not create effect: unknown exception");
    }
    if (!pEffect) {
        // should never happen
        throw Exception("Oops, EffectFactory bug: !pEffect");
    }
    vEffectInstances.push_back(pEffect);
    return pEffect;
}

void EffectFactory::Destroy(Effect* pEffect) {
    for (int i = 0; i < vEffectInstances.size(); i++) {
        if  (vEffectInstances[i] == pEffect) {
            vEffectInstances.erase(vEffectInstances.begin() + i);
            delete pEffect;
        }
    }
}

void EffectFactory::UpdateAvailableEffects() {
    // clear out all old effect infos
    for (int i = 0; i < vEffectInfos.size(); i++) delete vEffectInfos[i];
    vEffectInfos.clear();

    // scan for LADSPA effects
    vEffectInfos = LadspaEffect::AvailableEffects();
}

} // namespace LinuxSampler
