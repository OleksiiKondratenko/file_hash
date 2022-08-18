#pragma once

#include "BuilderAbstract.hpp"
#include "ReaderBuilderAbstract.hpp"
#include "FileReader.hpp"

class FileReaderBuilder : public ReaderBuilderAbstract,
    private BuilderAbstract<FileReader, const std::string&, unsigned, int, int, FileReader::OnReadFunctor>
{
public:
    ReaderAbstract &&getReader() override
    {
        return std::move(getInstance());
    }
};
