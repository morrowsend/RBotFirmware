// RBotFirmware
// Rob Dobson 2016

#pragma once

class WorkflowManager;
class CommandExtender;

// Command interpreter
class CommandInterpreter
{
private:
    WorkflowManager* _pWorkflowManager;
    RobotController* _pRobotController;
    CommandExtender* _pCommandExtender;
    bool setWifi(const char* pCmdStr);

public:
    CommandInterpreter(WorkflowManager* pWorkflowManager, RobotController* pRobotController);
    void setSequences(const char* configStr);
    const char* getSequences();
    void setPatterns(const char* configStr);
    const char* getPatterns();
    bool canAcceptCommand();
    bool queueIsEmpty();
    void processSingle(const char* pCmdStr, String& retStr);
    void process(const char* pCmdStr, String& retStr, int cmdIdx = -1);
    void service();
};
