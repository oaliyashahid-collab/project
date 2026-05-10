// ============================
// PIXEL.H
// ============================
#pragma once
#ifndef PIXEL_H
#define PIXEL_H

struct Pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;

    Pixel(unsigned char r = 0,
        unsigned char g = 0,
        unsigned char b = 0)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

#endif