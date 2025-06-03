#include "decoder_factory.h"

#include <iostream>
#include <memory>
#include <ostream>

#include "pid_decoder.h"
#include "msp_protocol.h"
#include "status_decoder.h"

std::unique_ptr<IDecoder> create_decoder(uint8_t command) {
    switch (command) {

        case MSP::MessageID::PID:
            std::cout<<"here we are"<< std::endl;
            return std::make_unique<PIDDecoder>();

        case MSP::MessageID::STATUS:
            std::cout<<"message id is status"<< std::endl;
            return std::make_unique<StatusDecoder>();
        default:
            std::cout<<"default decoder"<<std::endl;
            return nullptr;
    }
}

