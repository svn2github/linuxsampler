/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2008 Christian Schoenebeck                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 ***************************************************************************/

#ifndef LS_EFFECTCHAIN_H
#define LS_EFFECTCHAIN_H

#include "Effect.h"

namespace LinuxSampler {

// just symbol prototyping
class AudioOutputDevice;

/**
 * Container for a series of effects. The effects are sequentially processed,
 * that is the output of the first effect is passed to the input of the next
 * effect in the chain and so on.
 */
class EffectChain {
public:
    /**
     * Constructor.
     *
     * @param pDevice - audio output context for the effects, providing
     *                  informations like samplerate
     */
    EffectChain(AudioOutputDevice* pDevice);

    /**
     * Add the given effect to the end of the effect chain.
     */
    void AppendEffect(Effect* pEffect);

    /**
     * Insert the given effect into the position given by @a iChainPos .
     *
     * @throw Exception - if given position is invalid
     */
    void InsertEffect(Effect* pEffect, int iChainPos) throw (Exception);

    /**
     * Remove effect at chain position @a iChainPos from the effect chain.
     *
     * @throws Exception - if given position is invalid
     */
    void RemoveEffect(int iChainPos) throw (Exception);

    /**
     * Sequentially render the whole effects chain. The final signal
     * will be available in the output channels of the last effect in
     * the chain after this call, which then has to be copied to the
     * desired destination (e.g. the AudioOutputDevice's output channels).
     */
    void RenderAudio(uint Samples);

    /**
     * Returns effect at chain position @a iChainPos .
     */
    Effect* GetEffect(int iChainPos) const;

    /**
     * Returns amount of effects this effect chain currently contains.
     */
    int EffectCount() const;

    /**
     * Enable / disable the given effect. Currently, disabled effects are
     * automatically bypassed. We might add explicit "bypass" control in
     * future though.
     *
     * @throw Exception - if chain position is invalid
     */
    void SetEffectActive(int iChainPos, bool bOn) throw (Exception);

    /**
     * Whether the given effect is currently enabled.
     */
    bool IsEffectActive(int iChainPos) const;

    /**
     * Clears the audio input and output channels of all effects in the chain.
     */
    void ClearAllChannels();

private:
    struct _ChainEntry {
        Effect* pEffect;
        bool    bActive;
    };

    std::vector<_ChainEntry> vEntries;
    AudioOutputDevice*       pDevice;
};

} // namespace LinuxSampler

#endif // LS_EFFECTCHAIN_H
