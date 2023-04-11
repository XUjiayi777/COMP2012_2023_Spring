#include "handler.h"

HandlerModule::~HandlerModule()
{
    languageFilter = nullptr;
    toneFilter = nullptr;
    data.clear();
}

void HandlerModule::print() const
{
    std::cout << "Module name = " << m_name << ", this is a Handler, can handle topic = " << topic << std::endl;
}

void HandlerModule::trainData(const string &question, const string &answer)
{
    data.insert(question, answer);
}
string HandlerModule::answer(const string &question) const
{
    string question1=question, answer1="";
    if (languageFilter != nullptr)
    {
        question1 = languageFilter->translatePreData(question);
    }
    if (toneFilter != nullptr)
    {
        question1 = toneFilter->translatePreData(question1);
    }
    answer1 = inneranswer(question1);
    if (answer1 != "")
    {
        if (toneFilter != nullptr)
        {
            answer1 = toneFilter->translatePostData(answer1);
        }
        if (languageFilter != nullptr)
        {
            answer1 = languageFilter->translatePostData(answer1);
        }
        return answer1;
    }
    cout << "Sorry, I don't know";
    return "";
}
string HandlerModule::inneranswer(const string &question) const
{
    string answer = data.find(question);
    return answer;
}

HandlerMap::HandlerMap()
{
    arraySize = 0;
    names = nullptr;
    handlerModules = nullptr;
}

HandlerMap::~HandlerMap()
{
    clear();
}

void HandlerMap::insert(string key, HandlerModule *value)
{
    if (arraySize == 0)
    {
        arraySize = 1;
        names = new string[1];
        names[0] = key;
        handlerModules = new HandlerModule *[1];
        handlerModules[0] = value;
        return;
    }
    arraySize++;
    string *temp1 = new string[arraySize];
    HandlerModule **temp2 = new HandlerModule *[arraySize];
    for (int i = 0; i < arraySize - 1; i++)
    {
        temp1[i] = names[i];
        temp2[i] = handlerModules[i];
    }
    temp1[arraySize - 1] = key;
    temp2[arraySize - 1] = value;
    delete[] names;
    delete[] handlerModules;
    names = temp1;
    handlerModules = temp2;
    return;
}

HandlerModule *HandlerMap::find(const string &key) const
{
    for (int i = 0; i < arraySize; i++)
    {
        if (names[i] == key)
        {
            return handlerModules[i];
        }
    }
    return nullptr;
}

string HandlerMap::getNames(int index) const
{
    if (index < 0)
    {
        return nullptr;
    }
    if (index < arraySize)
    {
        return names[index];
    }
    else
    {
        return nullptr;
    }
}

void HandlerMap::clear()
{
    if (arraySize != 0)
    {
        arraySize = 0;
        delete[] names;
        delete[] handlerModules;
    }
}