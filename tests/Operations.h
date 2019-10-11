/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// We don't care about performance related checks in the tests
// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates,qstring-allocations

#ifndef KDDOCKWIDGETS_TESTING_OPERATIONS_H
#define KDDOCKWIDGETS_TESTING_OPERATIONS_H

#include "KDDockWidgets.h"

#include <QObject>
#include <QVector>

#include <memory>

namespace KDDockWidgets {

class DockWidgetBase;
class MainWindowBase;

namespace Testing {
namespace Operations {

enum OperationType {
    OperationType_None = 0,
    OperationType_CloseViaDockWidgetAPI, ///< Closing programatically via DockWidget::close()
    OperationType_HideViaDockWidgetAPI,  ///< Hidding programatically via DockWidget::hide()
    OperationType_ShowViaDockWidgetAPI,  ///< Hidding programatically via DockWidget::show()
    OperationType_AddDockWidget,        ///< MainWindow::addDockWidget()
    OperationType_Count /// Keep at end
};

///@brief Describes a testable action.
class OperationBase {

public:
    typedef std::shared_ptr<OperationBase> Ptr;
    typedef QVector<OperationBase::Ptr> List;
    explicit OperationBase(OperationType);
    virtual ~OperationBase();

    void execute();
protected:
    virtual void execute_impl() = 0;
    DockWidgetBase* dockByName(const QString &) const;
    MainWindowBase* mainWindowByName(const QString &) const;
private:
    const OperationType m_operationType;
};

class CloseViaDockWidgetAPI : public OperationBase
{
public:
    CloseViaDockWidgetAPI(const QString &dockWidgetName);

protected:
    void execute_impl() override;
    const QString m_dockWidgetName;
};

class HideViaDockWidgetAPI : public OperationBase
{
public:
    HideViaDockWidgetAPI(const QString &dockWidgetName);

protected:
    void execute_impl() override;
    const QString m_dockWidgetName;
};

class ShowViaDockWidgetAPI : public OperationBase
{
public:
    ShowViaDockWidgetAPI(const QString &dockWidgetName);

protected:
    void execute_impl() override;
    const QString m_dockWidgetName;
};

struct AddDockWidgetParams {
    QString mainWindowName;
    QString dockWidgetName;
    QString dockWidgetRelativeToName;
    KDDockWidgets::Location location;
    KDDockWidgets::AddingOption addingOption;
};

class AddDockWidget : public OperationBase
{
public:
    explicit AddDockWidget();

protected:
    void execute_impl() override;
};

}
}
}

#endif