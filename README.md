# Qt Chat App
A lightweight chat system using Qt and TCP sockets for real-time messaging. This project consists of two applications:
  1. Server App: A Qt-based C++ server that handles message distribution.
  2. Messenger GUI: A QML-based front-end with a C++ model for communication.

Features:
  Send and receive messages in real-time
  TCP socket-based communication 
  Simple, modular design for easy expansion

How It Works:
  The server listens for incoming connections and relays messages between clients.
  The client connects to the server, displays messages, and allows users to send new ones.
  Communication is handled via TCP sockets, ensuring reliable message delivery.
