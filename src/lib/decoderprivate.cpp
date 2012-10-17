/***
 *  This file is part of SpeechControl.
 *
 *  Copyright (C) 2012 Jacky Alciné <jackyalcine@gmail.com>
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

#include "lib/global.hpp"
#include "lib/decoderprivate.hpp"
#include <QStringList>

using namespace SpeechControl;

DecoderPrivate::DecoderPrivate (Decoder* p_qPtr) :
    config(0), decoder(0), languageModel(0),
    acousticModel(0), dictionary(0), q_ptr(p_qPtr)
{
    // @todo Obtain the default model and dictionary as specified by configuration.
    // @todo Also provide a failsafe if this check fails.
    config = cmd_ln_init(NULL, ps_args(), FALSE,
                         "-hmm", POCKETSPHINX_MODELDIR "/hmm/en_US/hub4wsj_sc_8k",
                         "-lm", POCKETSPHINX_MODELDIR "/lm/en/turtle.DMP",
                         "-dict", POCKETSPHINX_MODELDIR "/lm/en/turtle.dic",
                NULL);

    updateDecoder();
}

void DecoderPrivate::updateConfiguration(const QMap< QString, QString >& p_args){
    // Build up the PocketSphinx configuration object.
    // This requires a few arguments.
    // 1) a previously defined cmd_ln_t to be updated.
    // 2) argument definitions (defaults are in ps_args()).
    // 3) a boolean value telling the system whether or not to fail on strict argument parsing.
    // 4 + 5, ..., n-1, n) arguments to pass in; the first being the argument name and the second being the argument value.

    // Since we can't just expand the name, we'll do this...
    QString arg, value;
    QStringList args = p_args.keys();
    for (ushort i = 0; i < args.count(); i++){
        arg = args.at(i);
        value = p_args.value(arg);
        config = cmd_ln_init(config,ps_args(),TRUE,
                             arg.toStdString().c_str(),
                             value.toStdString().c_str(),NULL);
    }
}

void DecoderPrivate::updateDecoder(){
    if (decoder){
        ps_free(decoder);
        ps_reinit(decoder,config);
    } else {
        decoder = ps_init(config);
    }
}

DecoderPrivate::~DecoderPrivate(){
    ps_free(decoder);
    cmd_ln_free_r(config);
}

// kate: indent-mode cstyle; replace-tabs on; 
