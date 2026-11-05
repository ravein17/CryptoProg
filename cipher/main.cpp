#include <iostream>
#include <fstream>
#include <string>
#include <cstring> // Добавлено для memcpy
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

using namespace std;
using namespace CryptoPP;

int main(int argc, char* argv[]) 
{
    if (argc != 5) {
        cerr << "Использование: " << argv[0] << " <-e|-d> <входной_файл> <выходной_файл> <пароль>" << endl;
        return 1;
    }

    string mode = argv[1];
    string inputFile = argv[2];
    string outputFile = argv[3];
    string password = argv[4];

    CryptoPP::byte key[AES::MAX_KEYLENGTH];
    CryptoPP::byte iv[AES::BLOCKSIZE];
    SHA256 hash;
    hash.CalculateDigest(key, (const CryptoPP::byte*)password.c_str(), password.size());
    
    memcpy(iv, key, AES::BLOCKSIZE);

    try {
        if (mode == "-e") {
            CBC_Mode<AES>::Encryption e;
            e.SetKeyWithIV(key, sizeof(key), iv);
            FileSource fs(inputFile.c_str(), true, new StreamTransformationFilter(e, new FileSink(outputFile.c_str())));
            cout << "Файл успешно зашифрован." << endl;
        } 
        else if (mode == "-d") {
            CBC_Mode<AES>::Decryption d;
            d.SetKeyWithIV(key, sizeof(key), iv);
            FileSource fs(inputFile.c_str(), true, new StreamTransformationFilter(d, new FileSink(outputFile.c_str())));
            cout << "Файл успешно расшифрован." << endl;
        } 
        else {
            cerr << "Неизвестный режим. Используйте -e или -d" << endl;
            return 1;
        }
    } 
    catch (const Exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
