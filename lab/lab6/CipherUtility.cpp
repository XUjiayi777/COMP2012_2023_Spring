#include "CipherUtility.h"

// TODO #5
// Implement the static member function isKeyValid
bool CipherUtility::isKeyValid(const Cipher *cipher)
{
    for (int i = 0; i < (cipher->key.size()); i++)
    {
        if (!isalpha(cipher->key[i]))
        {
            return false;
        }
    }
    return true;
}

// TODO #6
// Implement the static member function removeNonAlphaCharsHelper
string CipherUtility::removeNonAlphaCharsHelper(string str)
{
    if (str == "")
    {
        return str;
    }
    else
    {
        if (isalpha(str[0]))
        {
            string new_string = str.substr(1, str.size());
            return (str[0] + removeNonAlphaCharsHelper(new_string));
        }
        else
        {
            string new_string = str.substr(1, str.size());
            return removeNonAlphaCharsHelper(new_string);
        }
    }
    return "";
}