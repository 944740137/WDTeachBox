#ifndef PROTOCOL_H
#define PROTOCOL_H

#define Start 1041
#define Response_Start 1042

#define Request_ChangeVel 1045
#define Response_ChangeVel 1046

#define Request_ChangeController 1066
#define Response_ChangeController 1067

#define Request_ChangePlanner 1068
#define Response_ChangePlanner 1069

#define Ask_SlaveConnect 998
#define Response_SlaveConnect 999

#define Request_BackToZero 995
#define Response_BackToZero 996

#define Request_StopMove 1110
#define Response_StopMove 1111

#define Ask_Position 1115
#define Response_Position 1116

#define Request_CreateRunTask 1121
#define Response_CreateRunTask 1122

#define Request_JogMove 1200
#define Response_JogMove 1201
#define Request_JogCycleMove 1202

#define Request_JogStop 1205
#define Response_JogStop 1206

#define Request_ChangeSpace 1212
#define Response_ChangeSpace 1213

#endif // PROTOCOL_H
