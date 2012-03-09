/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "wikipediacontentsource.hpp"

#include <QDebug>
#include <QtWebKit/QWebPage>
#include <QtWebKit/QWebFrame>
#include <QtWebKit/QWebElement>

using namespace SpeechControl;

WikipediaContentSource::WikipediaContentSource (QObject* parent) : AbstractContentSource(parent)
{

}

WikipediaContentSource::WikipediaContentSource (const QString& id, QObject* parent) : AbstractContentSource (id, parent)
{

}

WikipediaContentSource::~WikipediaContentSource()
{

}

bool WikipediaContentSource::ready() const
{
    return !wikiFrames.empty();
}

void WikipediaContentSource::order()
{
    // Cleanups
    portalPages.clear();
    portalFrames.clear();
    wikiPages.clear();
    wikiFrames.clear();
    
    portalSuccess = 0;
    portalFail    = 0;
    wikiSuccess   = 0;
    wikiFail      = 0;
    
    portalPhase();
}

void WikipediaContentSource::portalPhase()
{
    // Let's use featured articles from Technology, Society and History portals.
    QUrl tech("http://en.wikipedia.org/wiki/Portal:Technology"),
         society("http://en.wikipedia.org/wiki/Portal:Society"),
         history("http://en.wikipedia.org/wiki/Portal:History");
    
    QList<QUrl> portalUrls;
    portalUrls.append(tech);
    portalUrls.append(society);
    portalUrls.append(history);
    
    Q_FOREACH (QUrl url, portalUrls) {
        QWebPage *page = new QWebPage;
        QWebFrame *fr = page->mainFrame();
        
        connect(fr, SIGNAL(loadFinished(bool)), this, SLOT(wikiPhase(bool)));
        fr->load(url);
        
        portalPages.append(page);
        portalFrames.append(fr);
    }
}

void WikipediaContentSource::wikiPhase(bool ok)
{
    if (ok)
        ++portalSuccess;
    else
        ++portalFail;
    
    if (portalSuccess + portalFail != portalFrames.size())
        return;
    
    // Get featured articles' URLs.
    QList<QUrl> featuredUrls;
    Q_FOREACH (QWebFrame *portal, portalFrames) {
        qDebug() << "URL:" << portal->url();
        QWebElement document = portal->documentElement();
        QWebElementCollection links = document.findAll("p b a");
        
//         qDebug() << "Document has" << document.toPlainText();
        
        Q_FOREACH (QWebElement link, links) {
            if (link.toPlainText() == "Read more...") {
                featuredUrls.append(QUrl(link.attribute("href")));
                break;
            }
        }
    }
    
    // Start loading featured arcticles.
    Q_FOREACH (QUrl url, featuredUrls) {
        QWebPage *page = new QWebPage;
        QWebFrame *frame = page->mainFrame();
        
        connect(frame, SIGNAL(loadFinished(bool)), this, SLOT(parsingPhase(bool)));
        frame->load(url);
        
        wikiPages.append(page);
        wikiFrames.append(frame);
    }
}

void WikipediaContentSource::parsingPhase(bool ok)
{
    if (ok)
        ++wikiSuccess;
    else
        ++wikiFail;
    
    if (wikiSuccess + wikiFail != wikiFrames.size())
        return;
    
    emit generateReady();
}

Content* WikipediaContentSource::generate()
{
    if (!ready()) {
        qWarning() << "[WikipediaContentSource] Not ready for generation.";
        return NULL;
    }
    
    qDebug() << "We have" << wikiFrames.size() << "frames.";
    Q_FOREACH (QWebFrame *frame, wikiFrames) {
        qDebug() << "Text of the featured frame is:" << frame->toPlainText();
    }
    
    return Content::create("Unimplemented yet", "Unimplemented yet", "Unimplemented yet");
}

#include "wikipediacontentsource.moc"
