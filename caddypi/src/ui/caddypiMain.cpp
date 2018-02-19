#include <core.h>
#include <wiringPi.h>

int main( int argc, char * argv[] )
{
    // initialize wiringPi
    if(wiringPiSetupGpio() < 0) {    // using Broadcom GPIO pin mapping
        return -1;
    }
    // setup SPI channel 0
    wiringPiSPISetup(0, 2000000);

    boost::shared_ptr< boost::asio::io_service > io_service(
        new boost::asio::io_service
    );
    boost::shared_ptr< boost::asio::io_service::work > work(
        new boost::asio::io_service::work( *io_service )
    );

    io_service->run();
    
    return 0;
}

