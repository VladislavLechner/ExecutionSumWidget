#pragma once

#include <iostream>
#include <thread>
#include <exception>

#include <boost/filesystem.hpp>

#include <QDebug>
#include <QWidget>

#include <md5sum.h>

class ReadDirectory
{
public:
    ReadDirectory() = default;
    std::pair<std::list<std::string>, std::list<std::string> > resultOfMd5Sum() const;
    std::pair<int, int> countOfFiles() const;
    std::list<std::string> otherFiles() const;
    void checkInputData(const std::string& dir, const std::string& format, const std::string& operation);

    std::exception_ptr exception_ptr() const;

private:
    Md5Sum m_md5sum;
    std::list<std::string> m_otherFilies;
    std::pair<int, int> m_countOfFiles;
    std::exception_ptr m_exception_ptr;

private:
    void readDirectory(const std::string& dir, const std::string& format);
    void handle_eptr(std::exception_ptr eptr);

};
