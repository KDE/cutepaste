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
#include <QCoreApplication>

int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);
    application.setOrganizationName("CutePaste");
    application.setApplicationName("CutePaste Desktop Console Frontend");

    QTextStream standardOutputStream(stdout);

    QFile dataFile;
    dataFile.open(stdin, QIODevice::ReadOnly);

    QNetworkRequest networkRequest;
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

        if (identifierValue.isString()) {
            standardOutputStream << identifierValue.toString();
            endl(standardOutputStream);
        }
    });

    QObject::connect(networkReplyScopedPointer.data(), static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), [&](QNetworkReply::NetworkError networkReplyError) {
        if (networkReplyError != QNetworkReply::NoError) {
            QTextStream standardOutputStream2(stdout);
            standardOutputStream2 << networkReplyScopedPointer->errorString();
            // endl(standardOutputStream);
        }
    });

    QObject::connect(networkReplyScopedPointer.data(), &QNetworkReply::sslErrors, [&](QList<QSslError> networkReplySslErrors) {
        if (!networkReplySslErrors.isEmpty()) {
            foreach (const QSslError &networkReplySslError, networkReplySslErrors) {
                standardOutputStream << networkReplySslError.errorString();
                // endl(standardOutputStream);
            }
        }
    });

    bool returnValue = application.exec();

    dataFile.close();
    if (dataFile.error() != QFileDevice::NoError) {
        standardOutputStream << dataFile.errorString();
        // endl(standardOutputStream);
    }

    return returnValue;
}
