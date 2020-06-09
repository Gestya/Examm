#ifndef CODESAMPLE_H
#define CODESAMPLE_H

#include "string"

struct CodeSample
{
    std::string organization;
    std::string project;
    std::string component;
    std::string class_name;
    std::string method_name;

    bool wholly_filled() const
    {
        return !organization.empty() && !project.empty() && !component.empty()
                && !class_name.empty() && !method_name.empty();
    }
};

#endif // CODESAMPLE_H
