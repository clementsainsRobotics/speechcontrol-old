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

#ifndef SPCHCNTRL_LIB_LANGUAGEMODEL_HXX
#define SPCHCNTRL_LIB_LANGUAGEMODEL_HXX

#include <ngram_model.h>
#include <lib/languagemodel.hpp>
#include <QString>

namespace SpeechControl
{

/**
 * @struct LanguageModelPrivate
 *
 * Contains the internal private work of the language model
 * as defined by SpeechControl.
 */
struct SPCH_EXPORT LanguageModelPrivate {
    Q_DECLARE_PUBLIC(LanguageModel)

    /**
     * @ctor
     * @fn LanguageModelPrivate
     */
    explicit LanguageModelPrivate(LanguageModel* p_qPtr);

    QString m_path;
    ngram_model_t* model;
    LanguageModel* q_ptr;
};
}

#endif /* SPCHCNTRL_LIB_LANGUAGEMODEL_PRIVATE_HPP */
// kate: indent-mode cstyle; replace-tabs on; 
