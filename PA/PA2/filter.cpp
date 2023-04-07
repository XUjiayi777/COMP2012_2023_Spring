#include "filter.h"

FilterModule::~FilterModule()
{
    preData.clear();
    postData.clear();
}

void FilterModule::print() const
{
    std::cout << "Module name = " << m_name << ", this is a filter, filter type = " << getFilterType(type) << std::endl;
}

void FilterModule::trainPreData(const string &source, const string &target)
{
    preData.insert(source, target);
}

void FilterModule::trainPostData(const string &source, const string &target)
{
    postData.insert(source, target);
}

string FilterModule::translatePreData(string question) const
{
    string question_translated = preData.find(question);
    if (question_translated != "")
    {
        return question_translated;
    }
    return question;
}

string FilterModule::translatePostData(string question) const
{
    string question_translated = postData.find(question);
    if (question_translated != "")
    {
        return question_translated;
    }
    return question;
}

void FilterArray::insert(FilterModule *input)
{
    if (arraySize == 0)
    {
        arraySize = 1;
        array = new FilterModule *[1];
        array[0] = input;
        return;
    }
    arraySize++;
    FilterModule **temp1 = new FilterModule *[arraySize];
    for (int i = 0; i < arraySize - 1; i++)
    {
        temp1[i] = array[i];
    }
    temp1[arraySize - 1] = input;
    delete[] array;
    ;
    array = temp1;
    return;
}
FilterModule *FilterArray::get(int index) const
{
    if (index < 0)
    {
        return nullptr;
    }
    if (index < arraySize)
    {
        return array[index];
    }
    else
    {
        return nullptr;
    }
}
