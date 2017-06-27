#ifndef GLUTILS_HPP
#define GLUTILS_HPP

#include <string>

#include "SdlManager.hpp"

/**
 * This class is not intended to be initialized.
 * When checking for errors, wrap the function call around the code to check.
 * @brief The GlUtils class
 */
class GlUtils
{
public:
    static bool CheckForOpenGLError(const std::string& file, int line);
};

#endif // GLUTILS_HPP
