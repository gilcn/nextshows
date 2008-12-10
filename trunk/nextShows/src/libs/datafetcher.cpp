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
// QtGui
#include <QtGui/QApplication>


/*
** public:
*/
DataFetcher * DataFetcher::instance()
{
    qDebug() << Q_FUNC_INFO;
    static DataFetcher * dataFetcherInstance = 0;
    if (!dataFetcherInstance) {
        dataFetcherInstance = new DataFetcher(qApp);
    }

    return dataFetcherInstance;
} // instance()

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

    // Cleanup
    clearShowData(showId);

    QUrl urlEL("http://www.tvrage.com/feeds/episode_list.php");
    urlEL.addQueryItem("sid", QString::number(showId));
    doRequest(urlEL, DataFetcher::EpisodeListRequest, showId, QString());

    QUrl urlSI("http://www.tvragee.com/feeds/showinfo.php");
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
            if (success) {
                emit searchResultsReady(searchResults, true, QString());
            } else {
                QString errorText = QString("An error occured while parsing XML document for show \"%1\"!").arg(showName);
                qCritical() << errorText;
                qCritical() << "URL requested:" << reply->request().url().toString();
                qCritical() << "URL processed:" << reply->url().toString();
                qCritical("%s [L:%d-C:%d]", qPrintable(errorMessage), errorLine, errorColumn);
                emit searchResultsReady(NextShows::ShowInfosList(), false, errorText);
            }
        } else {
            QString errorText = QString("A network error occured while searching for show \"%1\" [%2]!").arg(showName).arg(errorCodeToText(reply->error()));
            qCritical() << errorText;
            qCritical() << "URL requested:" << reply->request().url().toString();
            qCritical() << "URL processed:" << reply->url().toString();
            emit searchResultsReady(NextShows::ShowInfosList(), false, errorText);
        }
        break;
    }
    case DataFetcher::ShowInfosRequest: {
        if (reply->error() == QNetworkReply::NoError) {
            bool success;
            QString errorMessage;
            int errorLine;
            int errorColumn;
            NextShows::ShowInfos_t t_showInfos = TvRageParser::parseShowInfos(reply->readAll(), &success, &errorMessage, &errorLine, &errorColumn);
            if (success) {
                m_showInfosHash[showId] = t_showInfos;
            } else {
                QString errorText = QString("An error occured while parsing XML document for ShowInfo ID#%1!").arg(showId);
                qCritical() << errorText;
                qCritical() << "URL requested:" << reply->request().url().toString();
                qCritical() << "URL processed:" << reply->url().toString();
                qCritical("%s [L:%d-C:%d]", qPrintable(errorMessage), errorLine, errorColumn);
                m_showInfosError[showId] = errorText;
            }
        } else {
            QString errorText = QString("A network error occured while retrieving ShowInfo ID#%1 [%2]!").arg(showId).arg(errorCodeToText(reply->error()));
            qCritical() << errorText;
            qCritical() << "URL requested:" << reply->request().url().toString();
            qCritical() << "URL processed:" << reply->url().toString();
            m_showInfosError[showId] = errorText;
        }
        emissionCheck(showId);
        break;
    }
    case DataFetcher::EpisodeListRequest: {
        if (reply->error() == QNetworkReply::NoError) {
            bool success;
            QString errorMessage;
            int errorLine;
            int errorColumn;
            NextShows::EpisodeListList t_episodeList = TvRageParser::parseEpisodeList(reply->readAll(), &success, &errorMessage, &errorLine, &errorColumn);
            if (success) {
                m_episodeListHash[showId] = t_episodeList;
            } else {
                QString errorText = QString("An error occured while parsing XML document for EpisodeList ID#%1!").arg(showId);
                qCritical() << errorText;
                qCritical() << "URL requested:" << reply->request().url().toString();
                qCritical() << "URL processed:" << reply->url().toString();
                qCritical("%s [L:%d-C:%d]", qPrintable(errorMessage), errorLine, errorColumn);
                m_episodeListError[showId] = errorText;
            }
        } else {
            QString errorText = QString("A network error occured while retrieving EpisodeList ID#%1 [%2]!").arg(showId).arg(errorCodeToText(reply->error()));
            qCritical() << errorText;
            qCritical() << "URL requested:" << reply->request().url().toString();
            qCritical() << "URL processed:" << reply->url().toString();
            m_showInfosError[showId] = errorText;
        }
        emissionCheck(showId);
        break;
    }
    default:
        qWarning("%s\nThis should never happen [%d]!!!", Q_FUNC_INFO, requestType);
    }

    reply->deleteLater();
} // requestFinished()


/*
** private:
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
    // Ensure both requests (showinfo + episodelist) were made for this showId
    int count = 0;
    count = (m_showInfosHash.contains(showId)   || m_showInfosError.contains(showId))   ? count + 1 : count;
    count = (m_episodeListHash.contains(showId) || m_episodeListError.contains(showId)) ? count + 1 : count;
    if (count != 2) {
        return;
    }

    // Are all the required data available ?
    if (m_showInfosHash.contains(showId) && m_episodeListHash.contains(showId)) {
        emit episodeListReady(m_showInfosHash.value(showId), m_episodeListHash.value(showId), true, QString());
    } else {
        // If we reach here, we assume there were at least one error at some point
        QString errorText;
        if (m_showInfosError.contains(showId)) {
            errorText = m_showInfosError.value(showId);
        }
        else if (m_episodeListError.contains(showId)) {
            errorText = m_episodeListError.value(showId);
        }
        else {
            qWarning("%s\nThis should never happen!!!", Q_FUNC_INFO);
        }
        emit episodeListReady(NextShows::ShowInfos_t(), NextShows::EpisodeListList(), false, errorText);
    }

    clearShowData(showId); // Cleanup
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

void DataFetcher::clearShowData(const int &showId)
{
    qDebug() << Q_FUNC_INFO;
    m_showInfosHash.remove(showId);
    m_showInfosError.remove(showId);
    m_episodeListHash.remove(showId);
    m_episodeListError.remove(showId);
} // clearShowData()

// EOF - vim:ts=4:sw=4:et:
