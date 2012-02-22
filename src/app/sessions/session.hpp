/**
 * This file is part of SpeechControl
 *
 * Copyright 2011 SpeechControl Developers <spchcntrl-devel@thesii.org>
 *
 * SpeechControl is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * SpeechControl is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with SpeechControl; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 **/

#ifndef SESSION_HPP
#define SESSION_HPP

#include <QMap>
#include <QUuid>
#include <QObject>
#include <QDateTime>
#include <QStringList>
#include <QtXml/QDomDocument>

namespace SpeechControl {
    class Corpus;
    class Content;
    class Sentence;
    class Session;

    typedef QList<Session*> SessionList;
    typedef QList<Content*> ContentList;
    typedef QList<Sentence*> SentenceList;

    typedef QMap<QUuid, Content*> ContentMap;
    typedef QMap<QUuid, Session*> SessionMap;

    /**
     * @brief Represents a collection of text to be used for training by @c Sessions.
     *
     * Contents are the pure-text representation of @c Corpus objects; @c Content goes out
     * to provide more specific data about the text being trained.
     **/
    class Content : public QObject {
        Q_OBJECT
        Q_DISABLE_COPY(Content)

    public:
        /**
         * @brief Default constructor.
         * @param p_uuid The uuid of the @c Content.
         **/
        explicit Content(const QUuid&);

        virtual ~Content();

        /**
         * @brief Loads a @c Content object by a specified UUID.
         * @param p_uuid The uuid of the Content to load.
         * @note After loading, you should check to see if isValid() returns true. It's possible for the loading operation to fail.
         **/
        void load(const QUuid&);

        /**
         * @brief Erases the Content, wiping all of its information.
         **/
        void erase();

        /**
         * @brief Counts the pages within this @c Content and returns that number.
         * @return A unsigned integer representing the number of pages in this @c Content.
         **/
        const uint pageCount() const;

        /**
         * @brief Counts the words within this @c Content and returns that number.
         * @return A unsigned integer representing the number of words in the text.
         **/
        const uint words() const;

        /**
         * @brief Counts the characters within this @c Content and returns that number.
         * @return A unsigned integer representing the total number of characters in the text.
         **/
        const uint length() const;

        /**
         * @brief Counts the alphanumber characters within this @c Content and returns that number.
         * @return A unsigned integer representing the total number of alphanumber characters in the text.
         **/
        const uint characters() const;

        /**
         * @brief Obtains the UUID of this Content.
         * @return The UUID of this @c Content.
         **/
        const QUuid uuid() const;

        /**
         * @brief Obtains the title of this Content.
         * @return A string holding the title of this Content.
         **/
        const QString title() const;

        /**
         * @brief ...
         *
         * @return const QString
         **/
        const QString author() const;

        /**
         * @brief ...
         *
         * @return
         **/
        const QStringList pages() const;

        /**
         * @brief
         * @param
         * @return
         **/
        const QString pageAt(const int&) const;

        /**
         * @brief Creates a new @c Content object to be used by @c Session objects.
         * @param p_author The author/writer of this text.
         * @param p_title The title of the text.
         * @param p_text The text that's represented by this @c Content.
         * @return A pointer to the new @c Content object created.
         **/
        static Content* create(const QString&, const QString&, const QString& );

        /**
         * @brief
         * @param
         * @return
         **/
        static Content* obtain(const QUuid&);

        /**
         * @brief
         * @return
         **/
        static ContentList allContents();

    private:
        static QString getPath(const QUuid&);
        static ContentMap s_lst;
        QStringList m_pages;
        QDomDocument* m_dom;
        QUuid m_uuid;
    };

    /**
     * @brief ...
     **/
    class Session : public QObject {
        Q_OBJECT
        Q_DISABLE_COPY(Session)
        Q_PROPERTY(Corpus* Corpus READ corpus WRITE setCorpus)
        Q_PROPERTY(QUuid Uuid READ uuid)
        Q_PROPERTY(Content* Content READ content WRITE setContent)

    public:
        /**
         * @brief ...
         **/
        class Backup {
            friend class Session;
        public:
            virtual ~Backup();
            /**
             * @brief ...
             *
             * @return :Session*
             **/
            Session* session();
            /**
             * @brief ...
             *
             * @return QDateTime
             **/
            QDateTime created();

        private:
            static const QString getPath(const QString&);
            static Backup* generate(const Session&);
            explicit Backup();
            QDomDocument* m_dom;
        };

        /**
         * @brief ...
         **/
        typedef QList<Backup*> BackupList;

        /**
         * @brief ...
         *
         * @param  ...
         **/
        explicit Session(const QUuid&);
        virtual ~Session();
        /**
         * @brief ...
         *
         * @return const QUuid
         **/
        const QUuid uuid() const;
        /**
         * @brief ...
         *
         * @return const bool
         **/
        const bool isCompleted() const;
        /**
         * @brief ...
         *
         * @return const bool
         **/
        const bool isValid() const;
        /**
         * @brief ...
         *
         * @return void
         **/
        void erase() const;
        /**
         * @brief ...
         *
         * @return :Session*
         **/
        Session* clone() const;
        /**
         * @brief ...
         *
         * @return :Session::Backup*
         **/
        Backup* createBackup() const;
        /**
         * @brief ...
         *
         * @return :Session::BackupList*
         **/
        BackupList* backups() const;
        /**
         * @brief ...
         *
         * @return Corpus*
         **/
        Corpus* corpus() const;
        /**
         * @brief ...
         *
         * @return Content*
         **/
        Content* content() const;
        /**
         * @brief ...
         *
         * @return :Sentence*
         **/
        Sentence* firstIncompleteSentence() const;
        /**
         * @brief ...
         *
         * @return :Sentence*
         **/
        Sentence* lastIncompleteSentence() const;
        /**
         * @brief ...
         *
         * @return :SentenceList
         **/
        SentenceList incompletedSentences() const;

        /**
         * @brief ...
         *
         * @return void
         **/
        static void init();
        /**
         * @brief ...
         *
         * @param  ...
         * @return :Session*
         **/
        static Session* obtain(const QUuid&);
        /**
         * @brief ...
         *
         * @param  ...
         * @return :Session*
         **/
        static Session* create(const Content*);
        /**
         * @brief ...
         *
         * @return :SessionList
         **/
        static SessionList allSessions();

    signals:
        /**
         * @brief ...
         *
         * @param  ...
         * @return void
         **/
        void progressChanged(const double& );

    public slots:
        /**
         * @brief ...
         *
         * @param  ...
         * @return void
         **/
        void setCorpus(Corpus* );

        /**
         * @brief ...
         *
         * @param  ...
         * @return void
         **/
        void setContent(Content* );

        /**
         * @brief ...
         *
         * @param  ...
         * @return void
         **/
        void load(const QUuid&);

        /**
         * @brief ...
         *
         * @return void
         **/
        void assessProgress();

    private:
        //static const QString getPath(const QUuid&);
        static QDomDocument* s_dom;
        static QMap<QUuid, QDomElement*> s_elems;
        Corpus* m_corpus;
        Content* m_content;
        QDomElement* m_elem;
    };
}

#endif // SESSION_HPP
// kate: indent-mode cstyle; space-indent on; indent-width 4; replace-tabs on; 
