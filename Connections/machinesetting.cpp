#include "machinesetting.h"

machinesetting::machinesetting(QObject *parent,Machine*m)
    : QObject{parent}
{
    setmachine(m);
}

void machinesetting::setmachine(Machine *m)
{
    machine = m;
}

void machinesetting::UpdateJackSetting(int jacknimber, double delayjack, double jacktime)
{
    machine->jacklist.at(jacknimber)->SetDelayTime(delayjack);
    machine->jacklist.at(jacknimber)->SetTimeDuration(jacktime);

}

void machinesetting::UpdateMotorSetting(int Motornumber, double motorspeed)
{
    machine->motorlist.at(Motornumber)->SetFreqPulse(motorspeed);
}

void machinesetting::JackJogTest(int jacknumber, bool Direction)
{
    if(Direction)
        machine->jacklist.at(jacknumber)->JogOn();
    else
        machine->jacklist.at(jacknumber)->JogOff();
}

void machinesetting::JackCycleState(int jacknumber, bool EXC)
{
    if(EXC)
        machine->jacklist.at(jacknumber)->CycleExecuteOn();
    else
        machine->jacklist.at(jacknumber)->CycleExecuteOff();
}

void machinesetting::JackTriggerState(int jacknumber, bool EXC)
{
    if(EXC)
        machine->jacklist.at(jacknumber)->triggerExecuteOn();
    else
        machine->jacklist.at(jacknumber)->triggerExecuteOff();
}

void machinesetting::MotorState(int Motornumber, bool DIrection, bool OnOff)
{
    if(OnOff)
        machine->motorlist.at(Motornumber)->JogOn(DIrection);
     else
        machine->motorlist.at(Motornumber)->JogOff();

}
