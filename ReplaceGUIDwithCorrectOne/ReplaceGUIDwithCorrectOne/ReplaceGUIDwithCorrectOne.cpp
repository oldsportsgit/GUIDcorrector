// ReplaceGUIDwithCorrectOne.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <regex>
#include <Windows.h>

std::string ReplaceSubstring(std::string string, std::string substring, std::string replaceWith)
{
    return std::regex_replace(string, std::regex(substring), replaceWith);
}

int main()
{
    std::string IncorrectGUIDsPath;
    std::string CorrectGUIDsPath;
    std::string UnityProjectPath;
    std::cout << "Give the path to the Incorrect guids (the package folder containing them) usually '/Assets/Scripts/[Package]'\n";
    //std::cin >> IncorrectGUIDsPath;
    std::getline(std::cin, IncorrectGUIDsPath);
    std::cout << "Give the path where the actual package is that usually being '/Library/PackageCache/[Package]/Runtime'\n";
    std::getline(std::cin, CorrectGUIDsPath);
    std::cout << "Give the path to the Unity Project's 'Assets' folder '/Assets'\n";
    std::getline(std::cin, UnityProjectPath);
    std::filesystem::path path1 = IncorrectGUIDsPath;
    std::filesystem::path path2 = CorrectGUIDsPath;
    std::filesystem::path path3 = UnityProjectPath;
    if (!std::filesystem::exists(path1) || !std::filesystem::exists(path2) || !std::filesystem::exists(path3))
    {
        std::cout << "WTH? a path wasn't valid! double check and try again";
        return 0;
    }
    for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(IncorrectGUIDsPath))
    {
        if (entry.path().extension() == ".meta")
        {
            std::ifstream ifs(entry.path());
            //get file contents
            std::string contentsOfWrongGUID((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
            std::string incorrectGuid = contentsOfWrongGUID.substr(27, 32);
            for (const auto& entry2 : std::filesystem::recursive_directory_iterator(CorrectGUIDsPath))
            {
                if (entry2.path().filename().string() == entry.path().filename().string())
                {
                    std::ifstream ifs2(entry2.path());
                    //get file contents
                    std::string contentsOfCorrectGUID((std::istreambuf_iterator<char>(ifs2)), (std::istreambuf_iterator<char>()));
                    std::string CorrectGuid = contentsOfCorrectGUID.substr(27, 32);
                    for (const auto& ProjectAssetFile : std::filesystem::recursive_directory_iterator(UnityProjectPath))
                    {
                        std::ifstream _fileToCorrect(ProjectAssetFile.path());
                        std::string fileToCorrectContents((std::istreambuf_iterator<char>(_fileToCorrect)), (std::istreambuf_iterator<char>()));
                        if (fileToCorrectContents.find(incorrectGuid) != std::string::npos)
                        {
                            std::ofstream corrected(ProjectAssetFile.path());
                            corrected << ReplaceSubstring(fileToCorrectContents, incorrectGuid, CorrectGuid) << std::endl;
                            std::cout << "File " + ProjectAssetFile.path().filename().string() + " has been corrected\n";
                        }
                    }
                }
            }
        }
    }
}
