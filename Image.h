// ============================
// IMAGE.H
// ============================

#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include <cmath>
#include "Matrix.h"
#include "Pixel.h"

class Image
{
private:

    Matrix<Pixel> pixels;
    int width;
    int height;

public:

    Image(int w = 0, int h = 0)
        : width(w), height(h), pixels(h, w)
    {
    }

    bool load(string filename)
    {
        ifstream file(filename, ios::binary);

        if (!file)
        {
            return false;
        }

        string format;
        file >> format;

        if (format != "P6")
        {
            return false;
        }

        file >> width >> height;

        int maxValue;
        file >> maxValue;

        file.ignore();

        pixels = Matrix<Pixel>(height, width);

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Pixel p;

                file.read((char*)&p.r, 1);
                file.read((char*)&p.g, 1);
                file.read((char*)&p.b, 1);

                pixels(i, j) = p;
            }
        }

        file.close();
        return true;
    }

    bool save(string filename)
    {
        ofstream file(filename, ios::binary);

        if (!file)
        {
            return false;
        }

        file << "P6\n";
        file << width << " " << height << "\n255\n";

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Pixel p = pixels(i, j);

                file.write((char*)&p.r, 1);
                file.write((char*)&p.g, 1);
                file.write((char*)&p.b, 1);
            }
        }

        file.close();
        return true;
    }

    Pixel getPixel(int x, int y)
    {
        return pixels(y, x);
    }

    void setPixel(int x, int y, Pixel value)
    {
        pixels(y, x) = value;
    }

    int getWidth()
    {
        return width;
    }

    int getHeight()
    {
        return height;
    }

    void grayscale()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Pixel& p = pixels(i, j);

                unsigned char gray =
                    (p.r + p.g + p.b) / 3;

                p.r = gray;
                p.g = gray;
                p.b = gray;
            }
        }
    }

    void brightness(int value)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Pixel& p = pixels(i, j);

                p.r = min(255, max(0, p.r + value));
                p.g = min(255, max(0, p.g + value));
                p.b = min(255, max(0, p.b + value));
            }
        }
    }

    void sharpen()
    {
        for (int i = 1; i < height - 1; i++)
        {
            for (int j = 1; j < width - 1; j++)
            {
                Pixel& p = pixels(i, j);

                p.r = min(255, p.r + 30);
                p.g = min(255, p.g + 30);
                p.b = min(255, p.b + 30);
            }
        }
    }

    void edgeDetection()
    {
        for (int i = 1; i < height - 1; i++)
        {
            for (int j = 1; j < width - 1; j++)
            {
                Pixel p1 = pixels(i - 1, j);
                Pixel p2 = pixels(i + 1, j);

                int diff = abs(p1.r - p2.r);

                unsigned char edge =
                    diff > 50 ? 255 : 0;

                pixels(i, j) =
                    Pixel(edge, edge, edge);
            }
        }
    }
};

#endif