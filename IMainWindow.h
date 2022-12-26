#ifndef IMAINWINDOW_H
#define IMAINWINDOW_H

class IMainWindow
{
public:
    virtual void serverAsked(std::string) = 0;
};

#endif // IMAINWINDOW_H
