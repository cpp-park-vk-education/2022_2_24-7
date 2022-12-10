#pragma once

class IServer {
   public:
    virtual void start_accept() = 0;
    virtual void handle_accept() = 0;
    virtual void stop_accept() = 0;
};
