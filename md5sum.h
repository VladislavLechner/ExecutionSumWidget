#pragma once

#include <iostream>
#include <thread>
#include <boost/filesystem.hpp>
#include <boost/uuid/name_generator.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

#include "formats.h"

class Md5Sum
{
public:
    Md5Sum() = default;
    void md5Sum(const std::string& dir);
    void setInputPath(const std::string inputPath);
    std::list <std::string> otherFiles() const;
    std::pair<std::list<std::string>, std::list<std::string> > resultOfMd5Sum() const;
    std::pair<int, int> countOfFiles() const;

private:
    std::pair<std::list<std::string>, std::list<std::string>> m_resultOfMd5Sum;
    std::list<std::string> m_otherFiles;
    std::string m_inputPath;

private:
    std::string toString(const boost::uuids::detail::md5::digest_type &digest);
};
