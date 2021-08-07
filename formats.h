#pragma once

#include <boost/filesystem.hpp>
#include <boost/exception/all.hpp>
#include <iostream>
#include <fstream>

class Formats
{
public:
    Formats() = default;
    bool matching(const std::string& path, const std::string& inputFormat);

private:
    std::string currentFormat(const std::string& format);

};

