
/**
 * Copyright (c) 2017-present, Status Research and Development GmbH.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include <memory>

#include "bridge.h"
#include "rni18ndesktop.h"
#include <QCryptographicHash>
#include <QDateTime>
#include <QDebug>
#include <QLocale>
#include <QMap>
#include <QNetworkDiskCache>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QQuickImageProvider>

namespace {
struct RegisterQMLMetaType {
    RegisterQMLMetaType() {
        qRegisterMetaType<RNI18n*>();
    }
} registerMetaType;
} // namespace

class RNI18nPrivate {

public:
    RNI18nPrivate() {}

    Bridge* bridge = nullptr;

    QVariantList languages() {
        QStringList languages = QLocale().uiLanguages();
        QVariantList variantLanguages;
        for (QString l : languages) {
            variantLanguages.push_back(l);
        }
        return variantLanguages;
    }
};

RNI18n::RNI18n(QObject* parent) : QObject(parent), d_ptr(new RNI18nPrivate) {}

RNI18n::~RNI18n() {}

void RNI18n::getLanguages(double successCallback, double errorCallback) {
    Q_D(RNI18n);
    QVariantList args;
    args.push_back(d->languages());

    if (d->bridge) {
        d->bridge->invokePromiseCallback(successCallback, args);
    }
}

QString RNI18n::moduleName() {
    return "RNI18n";
}

QList<ModuleMethod*> RNI18n::methodsToExport() {
    return QList<ModuleMethod*>{};
}

QVariantMap RNI18n::constantsToExport() {
    return QVariantMap{{"languages", d_ptr->languages()}};
}

void RNI18n::setBridge(Bridge* bridge) {
    Q_D(RNI18n);
    d->bridge = bridge;
}
