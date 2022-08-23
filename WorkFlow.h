#pragma once
#include <iostream>
#include <vector>
#include "ReturnCode.h"

using namespace std;

/* 使用方法，继承后定义：
class WorkFlowTest :public WorkFlow
{
public:
    WorkFlowTest()
    {
        objReturnCode.autoSetRule("D");
        objReturnCode.setCondition("D", 1);
        AddFunction((void (WorkFlow::*)())(&WorkFlowTest::dynamicfunc), 0, "D", 1);
    }

    void dynamicfunc()
    {
        std::cout << "test called" << std::endl;
    }
};

main.cpp
     while (objWorkFlowTest.m_steps < X)
    {
        objWorkFlowTest.ActStep();
    }
*/
// WorkFlow的函数对象（工作步骤）
template<typename T>
struct WorkFlowStep
{
    void (T::*func)();   // 函数方法
    unsigned int step;          // 调用步骤
    string strPrerequisite = ""; // 前提条件
    bool flagPrerequisiteOK = 0; // 前提条件满足状态（前提条件若为flagPrerequisiteOK执行下一步）
};

class WorkFlow
{
public:

    ReturnCode objReturnCode;

    unsigned int m_steps{0}; // 当前步骤

    void AddFunction(void (WorkFlow::*func)(), unsigned int step, string strPrerequisite, bool flagPrerequisite)
    {
        WorkFlowStep<WorkFlow> funNew; // 新函数
        // 函数指针，步骤号，前提条件，前提条件满足状态
        funNew.func = func;
        funNew.step = step;
        funNew.strPrerequisite = strPrerequisite;
        funNew.flagPrerequisiteOK = flagPrerequisite;
        vecFuntions.emplace_back(funNew);
    }

    void ActFlowSteps()
    {
        auto it = vecFuntions.begin();
        while(m_steps <vecFuntions.size() )
        {
            while (it != vecFuntions.end())
            {
                if (it->step == m_steps)
                {
                    if (it->func)
                    {
//                        std::cout << "step: " <<  it->step<< std::endl;
                        // 判断条件满足性
                        if (objReturnCode.checkCondition(it->strPrerequisite) == it->flagPrerequisiteOK)
                        {
                            ((*this).*(it->func))();
                        } else
                        {
                            cout << "step: " << it->step << ",Rule:" << it->strPrerequisite << ":Prerequisite not OK!" << endl;
                        }
                        it = vecFuntions.erase(it);
                    }
                    m_steps++;
                }
                else
                {
                    it++;
                }
            }
        }

    }
    std::vector<WorkFlowStep<WorkFlow> > vecFuntions;


};
