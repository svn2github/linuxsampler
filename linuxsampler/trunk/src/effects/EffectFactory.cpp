/*
    Copyright (C) 2010 Christian Schoenebeck
*/

#include "EffectFactory.h"
#include "LadspaEffect.h"

namespace LinuxSampler {

namespace {

class EffectInfos {
public:
    EffectInfos();
    ~EffectInfos();
    void Update();
    uint Count();
    EffectInfo* GetEffectInfo(uint index);
private:
    std::vector<EffectInfo*> infos;
    bool bInitialized;
};

EffectInfos::EffectInfos() : bInitialized(false) {
}

EffectInfos::~EffectInfos() {
    for (int i = 0; i < infos.size(); i++) delete infos[i];
}

void EffectInfos::Update() {
    // clear out all old effect infos
    for (int i = 0; i < infos.size(); i++) delete infos[i];

    // scan for LADSPA effects
    infos = LadspaEffect::AvailableEffects();
}

uint EffectInfos::Count() {
    if (!bInitialized) {
        Update();
        bInitialized = true;
    }
    return infos.size();
}

EffectInfo* EffectInfos::GetEffectInfo(uint index) {
    if (index >= infos.size()) return NULL;
    return infos[index];
}


EffectInfos effectInfos;

std::vector<Effect*> vEffectInstances;

}


////////////////////////////////////////////////////////////////////////////
// class 'EffectFactory'

String EffectFactory::AvailableEffectSystemsAsString() {
    return "LADSPA";
}

uint EffectFactory::AvailableEffectsCount() {
    return effectInfos.Count();
}

EffectInfo* EffectFactory::GetEffectInfo(uint index) {
    return effectInfos.GetEffectInfo(index);
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
    effectInfos.Update();
}

} // namespace LinuxSampler
