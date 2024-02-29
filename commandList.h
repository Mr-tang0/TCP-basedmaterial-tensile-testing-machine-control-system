#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include <QString>

struct controlCommand
{
    QString CMD_connent = "W001,1;";
    QString CMD_disconnent = "W001,0;";

    QString CMD_stopAllControl = "W003,0;";

    QString CMD_openCircleControl = "W03%1,%2;";

    QString CMD_generalControl = "W020,0;";

    QString CMD_controlChannal = "W010,%1;";
    QString CMD_controlSpeed = "W011,%1;";
    QString CMD_targetChannal = "W12,%1;";
    QString CMD_targetValue = "W13,%1;";
    QString CMD_targetAction = "W14,%1;";
    QString CMD_holdTime = "W15,%1;";
    QString CMD_outputPos = "W16,%1;";

};


#endif // COMMANDLIST_H
