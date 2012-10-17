/***
 *  This file is part of SpeechControl.
 *
 *  Copyright (C) 2012 Adrian Borucki <adrian.borucki@thesii.org>
 *                2012 Jacky Alcine <jacky.alcine@thesii.org>
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

#include <QDebug>

#include "lib/acousticmodel.hpp"
#include "lib/dictionary.hpp"
#include "lib/languagemodel.hpp"
#include "lib/decoderprivate.hpp"
#include "lib/decoder.hpp"

using namespace SpeechControl;

Decoder::Decoder (QObject* p_parent) : QObject (p_parent),
    d_ptr (new DecoderPrivate (this))
{
}

Decoder::Decoder (DecoderPrivate* p_private, QObject* p_parent) :
    QObject (p_parent), d_ptr (p_private)
{

}

Decoder::Decoder (const Decoder& p_other) :
    QObject (p_other.parent()),
    d_ptr (const_cast<DecoderPrivate*> (p_other.d_ptr.data()))
{

}

bool Decoder::isConfigured() const
{
    Q_D(const Decoder);
    return (d->config != NULL && d->dictionary != NULL);
}

LanguageModel* Decoder::languageModel() const
{
    Q_D (const Decoder);
    return d->languageModel;
}

Dictionary* Decoder::dictionary() const
{
    Q_D (const Decoder);
    return d->dictionary;
}

AcousticModel* Decoder::acousticModel() const
{
    Q_D (const Decoder);
    return d->acousticModel;
}

void Decoder::setLanguageModel (const QString& p_path)
{
    Q_D (Decoder);
    
    if (QFile::exists (p_path)) {
        d->languageModel = LanguageModel::fromDirectory(p_path);
        ngram_model_t* ngram_model = ps_get_lmset(d->decoder);
        ngram_model_set_select(ngram_model,languageModel()->internalName().toLocal8Bit());
    }
    else {
        qWarning() << "[AbstractSphinx] Given language model path" << p_path << "does not exist.";
    }
}

void Decoder::setLanguageModel (const LanguageModel* p_languageModel)
{
    if (p_languageModel) {
        setLanguageModel (p_languageModel->path());
    }
}

void Decoder::setDictionary (const QString& p_path)
{
    Q_D (Decoder);
    
    if (QFile::exists (p_path)) {
        d->dictionary = Dictionary::obtainFromPath(p_path);
    }
    else {
        qWarning() << "[AbstractSphinx] Given dictionary path" << p_path << "does not exist.";
    }
}

void Decoder::setDictionary (const Dictionary* p_dictionary)
{
    if (p_dictionary) {
        setDictionary (p_dictionary->path());
    }
}

void Decoder::setAcousticModel (const QString& p_path)
{
    Q_D (Decoder);
    
    if (QFile::exists (p_path)) {
        d->acousticModel = new AcousticModel(p_path,this);
    }
    else {
        qWarning() << "[AbstractSphinx] Given acoustic model path" << p_path << "does not exist.";
    }
}

void Decoder::setAcousticModel (const AcousticModel* p_acousticModel)
{
    if (p_acousticModel && p_acousticModel->isValid()) {
        setAcousticModel(p_acousticModel->path());
    }
}

Decoder::~Decoder()
{
}

#include "decoder.moc"
// kate: indent-mode cstyle; indent-width 4; replace-tabs on;
