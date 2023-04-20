#include "VigenereCipher.h"
#include "Utility.h"
#include <cctype>
#include <iostream>
using namespace std;

// TODO #1
// Initialize the static data member alphabetSize here
const int VigenereCipher::alphabetSize = 26;

// TODO #2
// Implement the encrypt member function according to the given algoirthm.
string VigenereCipher::encrypt(string plaintextMsg) const
{
    string encrypted_message = plaintextMsg;
    string key1 = key;
    int index = 0; // keep track of which character in the key is currently being used
    for (int i = 0; i < key.size(); i++)
    {
        if (isupper(key[i]))
        {
            key1[i] = key[i] + 32;
        }
        else
        {
            key1[i] = key[i];
        }
    }
    for (int j = 0; j < plaintextMsg.size(); j++)
    {
        if (isalpha(encrypted_message[j]))
        {
            if (isupper(encrypted_message[j]))
            {
                encrypted_message[j] += 32;
            }

            int shift;
            if (index >= key.size())
            {
                index = 0;
            }
            shift = key1[index] - 97;
            int check = static_cast<int>(encrypted_message[j]) + shift;
            if (check > 122)
            {
                encrypted_message[j] -= 26;
                encrypted_message[j] += shift;
            }
            else
            {
                encrypted_message[j] += shift;
            }
        }
        else
        {
            if (index >= key.size())
            {
                index = 0;
            }
        }
        index++;
    }
    return encrypted_message;
}

// TODO #3
// Implement the decrypt member function according to the given algoirthm.
string VigenereCipher::decrypt(string ciphertextMsg) const
{
    string decrypted_message = ciphertextMsg;
    string key1 = key;
    int index = 0; // keep track of which character in the key is currently being used
    for (int i = 0; i < key.size(); i++)
    {
        if (isupper(key[i]))
        {
            key1[i] = key[i] + 32;
        }
        else
        {
            key1[i] = key[i];
        }
    }
    for (int j = 0; j < ciphertextMsg.size(); j++)
    {
        if (isalpha(decrypted_message [j]))
        {
            if (isupper(decrypted_message [j]))
            {
                decrypted_message [j] += 32;
            }

            int shift;
            if (index >= key.size())
            {
                index = 0;
            }
            shift = key1[index] - 97;
            int check = static_cast<int>(decrypted_message [j]) - shift;
            if (check < 97)
            {
                decrypted_message [j] += 26;
                decrypted_message [j] -= shift;
            }
            else
            {
                decrypted_message [j] -= shift;
            }
        }
        else
        {
            if (index >= key.size())
            {
                index = 0;
            }
        }
        index++;
    }
    return decrypted_message ;
}

// TODO #4
// Implement the static member function generateRandomKey
// according to the given algorithm.
string VigenereCipher::generateRandomKey(int length)
{
    string generated_key="";
    for (int i = 0; i < length; i++)
    {
        int number = _rand() % alphabetSize;
        char temp = 'a' + number;
        generated_key += temp;
    }
    return generated_key;
}
