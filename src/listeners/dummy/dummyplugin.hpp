/*
    Copyright (c) 2013 Jacky Alcine <me@jalcine.me>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef SPEECHCONTROL_LISTENERS_DUMMYPLUGIN_HPP
#define SPEECHCONTROL_LISTENERS_DUMMYPLUGIN_HPP

#include <listeners/plugin.hpp>
#include <QtPlugin>

namespace SpeechControl {

namespace Listeners {

class DummyPlugin : public AbstractPlugin
{

public:
  explicit DummyPlugin(QObject* parent = 0);
  virtual QSettings* settings() const;
  virtual AbstractListener* listener() const;
};

}

}

Q_EXPORT_PLUGIN2(speechcontrol-listener-dummy, SpeechControl::Listeners::DummyPlugin);

#endif // SPEECHCONTROL_LISTENERS_DUMMYPLUGIN_HPP
