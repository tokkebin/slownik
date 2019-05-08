#include <cassert>
#include <string>
#include <iostream>

using namespace std;
void test_int()
{
	MultiSlownik<int, int> dict;

	// slownik jest pusty
	assert(dict.isEmpty() == true);
	assert(dict.size() == 0);
	assert(dict.contains(0) == false);

	// dodanie elementu do slownika
	dict.insert(0, 1);
	assert(dict.isEmpty() == false);
	assert(dict.size() == 1);
	assert(dict.contains(0) == true);
	assert(dict.value(0) == 1);

	// dodanie elementu do slownika jako pary
	dict.insert(1, 2);
	assert(dict.size() == 2);
	assert(dict.contains(1) == true);
	assert(dict.value(0) == 1);
	assert(dict.value(1) == 2);

	// operator []
	assert(dict[0] == 1);
	assert(dict[1] == 2);

	// operator [] tworzy nowy element
	dict[2] = 3;
	assert(dict.value(2) == 3);
	assert(dict.size() == 3);


	// nadpisanie wartosci dla istniejacego elementu
	dict.insert(2, 4);
	assert(dict.size() == 3);
	assert(dict.value(2) == 4);

	dict.show();


	MultiSlownik<int, int> dict1;
    dict1.insert(0, 1);
    dict1.insert(5, 6);
    dict1.insert(1,2);
    assert(dict1.compare_dict(dict,dict1)==false);
    //cout<<dict1.compare_dict(dict,dict1)<<endl;

	MultiSlownik<int, int> dict2;
    dict2.insert(0, 1);
    dict2.insert(1, 2);
    dict2[2] = 3;
    assert(dict2.compare_dict(dict,dict2)==true);
    //cout<<dict2.compare_dict(dict,dict2)<<endl;



}
#include "../histogram/project2/histogram.h"
void test_hist()
{
    MultiSlownik<histogram,histogram> dict_his;

    histogram hist1;
    histogram hist2;
    histogram hist3;
    histogram hist4;

    string text = "jfhi2o4ur";
    string text1 = "74278";
    string text2 = "5375";

    hist1.counterevrydigit(hist1.occurranceofdigits,text);
    hist1.counterfrequency(hist1.frequency,hist1.occurranceofdigits,text);

    hist3.counterevrydigit(hist3.occurranceofdigits,text1);
    hist3.counterfrequency(hist3.frequency,hist3.occurranceofdigits,text1);

    hist4.counterevrydigit(hist4.occurranceofdigits,text2);
    hist4.counterfrequency(hist4.frequency,hist4.occurranceofdigits,text2);

    // slownik jest pusty
	assert(dict_his.isEmpty() == true);
	assert(dict_his.size() == 0);
	assert(dict_his.contains(hist1) == false);



	// dodanie elementu do slownika
	dict_his.insert(hist1, hist2);
	assert(dict_his.isEmpty() == false);
	assert(dict_his.size() == 1);
	assert(dict_his.contains(hist1) == true);
	assert(dict_his.value(hist1) == hist2);

	dict_his.show();



	MultiSlownik<histogram, histogram> dict1;
    dict1.insert(hist3, hist4);
    dict1.insert(hist1, hist2);
    assert(dict1.compare_dict(dict_his,dict1)==false);
    //cout<<dict1.compare_dict(dict,dict1)<<endl;

	MultiSlownik<histogram, histogram> dict2;
    dict2.insert(hist1, hist2);
    assert(dict2.compare_dict(dict_his,dict2)==true);

}
