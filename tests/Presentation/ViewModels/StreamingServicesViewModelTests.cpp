#include <catch.hpp>
#include <MellowPlayer/Presentation.hpp>
#include <MellowPlayer/Infrastructure.hpp>
#include "../../Mocks/StreamingServiceLoaderMock.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace fakeit;

TEST_CASE("StreamingServicesViewModel") {
    auto loaderMock = StreamingServiceLoaderMock::get();
    ApplicationSettings  appSettings;
    StreamingServicesManager servicesManager(loaderMock.get());
    StreamingServicesViewModel viewModel(servicesManager, appSettings);

    Verify(Method(loaderMock, load)).Exactly(1);
    REQUIRE(viewModel.getModel()->rowCount() == servicesManager.getServices().count());

    SECTION("setCurrentService_change_currentIndex") {
        REQUIRE(viewModel.getCurrentIndex() == -1);
        REQUIRE(viewModel.getCurrentService() == nullptr);
        viewModel.setCurrentService(viewModel.getModel()->getItems()[1]);
        REQUIRE(viewModel.getCurrentIndex() == 1);
        REQUIRE(viewModel.getCurrentService() == viewModel.getModel()->getItems()[1]);
        viewModel.setCurrentService(viewModel.getModel()->getItems()[1]);
        viewModel.setCurrentIndex(1);

        SECTION("currentIndexMemorizedForNextLoad") {
            StreamingServicesManager servicesManager2(loaderMock.get());
            StreamingServicesViewModel viewModel2(servicesManager2, appSettings);
            REQUIRE(viewModel2.getModel()->rowCount() == servicesManager2.getServices().count());
            REQUIRE(viewModel2.getCurrentIndex() == 1);
        }
    }
}

