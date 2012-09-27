/***
 *  This file is part of SpeechControl.
 *
 *  Copyright (C) 2012 Jacky Alciné <jacky.alcine@thesii.org>
 *
 *  SpeechControl is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  SpeechControl is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with SpeechControl.  If not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef SPCHCNTRL_LIB_SPHINX_ABSTRACT_HXX_
#define SPCHCNTRL_LIB_SPHINX_ABSTRACT_HXX_

#include <pocketsphinx.h>
#include <lib/sphinx/abstract.hpp>

namespace SpeechControl
{

/**
 * @struct DecoderPrivate
 *
 * Contains the internal private work of the decoder for
 * SpeechControl.
 */
struct SPCH_EXPORT DecoderPrivate {
    Q_DECLARE_PUBLIC (Decoder)

    /**
     * @ctor
     * @fn DecoderPrivate
     *
     * Creates a new d-pointer for a Decoder object.
     *
     * @param p_qPtr The Decoder that this d-pointer is designed for.
     */
    explicit DecoderPrivate (Decoder* p_qPtr);

    /**
     * @dtor
     * @fn ~DecoderPrivate
     *
     * Represents the destructor for the Decoder object.
     */
    virtual ~DecoderPrivate();

    cmd_ln_t* config;
    ps_decoder_t* decoder;
    LanguageModel* languageModel;
    AcousticModel* acousticModel;
    Dictionary* dictionary;
    Decoder* q_ptr;
};

}

#endif /* SPCHCNTRL_LIB_AUDIOSOURCE_ABSTRACT_HXX_ */
// kate: indent-mode cstyle; replace-tabs on; 
