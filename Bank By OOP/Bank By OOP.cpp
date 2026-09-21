
#include <iostream>
#include <string>
#include <iomanip>
#include"clsMainScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include"clsLoginScreen.h"
using namespace std;



int main()
{
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }
   
    return 0;
}