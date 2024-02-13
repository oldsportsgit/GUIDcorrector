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
    std::cout << "Hello World!\n";
    std::string IncorrectGUIDsPath = R"(C:\Users\Stanley Yelnats\Downloads\bbcrProj\ExportedProject\Assets\Scripts\Unity.RenderPipelines.Universal.Runtime)";
    std::string CorrectGUIDsPath = R"(C:\Users\Stanley Yelnats\Downloads\bbcrProj\ExportedProject\Library\PackageCache\com.unity.render-pipelines.universal@10.10.1\Runtime)";
    std::string UnityProjectPath = R"(C:\Users\Stanley Yelnats\Downloads\bbcrProj\ExportedProject\Assets)";
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