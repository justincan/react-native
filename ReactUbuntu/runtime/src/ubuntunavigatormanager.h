
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

#ifndef UBUNTUNAVIGATORMANAGER_H
#define UBUNTUNAVIGATORMANAGER_H

#include <QString>
#include <QMap>

#include "reactviewmanager.h"


class QQuickItem;

class UbuntuNavigatorManager : public ReactViewManager
{
  Q_OBJECT
  // Q_PLUGIN_METADATA(IID ReactModuleInterface_IID)
  Q_INTERFACES(ReactModuleInterface)

  Q_INVOKABLE void push(int containerTag, int viewTag);
  Q_INVOKABLE void pop(int containerTag);
  Q_INVOKABLE void clear(int containerTag);

public:
  UbuntuNavigatorManager(QObject* parent = 0);
  ~UbuntuNavigatorManager();

  void setBridge(ReactBridge* bridge) override;

  ReactViewManager* viewManager() override;
  ReactPropertyHandler* propertyHandler(QObject* object);

  QString moduleName() override;
  QList<ReactModuleMethod*> methodsToExport() override;
  QVariantMap constantsToExport() override;

  QStringList customBubblingEventTypes() override;

  QQuickItem* view(const QVariantMap& properties) const override;

private Q_SLOTS:
  void backTriggered();

private:
  void configureView(QQuickItem* view) const;
  void invokeMethod(const QString& methodSignature,
                    QQuickItem* item,
                    const QVariantList& args = QVariantList{});
  QMetaMethod findMethod(const QString& methodSignature, QQuickItem* item);

  mutable int m_id;
  QMap<QPair<QString, QQuickItem*>, QMetaMethod> m_methodCache;
};

#endif // UBUNTUNAVIGATORMANAGER_H
