#include "array.h"

DataMap::DataMap()
{
    arraySize = 0;
    keys = nullptr;
    values = nullptr;
}

DataMap::~DataMap()
{
    clear();
}

void DataMap::insert(const string &key, const string &value)
{
    if (arraySize == 0)
    {
        arraySize = 1;
        keys = new string[1];
        keys[0] = key;
        values = new string[1];
        values[0] = value;
        return;
    }
    arraySize++;
    string *temp1 = new string[arraySize];
    string *temp2 = new string[arraySize];
    for (int i = 0; i < arraySize - 1; i++)
    {
        temp1[i] = keys[i];
        temp2[i] = values[i];
    }
    temp1[arraySize - 1] = key;
    temp2[arraySize - 1] = value;
    delete[] keys;
    delete[] values;
    keys = temp1;
    values = temp2;
    return;
}

string DataMap::find(const string &key) const
{
    for (int i = 0; i < arraySize; i++)
    {
        if (keys[i] == key)
        {
            return values[i];
        }
    }
    return "";
}

void DataMap::clear()
{
    if (arraySize != 0)
    {
        arraySize = 0;
        delete[] keys;
        delete[] values;
    }
}