# Utilities
collection of juce c++ utilities

## Monitor

Socket Monitor

The socket monitor class uses a posix select() function to montitor the status of a collection of socket file descriptors. When a file descriptor becomes ready to read from or write to the socket monitor can notify a registered delegate class via a specified callback.

## ZeroConf

ZeroConf / Bonjour Utility

The ZeroConf Manager class encapsulates calls to the system's bonjour/zeroconf deamon.

## AudioStreamManager

This class is responsible for streaming audio data to or from a specified udp port. It implements..
