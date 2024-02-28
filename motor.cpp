#include "motor.h"

motor::motor(QObject *parent)
    : QObject{parent}
{}

bool motor::open(QTcpSocket &mySocket)
{
    if(mySocket.isOpen())
    {
        mySocket.write("I'm in Motor Already!");
    }
}
