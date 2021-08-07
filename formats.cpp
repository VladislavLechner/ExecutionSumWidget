#include "formats.h"


std::string Formats::currentFormat(const std::string& format)
{
    if (format == "zip")
        return "Zip";
    else if(format == "txt")
        return "ASCII text";
    else if(format == "jpg")
        return "JPEG";
    else if (format == "pdf")
        return "PDF";
    else if (format == "run")
        return "ELF";
    else if (format == "webp")
        return "RIFF";
    else if (format == "png")
        return "PNG";
    else if (format == "rar")
        return "RAR";
    else if (format == "mp3")
        return "Audio file with ID3";
    else if (format =="doc")
        return "Microsoft Word";
    else if (format == "xlsx")
        return "Microsoft Excel";
    else if (format == "")
    {
        return "";
    }
    else
    {
        throw std::runtime_error("Неверный формат файла(ов)");
    }
}


bool Formats::matching(const std::string& path, const std::string& inputFormat)
{
    std::string forHex("file -b " + path + " > format.txt");
    system(forHex.c_str());
    std::ifstream formatFile(boost::filesystem::current_path().string() + "/format.txt");
    std::string temp;

    if (formatFile.is_open())
    {
        getline(formatFile,temp);
        formatFile.close();
    }
    else
    {
        throw std::runtime_error("Файл format.txt не открылся");
    }
    size_t pos = temp.find(",");
    if (pos < temp.size())
        temp.erase(pos, temp.size());
    return (temp.find(currentFormat(inputFormat)) < temp.size());
}
