/***
 *  This file is part of SpeechControl.
 *
 *  Copyright (C) 2012 SpeechControl Developers <spchcntrl-devel@thesii.org>
 *            (C) 2012 Adrian Borucki <gentoolx@gmail.com>
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
 *  along with SpeechControl .  If not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef SPEECHCONTROL_DECODER_HPP
#define SPEECHCONTROL_DECODER_HPP

// Qt includes
#include <QMap>
#include <QDir>
#include <QObject>

// local includes
#include <lib/global.hpp>
#include <lib/export.hpp>

namespace SpeechControl
{

class AcousticModel;
class Dictionary;
class LanguageModel;

class Decoder;
class DecoderPrivate;

/**
 * @class Decoder
 *
 * The Decoder class handles the top-layer work of handling
 * PocketSphinx's API into one object. It takes the API of the
 * system and turns it into a full-fledged Qt object that you
 * can manipulate to your whim.
 */
class SPCH_EXPORT Decoder : public QObject
{
    Q_OBJECT

protected:
    Q_DECLARE_PRIVATE (Decoder)
    Q_DISABLE_COPY (Decoder)

    Decoder (DecoderPrivate* p_private, QObject* p_parent = 0);
    QScopedPointer<DecoderPrivate> d_ptr;

public:
    explicit Decoder (QObject* p_parent = 0);
    virtual ~Decoder();
    LanguageModel* languageModel() const;
    Dictionary* dictionary() const;
    AcousticModel* acousticModel() const;
    bool isConfigured() const;
    void setLanguageModel (const QString& p_path);
    void setLanguageModel (const LanguageModel* p_languageModel);
    void setDictionary (const QString& p_path);
    void setDictionary (const Dictionary* p_dictionary);
    void setAcousticModel (const QString& p_path);
    void setAcousticModel (const AcousticModel* p_acousticModel);
};

}

#endif // ABSTRACTSPHINX_HPP
// kate: indent-mode cstyle; replace-tabs on; 
