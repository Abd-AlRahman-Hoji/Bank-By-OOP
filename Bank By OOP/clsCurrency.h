#pragma once

#include<iostream>
#include<string>
#include "clsString.h"
#include <vector>
#include <fstream>


using namespace std;
class clsCurrency {
    enum enMode { EmptyMode = 0, UpdateMode = 1 };
    enMode _Mode;
    string _Country;
    string _CurrencyCode;
    string _CurrencyName;
    double _Rate;

    static clsCurrency _ConvertLinetoCurrencyObject(string Line, string Seperator = "#//#")
    {

        vector<string> vCurrencyData = clsString::Split(Line, Seperator);
        if (vCurrencyData.size() < 4)
        {
            return _GetEmptyCurrencyObject();
        }

        double Rate = 0;
        try {
            Rate = stod(vCurrencyData[3]); // ÇÓÊÎÏÇã stod ÈÏáÇð ãä stof
        }
        catch (...) {
            return _GetEmptyCurrencyObject();
        }

        return clsCurrency(
            enMode::UpdateMode,
            vCurrencyData[0],
            vCurrencyData[1],
            vCurrencyData[2],
            Rate
        );

    }
    static  vector <clsCurrency> _LoadCurrencysDataFromFile()
    {

        vector <clsCurrency> vCurrencys;

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {
                if (!Line.empty() && Line.back() == '\r')
                    Line.pop_back();

                if (Line.empty()) continue;

                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);

                if (!Currency.IsEmpty())
                {
                    vCurrencys.push_back(Currency);
                }
            }

            MyFile.close();

        }

        return vCurrencys;

    }
    static clsCurrency _GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

    static string  _ConverCurrencyObjectToLine(clsCurrency C, string Seperator = "#//#") {
        string DataLine = "";
        DataLine += C.Country() + Seperator;
        DataLine += C.CurrencyCode() + Seperator;
        DataLine += C.CurrencyName() + Seperator;
        DataLine += to_string(C.Rate());

        return DataLine;
    }
    static void _SaveCurrencyDataToFile(vector<clsCurrency> _vCurrency) {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsCurrency& C : _vCurrency)
            {
                
                    DataLine = _ConverCurrencyObjectToLine(C);
                    MyFile << DataLine << endl;

                

            }

            MyFile.close();

        }

    }

    


    void _Update() {
        vector<clsCurrency> _vCurrency = _LoadCurrencysDataFromFile();
        for (clsCurrency& C : _vCurrency)
        {
            if (C.CurrencyCode() == CurrencyCode())
            {
                C = *this;
                break;
            }

        }

        _SaveCurrencyDataToFile(_vCurrency);

    }


public:
	clsCurrency(enMode Mode , string Country, string CurrencyCode, string CurrencyName, double Rate) {
        _Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

    bool IsEmpty() {
        return (_Mode == enMode::EmptyMode);
    }

    string Country()
    {
        return _Country;
    }

    string CurrencyCode()
    {
        return _CurrencyCode;
    }

   
    string CurrencyName()
    {
        return _CurrencyName;
    }

   
    double Rate()
    {
        return _Rate ;
    }

    static vector <clsCurrency> GetCurrenciesList()
    {
        return _LoadCurrencysDataFromFile();
    }

    static   clsCurrency FindByCode(string CurrencyCode)
    {

        CurrencyCode = clsString::UpperAllString(CurrencyCode);

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (Currency.CurrencyCode() == CurrencyCode)
                {
                    MyFile.close();
                    return Currency;
                }
            }

            MyFile.close();

        }

        return _GetEmptyCurrencyObject();

    }

    static   clsCurrency FindByCountry(string Country)
    {
        Country = clsString::UpperAllString(Country);

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (clsString::UpperAllString(Currency.Country()) == Country)
                {
                    MyFile.close();
                    return Currency;
                }

            }

            MyFile.close();

        }

        return _GetEmptyCurrencyObject();

    }

    static bool IsCurrencyExist(string CurrencyCode)
    {
        clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
        return (!C1.IsEmpty());

    }

     void  UpdateRate(double Rate) {
        _Rate = Rate;
        _Update();
       
    }
   
     float ConvertToUSD(float Amount)
     {
         return (float)(Amount / Rate());
     }

     float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
     {
         float AmountInUSD = ConvertToUSD(Amount);

         if (Currency2.CurrencyCode() == "USD")
         {
             return AmountInUSD;
         }

         return (float)(AmountInUSD * Currency2.Rate());

     }

};

