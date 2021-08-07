#include "readdirectory.h"


std::pair<std::list<std::string>, std::list<std::string> > ReadDirectory::resultOfMd5Sum() const
{
    return m_md5sum.resultOfMd5Sum();
}

std::pair<int, int > ReadDirectory::countOfFiles() const
{
    return m_countOfFiles;
}

std::list<std::string> ReadDirectory::otherFiles() const
{
    return m_otherFilies;
}


void ReadDirectory::checkInputData(const std::string& dir, const std::string& format, const std::string& operation)
{
    try {
        std::cout << "ReadDirectory's thread id: " <<  std::this_thread::get_id() << std::endl;
        m_md5sum.setInputPath(dir);
        if (boost::filesystem::exists(dir) && operation == "ctrlSum")
            readDirectory(dir, format);
        else {
            throw std::system_error(std::error_code(2,std::system_category()));
        }
    }  catch (...) {
        m_exception_ptr = std::current_exception();
        return;
    }
}

std::exception_ptr ReadDirectory::exception_ptr() const
{
    return m_exception_ptr;
}

void ReadDirectory::readDirectory(const std::string& dir, const std::string& format)
{
    try {
        Formats currentFormat;
        if (!boost::filesystem::is_directory(dir) && currentFormat.matching(dir, format))
        {
            m_md5sum.md5Sum(dir);
            return;
        }
        boost::filesystem::recursive_directory_iterator end;
        for(boost::filesystem::recursive_directory_iterator it(dir); it != end; ++it)
        {
            if (!boost::filesystem::is_directory(*it) && currentFormat.matching(it->path().string(), format))
            {
                m_md5sum.md5Sum(it->path().string());
                ++m_countOfFiles.first;
            }
            else if (!currentFormat.matching(it->path().string(), format) && !boost::filesystem::is_directory(*it))
            {
                m_otherFilies.push_back(it->path().string().substr(dir.size(), it->path().string().size()));
                ++m_countOfFiles.second;
            }
        }
    }  catch (...) {
        m_exception_ptr = std::current_exception();
        return;
    }
}

