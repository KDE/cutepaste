/******************************************************************************
 * This file is part of the CutePaste project
 * Copyright (c) 2013 Laszlo Papp <lpapp@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <QSslError>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTcpSocket>

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QScopedPointer>
#include <QTextStream>
#include <QList>
#include <QString>
#include <QCoreApplication>

int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);
    application.setOrganizationName("CutePaste");
    application.setApplicationName("CutePaste Desktop Console Frontend");

    QTextStream standardOutputStream(stdout);
    QNetworkRequest networkRequest;
    QFile dataFile;
    QString firstArgument = application::arguments().at(1)
    dataFile.open(firstArgument.isEmpty() ? stdin : firstArgument, QIODevice::ReadOnly);

    networkRequest.setAttribute(QNetworkRequest::DoNotBufferUploadDataAttribute, true);
    networkRequest.setUrl(QUrl("http://sandbox.paste.kde.org/api/json/create"));

    QNetworkAccessManager networkAccessManager;
    QScopedPointer<QNetworkReply> networkReplyScopedPointer(networkAccessManager.post(networkRequest, &dataFile));
    QObject::connect(networkReplyScopedPointer.data(), &QNetworkReply::finished, [&]() {
        QJsonDocument jsonDocument = QJsonDocument::fromJson(networkReplyScopedPointer->readAll());
        if (!jsonDocument.isObject())
            return;
        
        QJsonObject jsonObject = jsonDocument.object();
        QJsonValue identifierValue = jsonObject.value(QStringLiteral("id"));

        if (identifierValue.isString())
            endl(standardOutputStream << identifierValue.toString());
    });

    QObject::connect(networkReplyScopedPointer.data(), static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), [&](QNetworkReply::NetworkError networkReplyError) {
        if (networkReplyError != QNetworkReply::NoError)
            endl(standardOutputStream << networkReplyScopedPointer->errorString());
    });

    QObject::connect(networkReplyScopedPointer.data(), &QNetworkReply::sslErrors, [&](QList<QSslError> networkReplySslErrors) {
        if (!networkReplySslErrors.isEmpty()) {
            foreach (const QSslError &networkReplySslError, networkReplySslErrors)
                endl(standardOutputStream << networkReplySslError.errorString());
        }
    });

    bool returnValue = application.exec();

    dataFile.close();
    if (dataFile.error() != QFileDevice::NoError)
        endl(standardOutputStream << dataFile.errorString());

    return returnValue;
}
