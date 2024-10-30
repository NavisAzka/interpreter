#include "main.h"

// Fungsi untuk mengonversi karakter ke nilai integer (0-9 atau A-F)
int charToValue(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 10;
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 10;
    return -1; // Karakter tidak valid
}

// Fungsi untuk mengonversi nilai integer ke karakter (0-9 atau A-F)
char valueToChar(int value)
{
    if (value >= 0 && value <= 9)
        return '0' + value;
    if (value >= 10 && value <= 35)
        return 'A' + (value - 10);
    return '?'; // Nilai tidak valid
}

// Fungsi untuk mengonversi bilangan dari basis_awal ke desimal (basis 10)
int toDecimal(const std::string &number, int basis_awal)
{
    int result = 0;
    int power = 0;
    // Membaca dari kanan ke kiri (menghitung pangkat basis)
    for (int i = number.size() - 1; i >= 0; --i)
    {
        int value = charToValue(number[i]);
        if (value < 0 || value >= basis_awal)
        {
            std::cerr << "Invalid digit in number: " << number[i] << " for base " << basis_awal << std::endl;
            return -1;
        }
        result += value * std::pow(basis_awal, power);
        power++;
    }
    return result;
}

// Fungsi untuk mengonversi bilangan dari desimal ke basis tujuan
std::string fromDecimal(std::string num, int basis_tujuan)
{
    int number = std::stoi(num);

    if (number == 0)
        return "0";

    std::string result;
    while (number > 0)
    {
        int remainder = number % basis_tujuan;
        result += valueToChar(remainder);
        number /= basis_tujuan;
    }
    std::reverse(result.begin(), result.end()); // Balik urutan hasil
    return result;
}

// Fungsi untuk mengonversi bilangan dari desimal ke basis tujuan
std::string fromDecimal(int number, int basis_tujuan)
{
    if (number == 0)
        return "0";

    std::string result;
    while (number > 0)
    {
        int remainder = number % basis_tujuan;
        result += valueToChar(remainder);
        number /= basis_tujuan;
    }
    std::reverse(result.begin(), result.end()); // Balik urutan hasil
    return result;
}

// Fungsi utama untuk mengubah bilangan dari basis_awal ke basis_tujuan
std::string convertBase(const std::string &number, int basis_awal, int basis_tujuan)
{
    // Konversi dari basis_awal ke desimal
    int decimalNumber = toDecimal(number, basis_awal);
    if (decimalNumber == -1)
    {
        return "Error: Invalid input";
    }

    // Konversi dari desimal ke basis_tujuan
    return fromDecimal(decimalNumber, basis_tujuan);
}
