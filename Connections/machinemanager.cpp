#include "machinemanager.h"

MachineManager::MachineManager(QObject *parent,Machine*m)
    : QObject{parent}
{
    setmachine(m);
}

void MachineManager::setmachine(Machine *m)
{
    machine = m;
}

void MachineManager::SetMachineSenario(int Senario)
{
    if(Senario==senario::Inspection)
    {
        machine->jacklist.at(0)->CycleExecuteOn();
        machine->motorlist.at(0)->JogOn(true);
        machine->Device->WriteCoil(0x815,true);
    }else if(Senario == senario::calibration){
        machine->jacklist.at(0)->CycleExecuteOff();
        machine->jacklist.at(0)->JogOn();
        machine->jacklist.at(1)->JogOn();
        machine->motorlist.at(0)->JogOn(true);
        machine->Device->WriteCoil(0x815,true);
    }else if (Senario==senario::systemOff){
        machine->jacklist.at(0)->CycleExecuteOff();
        machine->jacklist.at(0)->JogOff();
        machine->jacklist.at(1)->JogOff();
        machine->motorlist.at(0)->JogOff();
        machine->Device->WriteCoil(0x815,false);
    }else{

    }
}

void MachineManager::setrejectjack(int jacknumber)
{
    rejectjack = jacknumber;
}

void MachineManager::rejectsample()
{
    machine->jacklist.at(rejectjack)->triggerExecuteOn();
}
