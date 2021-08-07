#include "md5sum.h"

std::pair<std::list<std::string>, std::list<std::string> > Md5Sum::resultOfMd5Sum() const
{
    return m_resultOfMd5Sum;
}

std::string Md5Sum::toString(const boost::uuids::detail::md5::digest_type &digest)
{
    const auto charDigest = reinterpret_cast<const char *>(&digest);
    std::string result;
    boost::algorithm::hex(charDigest, charDigest + sizeof(boost::uuids::detail::md5::digest_type), std::back_inserter(result));
    return result;
}

void Md5Sum::md5Sum(const std::string& dir)
{
    std::cout << "Md5Sum's thread id: " <<  std::this_thread::get_id() << std::endl;

    boost::uuids::detail::md5 md5sum;
    boost::uuids::detail::md5::digest_type digest {};
    std::ifstream currentFile(dir);
    std::string readCurrentFile {std::istreambuf_iterator<char>(currentFile), std::istreambuf_iterator<char>()};

    md5sum.process_bytes(readCurrentFile.data(),readCurrentFile.size());
    md5sum.get_digest(digest);

    m_resultOfMd5Sum.first.push_back(dir.substr(m_inputPath.size(), dir.size()));
    m_resultOfMd5Sum.second.push_back(toString(digest));
}

void Md5Sum::setInputPath(const std::string inputPath)
{
    m_inputPath = inputPath;
}


