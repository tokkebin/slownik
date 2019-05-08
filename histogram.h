#ifndef histogram_h
#define histogram_h

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class histogram
{

    public:
        //atrybuty
        int occurranceofdigits[10];
        float frequency[10];
        //konstruktory
        histogram();//domyslny
        histogram(string text);//z parametrem
        histogram(histogram &hist);//kopiujacy

        //destruktor
        ~histogram();

        //methods
        void counterevrydigit(int occurranceofdigits[], string text); //wystapienia konkretnych cyfr
        void counterfrequency(float frequency[], int occurranceofdigits[], string text); //czestosc wystapien

        //operators
        friend bool operator ==(histogram &hist, histogram &hist1);
        friend bool operator !=(histogram &hist, histogram &hist1);
        friend bool operator >(histogram &hist1, histogram &hist2);
        friend bool operator <(histogram &hist1, histogram &hist2);
        friend ostream& operator <<(ostream& os,const histogram &hist);
        histogram operator +(const histogram &hist1);
        void operator +=(const histogram &hist1);

        //public data
        //int numberofdigits;



    protected:

    private:

        //string text[50];
        //private data




};
#endif // histogram_h
