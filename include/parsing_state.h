#ifndef PARSING_STATE_H
#define PARSING_STATE_H

enum class ParsingState {
    WaitingForHeader,
    ReadingProtocolType,
    ReadingDirection,
    ReadingPayloadSize,
    ReadingCommand,
    ReadingPayload,
    ValidatingData,
    Error
};

#endif