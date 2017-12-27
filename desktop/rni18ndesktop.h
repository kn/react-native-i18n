
/**
 * Copyright (C) 2016, Canonical Ltd.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
 * Author: Justin McPherson <justin.mcpherson@canonical.com>
 *
 */

#ifndef RNI18NDESKTOP_H
#define RNI18NDESKTOP_H

#include <QUrl>

#include "moduleinterface.h"

class RNI18nPrivate;
class RNI18n : public QObject, public ModuleInterface {
    Q_OBJECT

    Q_INTERFACES(ModuleInterface)

    Q_DECLARE_PRIVATE(RNI18n)

public:
    Q_INVOKABLE RNI18n(QObject* parent = 0);
    ~RNI18n();

    Q_INVOKABLE REACT_PROMISE void getLanguages(double successCallback, double errorCallback);
    virtual QString moduleName() override;
    virtual QList<ModuleMethod*> methodsToExport() override;
    virtual QVariantMap constantsToExport() override;
    virtual void setBridge(Bridge* bridge) override;

private:
    QScopedPointer<RNI18nPrivate> d_ptr;
};

#endif // RNI18NDESKTOP_H
