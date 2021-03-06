#include "texture.h"
#include "lodepng/lodepng.h"

namespace evl {

Texture::Texture(const std::string& name, uint width, uint height, std::vector<uint8_t>& imageBuf)
    : mWidth(width)
    , mHeight(height)
    , mName(name)
{
    Upload(imageBuf);
}

Texture::~Texture()
{
    std::cout << "Texture deleted\n";
    glDeleteTextures(1, &mId);
}

void Texture::Upload(const std::vector<unsigned char>& imageBuf)
{
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_2D, mId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
        mWidth, mHeight,
        0, GL_RGBA, GL_UNSIGNED_BYTE, &imageBuf[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}
}
