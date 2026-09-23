#pragma once
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsCurrency.h"
class clsFindCurrencyScreen :clsScreen
{
	enum enOption
	{
		eByCode = 1,
		eByCountryName = 2
	};

	static short _ReadOptionCodeOrCountry() {

		short Num = 0;
		cout << "Find By : [1] Code or [2] Country ?";
		Num = clsInputValidate::ReadShortNumberBetween(1, 2, "Enter Number between 1 to 6? ");
		return Num;

	}
	static string ReadCodeOrCountry(string Message) {
		string Question;
		cout << Message;
		Question = clsInputValidate::ReadString();
		return Question;
	}

	static clsCurrency FindByCode() {

		string Code = ReadCodeOrCountry("\nPlease Enter CurrencyCode:");
		return clsCurrency::FindByCode(Code);

	}
	static clsCurrency FindByCountry() {
		string Country = ReadCodeOrCountry("Please Enter Country Name:");
		return clsCurrency::FindByCountry(Country);



	}

	static clsCurrency _CurrencyByCodeOrCountry(enOption Option) {


		switch (Option)
		{
		case clsFindCurrencyScreen::eByCode:
			return FindByCode();

			break;
		case clsFindCurrencyScreen::eByCountryName:
			return FindByCountry();
			break;

		}



	}
	static void PrintCurrencyInfo(clsCurrency C) {

		cout << "--------Currency-----" << endl;
		cout << "Country           :" << C.Country() << endl;
		cout << "Code              :" << C.CurrencyCode() << endl;
		cout << "Currency Country  :" << C.CurrencyName() << endl;
		cout << "Rate              :" << C.Rate() << endl;
		cout << "----------------------------------------\n\n";
	}

	static void _Result(clsCurrency currency) {

		if (currency.IsEmpty()) {


			cout << "\n\nIs Empty :-(\n";
		}
		else {

			cout << "\n\nFind Successfuly :-)\n\n";
			PrintCurrencyInfo(currency);
		}


	}



public:
	static void ShowFindCurrencyScreen() {

		_DrawScreenHeader("\t\t Find Currency Screen");


		clsCurrency Currency = _CurrencyByCodeOrCountry(enOption(_ReadOptionCodeOrCountry()));
		_Result(Currency);


	}

};