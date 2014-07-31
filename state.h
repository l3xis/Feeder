#ifndef STATE_H
#define STATE_H

#include "Qt"

class state : public QObject
{
public:
    state()
    {
        LoggedIn=false;
        //prevState=RequestState::NoState;
        //currState=Nostate;
    }
    enum RequestState {
        NoState,Auth,Preference,Categories,Subscriptions,Tags,Contents,Markers,Error
    };

private:
     RequestState currState;
     RequestState prevState;

public:
     void setState(RequestState state);
     RequestState getState();

     bool LoggedIn;

};

#endif // STATE_H
