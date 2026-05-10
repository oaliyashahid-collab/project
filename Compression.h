// ============================
// COMPRESSION.H
// ============================

#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <fstream>
#include "Image.h"

class Compressor
{
public:

    static void compress(Image& img,
        string filename)
    {
        ofstream file(filename, ios::binary);

        int width = img.getWidth();
        int height = img.getHeight();

        file.write((char*)&width, sizeof(width));
        file.write((char*)&height, sizeof(height));

        for (int i = 0; i < height; i++)
        {
            int count = 1;

            Pixel prev = img.getPixel(0, i);

            for (int j = 1; j < width; j++)
            {
                Pixel current =
                    img.getPixel(j, i);

                if (current.r == prev.r &&
                    current.g == prev.g &&
                    current.b == prev.b)
                {
                    count++;
                }
                else
                {
                    file.write((char*)&count,
                        sizeof(count));

                    file.write((char*)&prev,
                        sizeof(Pixel));

                    prev = current;
                    count = 1;
                }
            }

            file.write((char*)&count,
                sizeof(count));

            file.write((char*)&prev,
                sizeof(Pixel));
        }

        file.close();
    }

    static Image decompress(string filename)
    {
        ifstream file(filename, ios::binary);

        int width;
        int height;

        file.read((char*)&width, sizeof(width));
        file.read((char*)&height, sizeof(height));

        Image img(width, height);

        int x = 0;
        int y = 0;

        while (!file.eof())
        {
            int count;
            Pixel p;

            file.read((char*)&count,
                sizeof(count));

            file.read((char*)&p,
                sizeof(Pixel));

            if (file.eof())
            {
                break;
            }

            for (int i = 0; i < count; i++)
            {
                img.setPixel(x, y, p);

                x++;

                if (x >= width)
                {
                    x = 0;
                    y++;
                }
            }
        }

        file.close();

        return img;
    }
};

#endif