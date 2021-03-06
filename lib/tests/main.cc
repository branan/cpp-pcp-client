// Refer to https://github.com/philsquared/Catch/blob/master/docs/own-main.md
// for providing our own main function to Catch
#define CATCH_CONFIG_RUNNER

#include "test.hpp"

#include <vector>

// To enable log messages:
// #define ENABLE_LOGGING

#ifdef ENABLE_LOGGING
#define LEATHERMAN_LOGGING_NAMESPACE "puppetlabs.cpp_pcp_client.test"
#include <leatherman/logging/logging.hpp>
#include <boost/nowide/iostream.hpp>
#endif

int main(int argc, char** argv) {
#ifdef ENABLE_LOGGING
    leatherman::logging::setup_logging(boost::nowide::cout);
    leatherman::logging::set_level(leatherman::logging::log_level::debug);
#endif

    // Create the Catch session, pass CL args, and start it
    Catch::Session test_session {};

    // NOTE(ale): to list the reporters use:
    // test_session.configData().listReporters = true;

    // NOTE(ale): out of the box, Reporters are "xml", "junit", "console",
    // and "compact" (single line); "console" is the default
    // test_session.configData().reporterNames =
    //      std::vector<std::string> { "xml" };

    // ShowDurations::Always, ::Never, ::DefaultForReporter
    test_session.configData().showDurations = Catch::ShowDurations::Always;

    // NOTE(ale): enforcing ConfigData::useColour == UseColour::No
    // on Windows is not necessary; the default ::Auto works fine

    return test_session.run(argc, argv);
}
