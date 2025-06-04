#pragma once
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
