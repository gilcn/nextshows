/*
** Copyright (C) 2008 Gilles Chauvin <gcnweb+nextshows@gmail.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2  of  the  License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be  useful, but
** WITHOUT  ANY  WARRANTY;  without  even  the   implied   warranty  of
** MERCHANTABILITY or FITNESS FOR A  PARTICULAR  PURPOSE. See  the  GNU
** General Public License for more details.
**
** You should have received a copy of the GNU  General  Public  License
** along with  this  program;  if  not,  write  to  the  Free  Software
** Foundation, Inc.,
** 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


// Own
#include "datafetcher.h"
#include "nextshows.h"
#include "libs/tvrageparser.h"
// QtCore
#include <QtCore/QDebug>
#include <QtCore/QMetaEnum>
#include <QtCore/QUrl>


/*
** public:
*/
DataFetcher::DataFetcher(QObject *parent)
    : QObject(parent)
    , m_nam(new QNetworkAccessManager(this))
{
    qDebug() << Q_FUNC_INFO;
    connect(m_nam, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(requestFinished(QNetworkReply *)));
} // ctor()

DataFetcher::~DataFetcher()
{
    qDebug() << Q_FUNC_INFO;
    delete m_nam;
} // dtor()

void DataFetcher::searchShow(const QString &showName)
{
    qDebug() << Q_FUNC_INFO;
    QUrl url("http://www.tvrage.com:80/feeds/search.php");
    url.addQueryItem("results", "-1"); // Request all available results
    url.addQueryItem("show", showName);
    doRequest(url, DataFetcher::SearchShowRequest, -1, showName);
} // searchShow()

void DataFetcher::getEpisodeList(const int &showId)
{
    qDebug() << Q_FUNC_INFO;
    QUrl urlEL("http://www.tvrage.com/feeds/episode_list.php");
    urlEL.addQueryItem("sid", QString::number(showId));
    doRequest(urlEL, DataFetcher::EpisodeListRequest, showId, QString());

    QUrl urlSI("http://www.tvrage.com/feeds/showinfo.php");
    urlSI.addQueryItem("sid", QString::number(showId));
    doRequest(urlSI, DataFetcher::ShowInfosRequest, showId, QString());
} // getEpisodeList()


/*
** private Q_SLOTS:
*/
void DataFetcher::requestFinished(QNetworkReply *reply)
{
    qDebug() << Q_FUNC_INFO;
    DataFetcher::RequestType requestType = DataFetcher::RequestType(reply->request().attribute(QNetworkRequest::Attribute(RequestTypeAttribute)).toInt());
    int showId = reply->request().attribute(QNetworkRequest::Attribute(ShowIdAttribute)).toInt();
    QString showName = reply->request().attribute(QNetworkRequest::Attribute(ShowNameAttribute)).toString();

    switch(requestType) {
    case DataFetcher::SearchShowRequest: {
        if (reply->error() == QNetworkReply::NoError) {
            bool success;
            QString errorMessage;
            int errorLine;
            int errorColumn;
            NextShows::ShowInfosList searchResults = TvRageParser::parseSearchResults(reply->readAll(), &success, &errorMessage, &errorLine, &errorColumn);
            if (!success) {
                QString errorText = QString("Error while parsing XML document for show \"%1\"!").arg(showName);
                qCritical() << errorText;
                qCritical() << "URL requested:" << reply->request().url().toString();
                qCritical() << "URL processed:" << reply->url().toString();
                qCritical("%s [L:%d-C:%d]", qPrintable(errorMessage), errorLine, errorColumn);
                emit searchResultsReady(NextShows::ShowInfosList(), false, errorText);
            } else {
                emit searchResultsReady(searchResults, true, QString());
            }
        } else {
            QString errorText = QString("An error occured while searching for show \"%1\" [%2]!").arg(showName).arg(errorCodeToText(reply->error()));
            qCritical() << errorText;
            qCritical() << "URL requested:" << reply->request().url().toString();
            qCritical() << "URL processed:" << reply->url().toString();
            emit searchResultsReady(NextShows::ShowInfosList(), false, errorText);
        }
        break;
    }
    case DataFetcher::ShowInfosRequest: {
        m_showInfosNetworkError[showId] = reply->error();
        if (reply->error() == QNetworkReply::NoError) {
            bool success;
            QString errorMessage;
            int errorLine;
            int errorColumn;
            m_showInfosHash[showId] = TvRageParser::parseShowInfos(reply->readAll(), &success, &errorMessage, &errorLine, &errorColumn);
            if (!success) {
                QString errorText = QString("Error while parsing XML document for ShowInfo ID#%1!").arg(showId);
                qCritical() << errorText;
                qCritical() << "URL requested:" << reply->request().url().toString();
                qCritical() << "URL processed:" << reply->url().toString();
                qCritical("%s [L:%d-C:%d]", qPrintable(errorMessage), errorLine, errorColumn);
                // TODO: Emit error SIGNAL (parsing error)
            } else {
                // TODO: Emit success SIGNAL 
            }
        } else {
            // TODO: Emit error SIGNAL (network error) 
        }
        break;
    }
    case DataFetcher::EpisodeListRequest: {
        m_episodeListNetworkError[showId] = reply->error();
        if (reply->error() == QNetworkReply::NoError) {
            bool success;
            QString errorMessage;
            int errorLine;
            int errorColumn;
            m_episodeListHash[showId] = TvRageParser::parseEpisodeList(reply->readAll(), &success, &errorMessage, &errorLine, &errorColumn);
            if (!success) {
                QString errorText = QString("Error while parsing XML document for EpisodeList ID#%1!").arg(showId);
                qCritical() << errorText;
                qCritical() << "URL requested:" << reply->request().url().toString();
                qCritical() << "URL processed:" << reply->url().toString();
                qCritical("%s [L:%d-C:%d]", qPrintable(errorMessage), errorLine, errorColumn);
                // TODO: Emit error SIGNAL (parsing error)
            } else {
                // TODO: Emit success SIGNAL 
            }
        } else {
            // TODO: Emit error SIGNAL (network error) 
        }
        break;
    }
    default:
        qWarning("%s\nThis should never happen! [%d]", Q_FUNC_INFO, requestType);
    }

    reply->deleteLater();
} // requestFinished()


