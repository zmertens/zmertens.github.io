///////////////////////////////////////////////////////////
/// @zmertens
/// Builds a file using an approximate Markdown format
///////////////////////////////////////////////////////////

#pragma once
#ifndef MARKDOWN_BUILDER_HPP
#define MARKDOWN_BUILDER_HPP

#include <memory>

class Markdown {

};

class MarkdownBuilder {
public:
    typedef std::unique_ptr<Markdown> MarkdownPtr;

    MarkdownPtr build() const;

protected:

private:
    

};

#endif // MARKDOWN_BUILDER_HPP
