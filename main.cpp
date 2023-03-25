#include <iostream>
#include <fstream>
#include <math.h>


using namespace std;


struct piksel
{
    uint8_t RED;
    uint8_t GREEN;
    uint8_t BLUE;
};


struct BITMAPFILEHEADER
{
    uint8_t bfType1;
    uint8_t bfType2;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BITMAPINFOHEADER
{
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXpelsPerMeter;
    uint32_t biYpelsPerMeter;
    uint32_t biCrlUses;
    uint32_t biCrlImportant;
};


uint8_t sprawdzenieWartosci(int a)
{
    if (a < 0) return (uint8_t)0;
    else if(a>255) return (uint8_t)255;
    else return (uint8_t)a;
}

void wczytajPlik(BITMAPFILEHEADER& naglowekPliku,BITMAPINFOHEADER& naglowekObrazu,piksel**& tablicaPikseli,int &wiersze,int &kolumny)
{
    bool niepoprawnyPlik = false;

    do
    {
        cout << "Podaj nazwe pliku wraz z rozszerzeniem: ";
        char nazwa[80];
        cin >> nazwa;
        ifstream plik;

        plik.open(nazwa, ios::binary);
        
        if (plik.good())
        {
            plik.read(reinterpret_cast<char*>(&naglowekPliku.bfType1), 1);
            plik.read(reinterpret_cast<char*>(&naglowekPliku.bfType2), 1);
            plik.read(reinterpret_cast<char*>(&naglowekPliku.bfSize), 4);
            plik.read(reinterpret_cast<char*>(&naglowekPliku.bfReserved1), 2);
            plik.read(reinterpret_cast<char*>(&naglowekPliku.bfReserved2), 2);
            plik.read(reinterpret_cast<char*>(&naglowekPliku.bfOffBits), 4);

            plik.read(reinterpret_cast<char*>(&naglowekObrazu.biSize), 4);
            plik.read(reinterpret_cast<char*>(&naglowekObrazu.biWidth), 4);
            plik.read(reinterpret_cast<char*>(&naglowekObrazu.biHeight), 4);
            plik.read(reinterpret_cast<char*>(&naglowekObrazu.biPlanes), 2);
            plik.read(reinterpret_cast<char*>(&naglowekObrazu.biBitCount), 2);
            plik.read(reinterpret_cast<char*>(&naglowekObrazu.biCompression), 4);
            plik.read(reinterpret_cast<char*>(&naglowekObrazu.biSizeImage), 4);
            plik.read(reinterpret_cast<char*>(&naglowekObrazu.biXpelsPerMeter), 4);
            plik.read(reinterpret_cast<char*>(&naglowekObrazu.biYpelsPerMeter), 4);
            plik.read(reinterpret_cast<char*>(&naglowekObrazu.biCrlUses), 4);
            plik.read(reinterpret_cast<char*>(&naglowekObrazu.biCrlImportant), 4);

             wiersze = naglowekObrazu.biHeight;
             if (naglowekObrazu.biWidth % 4 == 0) kolumny = naglowekObrazu.biWidth;
             else
             kolumny = naglowekObrazu.biWidth + (4 - naglowekObrazu.biWidth % 4);

            tablicaPikseli = new piksel * [wiersze];
            for (int i = 0; i < wiersze; i++)
            {
                tablicaPikseli[i] = new piksel[kolumny];
            }


            for (int i = 0; i < wiersze; i++)
            {
                for (int g = 0; g < kolumny; g++)
                {
                    
                    plik.read(reinterpret_cast<char*>(&tablicaPikseli[i][g].BLUE), 1);
                    plik.read(reinterpret_cast<char*>(&tablicaPikseli[i][g].GREEN), 1);
                    plik.read(reinterpret_cast<char*>(&tablicaPikseli[i][g].RED), 1);
                    
                }
            }

            

            plik.close();
            niepoprawnyPlik = false;
        }
        else
        {
            cout << "Nie udalo sie otworzyc pliku!" << endl;
            niepoprawnyPlik = true;
        }
    } while (niepoprawnyPlik);

}

void wypiszNaglowki(BITMAPFILEHEADER naglowekPliku, BITMAPINFOHEADER naglowekObrazu)
{
    cout << endl;
    cout << "Sygnatura pliku: " << naglowekPliku.bfType1<<naglowekPliku.bfType2<<endl;
    cout << "Dlugosc pliku: " << naglowekPliku.bfSize<<endl;
    cout << "Pole zarezerwowane: " << naglowekPliku.bfReserved1<<endl;
    cout << "Pole zarezerwowane: " << naglowekPliku.bfReserved2<<endl;
    cout << "Pozycja danych obrazowych w pliku: " << naglowekPliku.bfOffBits<<endl;

    cout << endl;

    cout << "Rozmiar naglowka informacyjnego: " << naglowekObrazu.biSize<<endl;
    cout << "Szerokosc obrazu: " << naglowekObrazu.biWidth<<endl;
    cout << "Wysokosc obrazu: " << naglowekObrazu.biHeight<<endl;
    cout << "Liczba platow: " << naglowekObrazu.biPlanes<<endl;
    cout << "Liczba platow na piksel: " << naglowekObrazu.biBitCount<<endl;
    cout << "Algorytm kompresji: " << naglowekObrazu.biCompression<<endl;
    cout << "Rozmiar rysunku: " << naglowekObrazu.biSizeImage<<endl;
    cout << "Rozdzielczosc pozioma: " << naglowekObrazu.biXpelsPerMeter<<endl;
    cout << "Rozdzielczosc pionowa: " << naglowekObrazu.biYpelsPerMeter <<endl;
    cout << "Liczba kolorow w palecie: " << naglowekObrazu.biCrlUses<<endl;
    cout << "Liczba waznych kolorow w palecie: " << naglowekObrazu.biCrlImportant<<endl;

    cout << endl;
}

void operatorSobela(piksel**& nowaTablicaPikseli,piksel**& tablicaPikseli, int wiersze, int kolumny)
{

    
    int maski[8][3][3];


    maski[0][0][0] = -1;
    maski[0][0][1] = 0;
    maski[0][0][2] = 1;
    maski[0][1][0] = -2;
    maski[0][1][1] = 0;
    maski[0][1][2] = 2;
    maski[0][2][0] = -1;
    maski[0][2][1] = 0;
    maski[0][2][2] = 1;

    maski[1][0][0] = 0;
    maski[1][0][1] = 1;
    maski[1][0][2] = 2;
    maski[1][1][0] = -1;
    maski[1][1][1] = 0;
    maski[1][1][2] = 1;
    maski[1][2][0] = -2;
    maski[1][2][1] = -1;
    maski[1][2][2] = 0;

    maski[2][0][0] = 1;
    maski[2][0][1] = 2;
    maski[2][0][2] = 1;
    maski[2][1][0] = 0;
    maski[2][1][1] = 0;
    maski[2][1][2] = 0;
    maski[2][2][0] = -1;
    maski[2][2][1] = -2;
    maski[2][2][2] = -1;

    maski[3][0][0] = 2;
    maski[3][0][1] = 1;
    maski[3][0][2] = 0;
    maski[3][1][0] = 1;
    maski[3][1][1] = 0;
    maski[3][1][2] = -1;
    maski[3][2][0] = 0;
    maski[3][2][1] = -1;
    maski[3][2][2] = -2;

    for (int i = 4; i < 8; i++)
    {
        for (int g = 0; g < 3; g++)
        {
            for (int h = 0; h < 3; h++)
            {
                maski[i][g][h] = maski[i - 4][g][h] * (-1);
            }
        }
    }
    piksel*** tabliceDlaMasek;
    tabliceDlaMasek = new piksel * *[8];
    for (int i = 0; i < 8; i++)
    {
        tabliceDlaMasek[i] = new piksel * [wiersze];
    }
    for (int i = 0; i < 8; i++)
    {
        for (int g = 0; g < wiersze; g++)
        {
            tabliceDlaMasek[i][g] = new piksel[kolumny];
        }
    }

    for(int i=0;i<8;i++)
    {
        for(int g=0;g<wiersze;g++)
        {
            for(int m=0;m<kolumny;m++)
            {
                tabliceDlaMasek[i][g][m].RED=0;
                tabliceDlaMasek[i][g][m].GREEN=0;
                tabliceDlaMasek[i][g][m].BLUE=0;
            }
        }
    }

    for (int i = 0; i < 8; i++)
    {
        for (int m = 1; m < wiersze-1; m++)
        {
            for (int n = 1; n < kolumny - 1; n++)
            {
                tabliceDlaMasek[i][m][n].RED = sprawdzenieWartosci(maski[i][0][0] * (int)tablicaPikseli[m - 1][n - 1].RED + maski[i][0][1] * (int)tablicaPikseli[m - 1][n].RED + maski[i][0][2] * (int)tablicaPikseli[m - 1][n + 1].RED + maski[i][1][0] * (int)tablicaPikseli[m][n - 1].RED + maski[i][1][1] * (int)tablicaPikseli[m][n].RED + maski[i][1][2] * (int)tablicaPikseli[m][n + 1].RED + maski[i][2][0] * (int)tablicaPikseli[m + 1][n - 1].RED + maski[i][2][1] * (int)tablicaPikseli[m + 1][n].RED + maski[i][2][2] * (int)tablicaPikseli[m + 1][n + 1].RED);
                tabliceDlaMasek[i][m][n].BLUE = sprawdzenieWartosci(maski[i][0][0] * (int)tablicaPikseli[m - 1][n - 1].BLUE + maski[i][0][1] * (int)tablicaPikseli[m - 1][n].BLUE + maski[i][0][2] * (int)tablicaPikseli[m - 1][n + 1].BLUE + maski[i][1][0] * (int)tablicaPikseli[m][n - 1].BLUE + maski[i][1][1] * (int)tablicaPikseli[m][n].BLUE + maski[i][1][2] * (int)tablicaPikseli[m][n + 1].BLUE + maski[i][2][0] * (int)tablicaPikseli[m + 1][n - 1].BLUE + maski[i][2][1] * (int)tablicaPikseli[m + 1][n].BLUE + maski[i][2][2] * (int)tablicaPikseli[m + 1][n + 1].BLUE);
                tabliceDlaMasek[i][m][n].GREEN = sprawdzenieWartosci(maski[i][0][0] * (int)tablicaPikseli[m - 1][n - 1].GREEN + maski[i][0][1] * (int)tablicaPikseli[m - 1][n].GREEN + maski[i][0][2] * (int)tablicaPikseli[m - 1][n + 1].GREEN + maski[i][1][0] * (int)tablicaPikseli[m][n - 1].GREEN + maski[i][1][1] * (int)tablicaPikseli[m][n].GREEN + maski[i][1][2] * (int)tablicaPikseli[m][n + 1].GREEN + maski[i][2][0] * (int)tablicaPikseli[m + 1][n - 1].GREEN + maski[i][2][1] * (int)tablicaPikseli[m + 1][n].GREEN + maski[i][2][2] * (int)tablicaPikseli[m + 1][n + 1].GREEN);
            }
        }
    }

   
    for (int m = 1; m < wiersze; m++)
    {
        for (int n = 1; n < kolumny; n++)
        {
            int sumaRED=0;
            int sumaBLUE=0;
            int sumaGREEN=0;
            for (int i = 0; i < 8; i++)
            {
                sumaRED += tabliceDlaMasek[i][m][n].RED;
                sumaBLUE += tabliceDlaMasek[i][m][n].BLUE;
                sumaGREEN += tabliceDlaMasek[i][m][n].GREEN;
            } 
            //ustawienie pikseli oraz podbicie ich jasnosci i kontrastu
            nowaTablicaPikseli[m][n].RED = sprawdzenieWartosci(ceil(sumaRED / 8 +15)*1.8);
            nowaTablicaPikseli[m][n].BLUE = sprawdzenieWartosci(ceil(sumaBLUE / 8+15)*1.8);
            nowaTablicaPikseli[m][n].GREEN = sprawdzenieWartosci(ceil(sumaGREEN / 8+15)*1.8);
        }
    }
   
    
    for(int i=0;i<8;i++)
    {
        for(int m=0;m<wiersze;m++)
        {
            delete [] tabliceDlaMasek[i][m];
        }
        delete [] tabliceDlaMasek[i];
    }
        delete[] tabliceDlaMasek;
        tabliceDlaMasek= NULL;
    }

    



void zapiszDoPliku(piksel**& tablicaPikseli, int wiersze, int kolumny, BITMAPFILEHEADER naglowekPliku, BITMAPINFOHEADER naglowekObrazu)
{
    char nazwa[30];
    cout<<"Podaj nazwe pliku wyjsciowego wraz rozszerzeniem: ";
    cin>>nazwa;


    ofstream plik;
    plik.open(nazwa, ios::binary);

    plik.write(reinterpret_cast<char*>(&naglowekPliku.bfType1), 1);
    plik.write(reinterpret_cast<char*>(&naglowekPliku.bfType2), 1);
    plik.write(reinterpret_cast<char*>(&naglowekPliku.bfSize), 4);
    plik.write(reinterpret_cast<char*>(&naglowekPliku.bfReserved1), 2);
    plik.write(reinterpret_cast<char*>(&naglowekPliku.bfReserved2), 2);
    plik.write(reinterpret_cast<char*>(&naglowekPliku.bfOffBits), 4);

    plik.write(reinterpret_cast<char*>(&naglowekObrazu.biSize), 4);
    plik.write(reinterpret_cast<char*>(&naglowekObrazu.biWidth), 4);
    plik.write(reinterpret_cast<char*>(&naglowekObrazu.biHeight), 4);
    plik.write(reinterpret_cast<char*>(&naglowekObrazu.biPlanes), 2);
    plik.write(reinterpret_cast<char*>(&naglowekObrazu.biBitCount), 2);
    plik.write(reinterpret_cast<char*>(&naglowekObrazu.biCompression), 4);
    plik.write(reinterpret_cast<char*>(&naglowekObrazu.biSizeImage), 4);
    plik.write(reinterpret_cast<char*>(&naglowekObrazu.biXpelsPerMeter), 4);
    plik.write(reinterpret_cast<char*>(&naglowekObrazu.biYpelsPerMeter), 4);
    plik.write(reinterpret_cast<char*>(&naglowekObrazu.biCrlUses), 4);
    plik.write(reinterpret_cast<char*>(&naglowekObrazu.biCrlImportant), 4);


    for (int i = 0; i < wiersze; i++)
    {
        for (int g = 0; g < kolumny; g++)
        {
            if(tablicaPikseli)
            { 
                plik.write(reinterpret_cast<char*>(&tablicaPikseli[i][g].BLUE), 1);
                plik.write(reinterpret_cast<char*>(&tablicaPikseli[i][g].GREEN), 1);
                plik.write(reinterpret_cast<char*>(&tablicaPikseli[i][g].RED), 1);
            }

        }
    }
    plik.close();

    cout<<"Poprawnie zapisano do pliku!"<<endl;
}

int main()
{
    BITMAPFILEHEADER naglowekPliku;
    BITMAPINFOHEADER naglowekObrazu;
    piksel** tablicaPikseli;
    int wiersze, kolumny;

    piksel** nowaTablicaPikseli;

    

    wczytajPlik(naglowekPliku, naglowekObrazu,tablicaPikseli,wiersze,kolumny);
    wypiszNaglowki(naglowekPliku, naglowekObrazu);

    nowaTablicaPikseli = new piksel * [wiersze];
    for (int i = 0; i < wiersze; i++)
    {
        nowaTablicaPikseli[i] = new piksel[kolumny];
    }

    for (int i = 0; i < wiersze; i++)
    {
        for (int g = 0; g < kolumny; g++)
        {
            nowaTablicaPikseli[i][g].BLUE=0;
            nowaTablicaPikseli[i][g].GREEN=0;
            nowaTablicaPikseli[i][g].RED=0;
        }
    }



    operatorSobela(nowaTablicaPikseli,tablicaPikseli, wiersze, naglowekObrazu.biWidth);
   
    zapiszDoPliku(nowaTablicaPikseli, wiersze, kolumny, naglowekPliku, naglowekObrazu);

    

        for (int i = 0; i < wiersze; i++)
        {

            delete[] tablicaPikseli[i];
            delete[] nowaTablicaPikseli[i];

        }
        delete[] nowaTablicaPikseli;
        delete[] tablicaPikseli;
    

    nowaTablicaPikseli=NULL;
    tablicaPikseli = NULL;
}


