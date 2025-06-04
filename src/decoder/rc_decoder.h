
#include "idecoder.h"

class RCDecoder : public IDecoder {
public:
    DecodedTypes decode(const std::vector<uint8_t>& payload) override;
};

