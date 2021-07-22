#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <exception>
#include <stdexcept>

void makeSentence(char *tab, int length)
{
    for (int j = 0; j < length; j++)
    {
        tab[j] = 'a' + rand() % 26;
    }
}

int convertLetterInNumber(char letter)
{
    const int NUMBERASCIITOALPHABET = 87;
    return (int)letter - NUMBERASCIITOALPHABET;
}

std::string convertToString(char *a, int size)
{
    int i;
    std::string s = "";
    for (i = 0; i < size; i++)
    {
        s = s + a[i];
    }
    return s;
}

int getRandomizedValue(int number)
{
    const int MINRAND = 1;
    const int MAXRAND = 615384;
    return number * (rand() % MAXRAND + MAXRAND);
}

std::string getHexValue(int randomizedValue)
{
    char hex[5];
    int hex_size = sizeof(hex) / sizeof(char);
    std::string s_hex = convertToString(hex, hex_size);
    sprintf(hex, "%x", randomizedValue);
    return hex;
}

void getRGBValue(std::string hexValue, int *red, int *blue, int *green, int *tmp1, int *tmp2, int *tmp3)
{
    std::string hexRed = hexValue.substr(0, 2);
    std::string hexGreen = hexValue.substr(2, 2);
    std::string hexBlue = hexValue.substr(4, 2);
    try
    {
        *tmp1 = std::stoi(hexRed, nullptr, 16);
        *tmp2 = std::stoi(hexGreen, nullptr, 16);
        *tmp3 = std::stoi(hexBlue, nullptr, 16);
    }
    catch (std::invalid_argument &e)
    {
        std::cout << "exception 1" << e.what();
    }
    catch (std::out_of_range &e)
    {
        std::cout << "exception 2" << e.what();
    }

    red = tmp1;
    blue = tmp2;
    green = tmp3;
}

void makeImage(char *tab)
{
    int *red, *blue, *green = 0;
    HDC hdc = GetDC(GetConsoleWindow());
    int counter = 0;
    int *tmp1, *tmp2, *tmp3 = 0;
    for (int x = 0; x < 1920; x++)
    {
        for (int y = 0; y < 1080; y++)
        {
            int letterNumber = 0;
            letterNumber = convertLetterInNumber(tab[counter]);
            letterNumber = getRandomizedValue(letterNumber);
            std::string hexValue = getHexValue(letterNumber);

            getRGBValue(hexValue, red, green, blue, tmp1, tmp2, tmp3);
            SetPixel(hdc, x, y, RGB(*red, *green, *blue));
            counter++;
            int a = 0;
        }
    }
}

int main(void)
{

    const int SIZE = 2073600;
    char *tab = new char[SIZE];
    makeSentence(tab, SIZE);
    char tab1 = tab[2];
    makeImage(tab);
    delete (tab);
    return 0;
}