/*
** private:
*/
void DataFetcher::doRequest(const QUrl &url, DataFetcher::RequestType requestType, const int &showId, const QString &showName="")
{
    qDebug() << Q_FUNC_INFO;
    QNetworkRequest request;
    QString httpUA = QString("nextShows/%1 (http://nextshows.googlecode.com/)").arg(NEXTSHOWS_VERSION);
    request.setRawHeader("User-Agent", qPrintable(httpUA));
    request.setUrl(url);

    // Set some attributes
    // Request Type
    request.setAttribute(QNetworkRequest::Attribute(RequestTypeAttribute), QVariant((int)requestType));
    // Show ID
    request.setAttribute(QNetworkRequest::Attribute(ShowIdAttribute), QVariant(showId));
    // Show Name
    request.setAttribute(QNetworkRequest::Attribute(ShowNameAttribute), QVariant(showName));

    m_nam->get(request);
} // doRequest()

void DataFetcher::emissionCheck(const int &showId)
{
    qDebug() << Q_FUNC_INFO;
    bool errorCheck = (m_showInfosNetworkError.contains(showId) && m_episodeListNetworkError.contains(showId));
    if (errorCheck) {
//        m_showInfosError.value(showId);
//        m_episodeListError.value(showId);
    }

    bool check = (m_showInfosHash.contains(showId) && m_episodeListHash.contains(showId));

    if (check) {
        emit episodeListReady(m_showInfosHash.value(showId), m_episodeListHash.value(showId));
        m_showInfosHash.remove(showId);
        m_showInfosNetworkError.remove(showId);
        m_episodeListHash.remove(showId);
        m_episodeListNetworkError.remove(showId);
    }
} // emissionCheck()

QString DataFetcher::errorCodeToText(QNetworkReply::NetworkError errorCode)
{
    qDebug() << Q_FUNC_INFO;
    QString errorName;
    QMetaObject meta = QNetworkReply::staticMetaObject;
    for (int i=0; i < meta.enumeratorCount(); ++i) {
        QMetaEnum m = meta.enumerator(i);
        if (m.name() == QLatin1String("NetworkError")) {
            errorName = QLatin1String(m.valueToKey(errorCode));
            break;
        }
    }

    return errorName;
} // errorCodeToText()


// EOF - vim:ts=4:sw=4:et:
