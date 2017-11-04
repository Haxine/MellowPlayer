#pragma once

#include "IApplication.hpp"

namespace MellowPlayer::Domain
{
    class IQtApplication;
    class IMainWindow;
    class StreamingServicesController;
    class IHotkeysController;
    class ISystemTrayIcon;
    class INotifier;
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class CoreApplication : public IApplication
    {
    public:
        CoreApplication(Domain::IQtApplication& qtApp, Domain::IMainWindow& mainWindow,
                        Domain::StreamingServicesController& streamingServices, Domain::IHotkeysController& kotkeys,
                        Domain::ISystemTrayIcon& systemTrayIcon, Domain::INotifier& notifier);

        void initialize() override;
        void restoreWindow() override;
        int run() override;
        void quit() override;

    private:
        Domain::ILogger& logger_;
        Domain::IQtApplication& qtApp_;
        Domain::IMainWindow& mainWindow_;
        Domain::StreamingServicesController& streamingServices_;
        Domain::IHotkeysController& kotkeys_;
        Domain::ISystemTrayIcon& systemTrayIcon_;
        Domain::INotifier& notifier_;
    };
}
