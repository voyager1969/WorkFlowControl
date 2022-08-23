#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;
typedef unsigned int uint;

struct CodeCondition
{
    uint Code = 0;
    bool Condition = 0;

};

class ReturnCode
{
public:
    void setCodeRule(string conditionName, uint returnCode)
    {
        if (!mapReturnRule.count(conditionName))
        {
            cout << "AddErrorConditionName:" << conditionName << endl;
            iKeyCount++;
        }
        mapReturnRule[conditionName].Code = returnCode;
    }

    void autoSetRule(string conditionName)
    {
        if (!mapReturnRule.count(conditionName))
        {
            iKeyCount++;
            mapReturnRule[conditionName].Code = iKeyCount;
        }
    }


    uint getCodeRule(string conditionName)
    {
        if (!mapReturnRule.count(conditionName))
        {
            cout << "ErrorConditionName:" << conditionName << endl;
            return 999999;
        } else
        {
            return mapReturnRule[conditionName].Code;
        }

    }

    void setCondition(string conditionName, bool flagCondition)
    {
        if (!mapReturnRule.count(conditionName))
        {
            cout << "ErrorConditionName:" << conditionName << endl;
        } else
        {
            mapReturnRule[conditionName].Condition = flagCondition;
        }

    }

    bool checkCondition(string conditionName)
    {
        if (conditionName == "")
        {
            return 0;
        }
        return (mapReturnRule[conditionName].Condition);
    }

private:
    uint iKeyCount = 0;
    uint iReturnCode = 0;
    unordered_map<string, CodeCondition> mapReturnRule;
};
