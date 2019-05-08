#include "histogram.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
//#include "../../slownik/test.h"

using namespace std;

histogram::histogram()
{


    for(int i=0;i<10;i++)
    {
            this->occurranceofdigits[i] = 0; //zerowanie tablicy
            this->frequency[i]=0;
    }

    //cout<<"Default constructor"<<endl;
    //konstruktor domyslny
}

histogram::histogram(histogram& hist)
{
    //konstruktor kopiujacy
    for(int i=0;i<10;i++)
    {
        this->occurranceofdigits[i] = hist.occurranceofdigits[i];
        this->frequency[i]=hist.frequency[i];
    }
}

histogram::~histogram()
{


    //destruktor
}


void histogram::counterevrydigit(int occurranceofdigits[], string text)
{

    //metoda liczy wystapienia kazdej z cyfr
    for( int i = 0; i < text.length(); i++ )
    {

        char a = text[i];
        switch(a)
        {
        case '0':
            occurranceofdigits[0]++;
            break;
        case '1':
            occurranceofdigits[1]++;
            break;
        case '2':
            occurranceofdigits[2]++;
            break;
        case '3':
            occurranceofdigits[3]++;
            break;
        case '4':
            occurranceofdigits[4]++;
            break;
        case '5':
            occurranceofdigits[5]++;
            break;
        case '6':
            occurranceofdigits[6]++;
            break;
        case '7':
            occurranceofdigits[7]++;
            break;
        case '8':
            occurranceofdigits[8]++;
            break;
        case '9':
            occurranceofdigits[9]++;
            break;
        }
    }

}

void histogram::counterfrequency(float frequency[],int occurranceofdigits[], string text)
{
    int len = text.size();
    cout<<"dlugosc:"<<len<<endl;
    for(int i=0;i<10;i++)
    {
        frequency[i] = (float)occurranceofdigits[i]/len;
    }
}

histogram histogram::operator+(const histogram &hist2)
{
    histogram hist;
    //hist.numberofdigits = numberofdigits + hist1.numberofdigits;
    for(int i=0;i<10;i++)
    {
        hist.occurranceofdigits[i] = this->occurranceofdigits[i] + hist2.occurranceofdigits[i];
        hist.frequency[i] = this->frequency[i] + hist2.frequency[i];
    }

    return hist;
}

void histogram::operator+=(const histogram &hist1)
{
    for(int i=0;i<10;i++)
    {
        this->occurranceofdigits[i]+=hist1.occurranceofdigits[i];
        this->frequency[i]+=hist1.frequency[i];
    }

}

bool operator==(histogram &hist, histogram &hist1)
{
    for(int i=0;i<10;i++)
    {
        if(hist.occurranceofdigits[i]!=hist1.occurranceofdigits[i]) //szukamy chociaz jednej roznicy
            return false;
    }
    return true;
}

bool operator!=(histogram &hist1, histogram &hist2)
{
    for(int i=0;i<10;i++)
    {
        if(hist1.occurranceofdigits[i]!=hist2.occurranceofdigits[i]) //szukamy chociaz jednej roznicy
            return true;

    }
    return false;
}

ostream& operator<<(ostream& os, const histogram &hist)
{
    os<<"Occurrance of number 0: "<<hist.occurranceofdigits[0]<<" and frequency:"<<hist.frequency[0]<<endl;
    os<<"Occurrance of number 1: "<<hist.occurranceofdigits[1]<<" and frequency:"<<hist.frequency[1]<<endl;
    os<<"Occurrance of number 2: "<<hist.occurranceofdigits[2]<<" and frequency:"<<hist.frequency[2]<<endl;
    os<<"Occurrance of number 3: "<<hist.occurranceofdigits[3]<<" and frequency:"<<hist.frequency[3]<<endl;
    os<<"Occurrance of number 4: "<<hist.occurranceofdigits[4]<<" and frequency:"<<hist.frequency[4]<<endl;
    os<<"Occurrance of number 5: "<<hist.occurranceofdigits[5]<<" and frequency:"<<hist.frequency[5]<<endl;
    os<<"Occurrance of number 6: "<<hist.occurranceofdigits[6]<<" and frequency:"<<hist.frequency[6]<<endl;
    os<<"Occurrance of number 7: "<<hist.occurranceofdigits[7]<<" and frequency:"<<hist.frequency[7]<<endl;
    os<<"Occurrance of number 8: "<<hist.occurranceofdigits[8]<<" and frequency:"<<hist.frequency[8]<<endl;
    os<<"Occurrance of number 9: "<<hist.occurranceofdigits[9]<<" and frequency:"<<hist.frequency[9]<<endl;
    return os;
}

bool operator>(histogram &hist1,histogram &hist2)
{
    int k = 0;
    for(int i=0; i<10; i++)
    {
        if(hist1.occurranceofdigits[i]>hist2.occurranceofdigits[i])
            k++;
    }

    return (k>5)? true: false;
}

bool operator<(histogram &hist1,histogram &hist2)
{
    int k = 0;
    for(int i=0; i<10; i++)
    {
        if(hist1.occurranceofdigits[i]<hist2.occurranceofdigits[i])
            k++;
    }

    return (k>5)? true: false;
}
